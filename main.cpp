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

void printShape(TopoDS_Shape& shape, std::ostream& outputStream) {

	unsigned counter = 0;
	TopExp_Explorer ex;

	counter = 0;
	for (ex.Init(shape, TopAbs_VERTEX); ex.More(); ex.Next()) {
		++counter;

		TopoDS_Vertex vertex = TopoDS::Vertex(ex.Current());
		gp_Pnt point = BRep_Tool::Pnt(vertex);
		outputStream << "Vertex " << counter << ": X: " << point.X() << " - Y:" << point.Y() << " - Z: " << point.Z() << std::endl;
	}
	outputStream << "STEP: Load vertex: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_FACE); ex.More(); ex.Next()) {
		++counter;
	}
	outputStream << "STEP: Load face: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_EDGE); ex.More(); ex.Next()) {
		++counter;
	}
	outputStream << "STEP: Load edge: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_SOLID); ex.More(); ex.Next()) {
		++counter;
	}
	outputStream << "STEP: Load solid: " << counter << std::endl;

	counter = 0;
	for (ex.Init(shape, TopAbs_SHELL); ex.More(); ex.Next()) {
		++counter;
	}
	outputStream << "STEP: Load shell: " << counter << std::endl;
}

void tesselateShape(TopoDS_Shape& shape) {
	double deflection = 0.1;
	BRepMesh_IncrementalMesh(shape, deflection);
}

XSControl_Reader	createStepReader()
{
	return STEPControl_Reader();
}

XSControl_Reader	createIgesReader()
{
	return IGESControl_Reader();
}

TopoDS_Shape readShape(const std::string& filename, XSControl_Reader& reader) {
	IFSelect_ReturnStatus stat = reader.ReadFile(filename.c_str());
	if (stat != IFSelect_RetDone) {
		std::string message = "Unable to read file '" + filename + "'";
		throw std::exception(message.c_str());
	}

	reader.NbRootsForTransfer(); //Transfer whole file
	reader.TransferRoots();
	return reader.OneShape();
}

void convertShapeToMesh(const std::string& filename, XSControl_Reader& reader) {
	std::cout << std::endl << 
		"Loading file '" << filename << "' ..." << std::endl;

	TopoDS_Shape shape = readShape(filename, reader);
	tesselateShape(shape);
	{
		const std::string	outputFilename = filename + ".vertices";

		std::cout << "Writing loaded vertices to '" << outputFilename << "' ..." << std::endl;

		std::ofstream	stepOutputStream(outputFilename);
		printShape(shape, stepOutputStream);
	}
}

int main(int , char **) {

	convertShapeToMesh(stepFileName, createStepReader());
	convertShapeToMesh(igesFileName, createIgesReader());

	// Wait for key press
	std::cout << std::endl
		<< "Press any key to continue ...";

	getchar();

    return 0;
}
