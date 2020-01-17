#include <iostream>
#include <fstream>
#include <map>

#include <STEPControl_Reader.hxx>
#include <IGESControl_Reader.hxx>
#include <TopoDS_Shape.hxx>

#include <TopTools_HSequenceOfShape.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <XCAFApp_Application.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <TDF_LabelSequence.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <TDF_Label.hxx>
#include <TDataStd_Name.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <VrmlData_Scene.hxx>
#include <TDocStd_Document.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS.hxx>
#include <BRep_Builder.hxx>
#include <Quantity_Color.hxx>


const std::string dataDirectory = "c:\\Source\\ModelConverter\\src\\data\\";
const std::string stepFileName = dataDirectory + "impeller.STEP";
const std::string igesFileName = dataDirectory + "impeller.IGS";
const std::string vrmlFileName = dataDirectory + "out_impeller.vrml";

void processShape(TopoDS_Shape& shape) {

	BRepMesh_IncrementalMesh(shape, 0.1, Standard_True);

	unsigned counter = 0;
	TopExp_Explorer ex;

	counter = 0;
	for (ex.Init(shape, TopAbs_VERTEX); ex.More(); ex.Next()) {
		++counter;

		TopoDS_Vertex vertex = TopoDS::Vertex(ex.Current());
		gp_Pnt point = BRep_Tool::Pnt(vertex);
		//cout << "Vertex " << counter << ": X: " << point.X() << " - Y:" << point.Y() << " - Z: " << point.Z() << std::endl;
	}
	std::cout << "STEP: Load vertex: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_FACE); ex.More(); ex.Next()) {
		++counter;
	}
	std::cout << "STEP: Load face: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_EDGE); ex.More(); ex.Next()) {
		++counter;
	}
	std::cout << "STEP: Load edge: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_SOLID); ex.More(); ex.Next()) {
		++counter;
	}
	std::cout << "STEP: Load solid: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_SHELL); ex.More(); ex.Next()) {
		++counter;
	}
	std::cout << "STEP: Load shell: " << counter << std::endl;
}

int importStep() {
    Handle(TopTools_HSequenceOfShape) aHSequenceOfShape = new TopTools_HSequenceOfShape();
    aHSequenceOfShape->Clear();
    //Create Document
    Handle(TDocStd_Document) aDoc;
    Handle(XCAFApp_Application) anApp = XCAFApp_Application::GetApplication();
    anApp->NewDocument("MDTV-XCAF", aDoc);

    // create additional log file
    STEPCAFControl_Reader aReader;
    aReader.SetColorMode(true);
    aReader.SetNameMode(true);
    aReader.SetLayerMode(true);

    IFSelect_ReturnStatus status = aReader.ReadFile(stepFileName.c_str());
    if (status != IFSelect_RetDone)
        //return NO;
        return 1;
    if (!aReader.Transfer(aDoc)) {
        //NSLog(@"STEP File could not be transfered");
        std::cout << "STEP File could not be transfered" << std::endl;
        //return NO;
        return 1;
    }

    Handle(XCAFDoc_ColorTool) myColors = XCAFDoc_DocumentTool::ColorTool(aDoc->Main());
    Handle(XCAFDoc_ShapeTool) myAssembly = XCAFDoc_DocumentTool::ShapeTool(aDoc->Main());
    TDF_LabelSequence frshapes;
    myAssembly->GetShapes(frshapes);
    //myAssembly->GetFreeShapes(frshapes);

    // set presentations and show
    for (Standard_Integer i = 1; i <= frshapes.Length(); i++) {
        // get the shapes and attributes
        const TDF_Label &label = frshapes.Value(i);
        Handle(TDataStd_Name) name;
        if (label.FindAttribute(TDataStd_Name::GetID(), name))
        {
            TCollection_ExtendedString extstr = name->Get();
            cout << extstr;
        }

        TopoDS_Shape shape;
        myAssembly->GetShape(label, shape);

		processShape(shape);

        aHSequenceOfShape->Append(shape);
    }

    //Export VRML

    Standard_Boolean ReturnValue = Standard_True;
    if (aHSequenceOfShape->Length() == 0)
    {
        return 1;
    }

    // VRML scene.
    VrmlData_Scene scene;
    //AFVrmlData_ShapeConvert converter(scene, myColors/*, 0.001*/); // from mm to meters
    Standard_Integer iShape = 1; // Counter of shapes

    for (int i = 1; i <= aHSequenceOfShape->Length(); i++)
    {
        // Shape
        TopoDS_Shape shape = aHSequenceOfShape->Value(i);
        if (shape.IsNull())
        {
            continue;
        }

		processShape(shape);

        // Give a name to the shape.
        TCollection_AsciiString name("Shape");
        name += TCollection_AsciiString(iShape++);
        //converter.AddShape(shape, name.ToCString());
    } // iterator of shapes

    //converter.Convert(true, false, 0.1); // faces only

    // Call VRML writer
    ofstream writer(vrmlFileName);
    writer << scene;
    writer.close();

    return 0;
}

