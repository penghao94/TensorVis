#include <igl/viewer/Viewer.h>
#include <igl/file_dialog_save.h>
#include <nanogui/formhelper.h>
#include <nanogui/screen.h>
#include <igl/png/readPNG.h>

#include "loadMesh.h"
#include "saveMesh.h"
#include "jet_tensor.h"
#include "drawTensor.h"
#include "printPNG.h"
#include "batch_ten.h"
#include <iostream>
using namespace std;
//init the viewer
igl::viewer::Viewer viewer;

/*
V the vertical matrics of mesh
F the facet matrics of mesh
S the scalar field matrics of mesh
T the tensor field matrics of mesh
C the color of scalar field
*/
Eigen::MatrixXd V;
Eigen::MatrixXi F;
Eigen::MatrixXd S;
Eigen::MatrixXd T;
Eigen::MatrixXd C;
/*
SCALAR_MIN the min value of scalar field
SCALAR_MAX the max value of scalar field
*/
double SCALAR_MIN = 0.0;
double SCALAR_MAX = 20000000.0;
/*
Parameters of tensor field
AXIS		the direction of tensor field
LAYER		the layer of tensor field
ACCURACY	the accuracy of simplifing tensor field
RADOM		the number of radom seeds of tensor field
*/
string AXIS = "X";
int LAYER = 1;
double ACCURACY = 0.5;
int RADOM = 500;
bool isAccuracy = true;
int main(int argc, char *argv[])
{
	// Extend viewer menu
	viewer.callback_init = [&](igl::viewer::Viewer& viewer)
	{
		// Add an additional menu window
		viewer.ngui->addWindow(Eigen::Vector2i(230, 10), "Tensor Vis");

		/*
		Add a group of I/O operator
		*/
		viewer.ngui->addGroup("IO options");

		//Add load mesh button
		viewer.ngui->addButton("Load Mesh", [&]() {

			viewer.data.clear();
			tev::loadMesh(V,F,S,T);//load mesh data
			tev::jet(S.col(0), SCALAR_MIN, SCALAR_MAX, C);//calculate scalar field color

			cout << "--------Mesh Information--------" << endl;
			cout << "Vertics:" << "  " << V.rows() << "  " << V.cols() << endl;
			cout << "Facets:" << "  " << F.rows() << "  " << V.cols() << endl;
			cout << "Scalar Field:" << "  " << S.rows() << "  " << S.cols() << endl;
			cout << "Tensor Field:" << "  " << T.rows() << "  " << T.cols() << endl;
			cout << "--------------------------------" << endl;
			//set mesh and scalar color
			viewer.data.set_mesh(V, F);
			viewer.data.set_colors(C);
		});

		//Add save mesh button
		viewer.ngui->addButton("Save Mesh", [&]() {
			string output = "";
			output = igl::file_dialog_save();
			if (output != "") {
				tev::saveMesh(output, V, F, C);
			}
		});
		/*
		Add a group to reset color
		*/
		viewer.ngui->addGroup("Scalar Field");
		viewer.ngui->addVariable<double>("Treshold", [&](double SCALAR_MAX)
		{
			if (V.rows() != 0) {
				tev::jet(S.col(0), SCALAR_MIN, SCALAR_MAX, C);//calculate scalar field color
				viewer.data.set_colors(C);
			}
				
		}, [&]()
		{
			return SCALAR_MAX;
		});

		viewer.ngui->addButton("Reset Scalar", [&]() {
			if (V.rows() != 0) {
				viewer.data.clear();
				viewer.data.set_mesh(V, F);
				viewer.data.set_colors(C);
			}
			
		});
		/*
		Add a group of tensor field
		*/
		viewer.ngui->addGroup("Tensor Field");

		viewer.ngui->addVariable<std::string>("Axis", [&](std::string axis)
		{
			AXIS = axis;
			if (V.rows() != 0)
				tev::drawTensor(viewer, AXIS, ACCURACY, RADOM, LAYER, V, T, isAccuracy);
		}, [&]()
		{
			
			return AXIS;
		});

		viewer.ngui->addVariable<int>("Layer", [&](int layer)
		{
			LAYER = layer;
			if (V.rows() != 0)
				tev::drawTensor(viewer, AXIS, ACCURACY, RADOM, LAYER, V, T, isAccuracy);
		}, [&]()
		{
			return LAYER;
		});

		viewer.ngui->addVariable<double>("Accuracy", [&](double accuracy)
		{
			isAccuracy = true;
			ACCURACY = accuracy;
			if (V.rows() != 0)
				tev::drawTensor(viewer, AXIS, ACCURACY, RADOM, LAYER, V, T, isAccuracy);
		}, [&]()
		{
			return ACCURACY;
		});

		viewer.ngui->addVariable<int>("Radom", [&](int radom)
		{
			isAccuracy = false;
			RADOM=radom;
			if (V.rows() != 0)
				tev::drawTensor(viewer, AXIS, ACCURACY, RADOM, LAYER, V, T, isAccuracy);
		}, [&]()
		{
			return RADOM;
		});

		viewer.ngui->addButton("Reset Tensor", [&]() {
			if (V.rows() != 0)
				tev::drawTensor(viewer, AXIS, ACCURACY, RADOM, LAYER, V, T, isAccuracy);
		});

		/*
		Add a group of print and batch
		*/
		viewer.ngui->addGroup("Print and batch");

		viewer.ngui->addButton("Print Png", [&]() {
			tev::printPNG(viewer);
		});
		viewer.ngui->addButton("Batch Tensor ", [&]() {
			tev::batch_ten();
		});
		// Generate menu
		viewer.screen->performLayout();

		return false;
	};
  viewer.launch();
  
}
