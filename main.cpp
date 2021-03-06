#include <iostream>
#include <fstream>
#include <map>
#include <memory>

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
#include <TDocStd_Document.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS.hxx>
#include <BRep_Builder.hxx>
#include <Quantity_Color.hxx>

const std::string dataDirectory = "c:\\Source\\ModelConverter\\src\\data\\";
const std::string stepFileName = dataDirectory + "impeller.STEP";
const std::string igesFileName = dataDirectory + "impeller.IGS";

void tesselateShape(TopoDS_Shape& shape) {
	double deflection = 0.1;
	BRepMesh_IncrementalMesh(shape, deflection);
}

void printShape(TopoDS_Shape& shape, std::ostream& totalsOutputStream, std::ostream& vertexOutputStream) {

	unsigned counter = 0;
	TopExp_Explorer ex;

	counter = 0;
	for (ex.Init(shape, TopAbs_VERTEX); ex.More(); ex.Next()) {
		++counter;

		TopoDS_Vertex vertex = TopoDS::Vertex(ex.Current());
		gp_Pnt point = BRep_Tool::Pnt(vertex);
		vertexOutputStream << "Vertex " << counter << ": X: " << point.X() << " - Y:" << point.Y() << " - Z: " << point.Z() << std::endl;
	}
	totalsOutputStream << "STEP: Load vertex: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_FACE); ex.More(); ex.Next()) {
		++counter;
	}
	totalsOutputStream << "STEP: Load face: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_EDGE); ex.More(); ex.Next()) {
		++counter;
	}
	totalsOutputStream << "STEP: Load edge: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_SOLID); ex.More(); ex.Next()) {
		++counter;
	}
	totalsOutputStream << "STEP: Load solid: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_SHELL); ex.More(); ex.Next()) {
		++counter;
	}
	totalsOutputStream << "STEP: Load shell: " << counter << std::endl;
}

std::unique_ptr<XSControl_Reader> createStepReader() {
	return std::make_unique<STEPControl_Reader>();
}

std::unique_ptr<XSControl_Reader> createIgesReader() {
	return std::make_unique<IGESControl_Reader>();
}

int convertShapeToMesh(const std::string& filename, std::unique_ptr<XSControl_Reader> reader) {
    IFSelect_ReturnStatus stat = reader->ReadFile(filename.c_str());
    if (stat != IFSelect_RetDone) {
        std::cout << "Error reading file '" << filename << "'" << std::endl;
        return 1;
    }

    reader->TransferRoots();
    TopoDS_Shape shape = reader->OneShape();

	tesselateShape(shape);

	std::string	outputVerticesFilename = filename + ".vertices";
	std::ofstream outputVerticesStream(outputVerticesFilename);
	printShape(shape, std::cout, outputVerticesStream);

    return 0;
}

int main(int , char **) {

	std::cout << std::endl
		<< "---------" << std::endl
		<< "readIges:" << std::endl;

	convertShapeToMesh(
		igesFileName,
		createIgesReader()
		);

	std::cout << std::endl
		<< "---------" << std::endl
		<< "readStep:" << std::endl;

	convertShapeToMesh(
		stepFileName,
		createStepReader()
		);

	// Wait for key press
	std::cout << std::endl
		<< "Press any key to continue ...";

	getchar();

    return 0;
}