int importStepParts() {
    STEPControl_Reader aReader;
    TopoDS_Shape aShape;

    const std::string encodedname = stepFileName;

    if (aReader.ReadFile((Standard_CString)encodedname.c_str()) != IFSelect_RetDone) {
        //throw Base::FileException("Cannot open STEP file");
        std::cout << "Cannot open STEP file" << std::endl;
        return 1;
    }

    //Handle(Message_ProgressIndicator) pi = new ProgressIndicator(100);
    //aReader.WS()->MapReader()->SetProgress(pi);
    //pi->NewScope(100, "Reading STEP file...");
    //pi->Show();

    // Root transfers
    Standard_Integer nbr = aReader.NbRootsForTransfer();
    //aReader.PrintCheckTransfer (failsonly, IFSelect_ItemsByEntity);
    for (Standard_Integer n = 1; n <= nbr; n++) {
        //Base::Console().Log("STEP: Transferring Root %d\n", n);
        std::cout << "STEP: Transferring Root " << n << std::endl;
        aReader.TransferRoot(n);
    }
    //pi->EndScope();

    // Collecting resulting entities
    Standard_Integer nbs = aReader.NbShapes();
    if (nbs == 0) {
        //throw Base::FileException("No shapes found in file ");
        std::cout << "No shapes found in file " << std::endl;
        return 1;
    } else {
        //Handle(StepData_StepModel) Model = aReader.StepModel();
        //Handle(XSControl_WorkSession) ws = aReader.WS();
        //Handle(XSControl_TransferReader) tr = ws->TransferReader();

        std::map<int, Quantity_Color> hash_col;
        //ReadColors(aReader.WS(), hash_col);
        //ReadNames(aReader.WS());

        aShape = aReader.OneShape();
		processShape(aShape);

        //for (Standard_Integer i = 1; i <= nbs; i++) {
        //    //Base::Console().Log("STEP:   Transferring Shape %d\n", i);
        //    std::cout << "STEP: Transferring Shape " << i << std::endl;
        //    //aShape = aReader.Shape(i);

        //    // load each solid as an own object
        //    TopExp_Explorer ex;
        //    int counter = 0;
        //    for (ex.Init(aShape, TopAbs_SOLID); ex.More(); ex.Next()) {
        //        std::cout << "STEP: Load solid: " << ++counter << std::endl;
        //        // get the shape
        //        const TopoDS_Solid &aSolid = TopoDS::Solid(ex.Current());

        //        //std::string name = fi.fileNamePure();
        //        //Handle(Standard_Transient) ent = tr->EntityFromShapeResult(aSolid, 3);
        //        //if (!ent.IsNull()) {
        //        //    name += ws->Model()->StringLabel(ent)->ToCString();
        //        //}

        //        //Part::Feature *pcFeature;
        //        //pcFeature = static_cast<Part::Feature *>(pcDoc->addObject("Part::Feature", name.c_str()));
        //        //pcFeature->Shape.setValue(aSolid);

        //        // This is a trick to access the GUI via Python and set the color property
        //        // of the associated view provider. If no GUI is up an exception is thrown
        //        // and cleared immediately
        //        //std::map<int, Quantity_Color>::iterator it = hash_col.find(aSolid.HashCode(INT_MAX));
        //        //if (it != hash_col.end()) {
        //        //    try {
        //        //        Py::Object obj(pcFeature->getPyObject(), true);
        //        //        Py::Object vp(obj.getAttr("ViewObject"));
        //        //        Py::Tuple col(3);
        //        //        col.setItem(0, Py::Float(it->second.Red()));
        //        //        col.setItem(1, Py::Float(it->second.Green()));
        //        //        col.setItem(2, Py::Float(it->second.Blue()));
        //        //        vp.setAttr("ShapeColor", col);
        //        //        //Base::Console().Message("Set color to shape\n");
        //        //    } catch (Py::Exception & e) {
        //        //        e.clear();
        //        //    }
        //        //}
        //    }
        //    counter = 0;
        //    // load all non-solids now
        //    for (ex.Init(aShape, TopAbs_SHELL, TopAbs_SOLID); ex.More(); ex.Next()) {
        //        std::cout << "STEP: Load shell: " << ++counter << std::endl;
        //        // get the shape
        //        const TopoDS_Shell &aShell = TopoDS::Shell(ex.Current());

        //        //std::string name = fi.fileNamePure();
        //        //Handle(Standard_Transient) ent = tr->EntityFromShapeResult(aShell, 3);
        //        //if (!ent.IsNull()) {
        //        //    name += ws->Model()->StringLabel(ent)->ToCString();
        //        //}

        //        //Part::Feature *pcFeature = static_cast<Part::Feature *>(pcDoc->addObject("Part::Feature", name.c_str()));
        //        //pcFeature->Shape.setValue(aShell);
        //    }

        //    // put all other free-flying shapes into a single compound
        //    Standard_Boolean emptyComp = Standard_True;
        //    BRep_Builder builder;
        //    TopoDS_Compound comp;
        //    builder.MakeCompound(comp);

        //    counter = 0;
        //    for (ex.Init(aShape, TopAbs_FACE, TopAbs_SHELL); ex.More(); ex.Next()) {
        //        std::cout << "STEP: Load face: " << ++counter << std::endl;
        //        if (!ex.Current().IsNull()) {
        //            builder.Add(comp, ex.Current());
        //            emptyComp = Standard_False;
        //        }
        //    }
        //    counter = 0;
        //    for (ex.Init(aShape, TopAbs_WIRE, TopAbs_FACE); ex.More(); ex.Next()) {
        //        std::cout << "STEP: Load wire: " << ++counter << std::endl;
        //        if (!ex.Current().IsNull()) {
        //            builder.Add(comp, ex.Current());
        //            emptyComp = Standard_False;
        //        }
        //    }
        //    counter = 0;
        //    for (ex.Init(aShape, TopAbs_EDGE, TopAbs_WIRE); ex.More(); ex.Next()) {
        //        std::cout << "STEP: Load edge: " << ++counter << std::endl;
        //        if (!ex.Current().IsNull()) {
        //            builder.Add(comp, ex.Current());
        //            emptyComp = Standard_False;
        //        }
        //    }
        //    counter = 0;
        //    for (ex.Init(aShape, TopAbs_VERTEX, TopAbs_EDGE); ex.More(); ex.Next()) {
        //        std::cout << "STEP: Load vertex: " << ++counter << std::endl;
        //        if (!ex.Current().IsNull()) {
        //            builder.Add(comp, ex.Current());
        //            emptyComp = Standard_False;
        //        }
        //    }

        //    if (!emptyComp) {
        //        //std::string name = fi.fileNamePure();
        //        //Part::Feature *pcFeature = static_cast<Part::Feature *>(pcDoc->addObject
        //        //("Part::Feature", name.c_str()));
        //        //pcFeature->Shape.setValue(comp);
        //    }
        //}
    }

    return 0;
}
    
