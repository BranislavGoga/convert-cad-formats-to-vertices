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

    reader.NbRootsForTransfer(); //Transfer whole file
    reader.TransferRoots();
    TopoDS_Shape shape = reader.OneShape();

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