int readStep() {
    STEPControl_Reader reader;
    IFSelect_ReturnStatus stat = reader.ReadFile(stepFileName.c_str());
    if (stat != IFSelect_RetDone) {
        std::cout << "Error reading file" << std::endl;
        return 1;
    }

    IFSelect_PrintCount mode = IFSelect_ListByItem;
    std::cout << "reader.PrintCheckLoad(false, mode)" << std::endl;
    reader.PrintCheckLoad(false, mode);

    // make brep
    //reader.TransferRoots();
    // one shape, who contain's all subshapes
    //TopoDS_Shape shape;
    //shape = reader.OneShape();

    Standard_Integer NbRoots = reader.NbRootsForTransfer(); //Transfer whole file
    //Standard_Integer num = reader.TransferRoots();

    Standard_Integer NbTrans = reader.TransferRoots();
    TopoDS_Shape result = reader.OneShape();
    TopoDS_Shape shape = reader.Shape();

    std::cout << "NbRoots / NbTrans" << std::endl;
    cout << NbRoots << endl;
    cout << NbTrans << endl;
    //cout << num << endl;

	processShape(result);
	processShape(shape);

    return 0;
}

int readIges() {
	IGESControl_Reader reader;
	IFSelect_ReturnStatus stat = reader.ReadFile(igesFileName.c_str());

	IFSelect_PrintCount mode = IFSelect_ListByItem;
	std::cout << "reader.PrintCheckLoad(false, mode)" << std::endl;
	reader.PrintCheckLoad(false, mode);

	Standard_Integer NbRoots = reader.NbRootsForTransfer(); //Transfer whole file
	Standard_Integer NbTrans = reader.TransferRoots();
	TopoDS_Shape result = reader.OneShape();

	processShape(result);

	return 0;
}

int main(int , char **) {

	std::cout << std::endl 
		<< "-----------" << std::endl
		<< "importStep:" << std::endl;

	importStep();

	std::cout << std::endl 
		<< "----------------" << std::endl
		<< "importStepParts:" << std::endl;

	importStepParts();

	std::cout << std::endl
		<< "---------" << std::endl
		<< "readIges:" << std::endl;

	readIges();

	std::cout << std::endl
		<< "---------" << std::endl
		<< "readStep:" << std::endl;

	readStep();

	// Wait for key press
	std::cout << std::endl
		<< "Press any key to continue ...";

	getchar();

    return 0;
}
