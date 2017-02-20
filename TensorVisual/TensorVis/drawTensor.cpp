#include "drawTensor.h"
#include "slice.h"
#include "deform.h"
#include "jet_tensor.h"
using namespace std;

bool tev::drawTensor(igl::viewer::Viewer & viewer,
	const std::string axis, 
	double accuracy, 
	int radom, 
	int layer,
	Eigen::MatrixXd & V, 
	Eigen::MatrixXd & T,
	bool isAccuracy)
{
	cout << "-------Tensor Information------" << endl;
	cout << " Axis is:      " << axis << endl;
	cout << " Layer is:     " << layer << endl;
	cout << " Accuracy is:  " << accuracy << endl;
	cout << " Radom is:     " << radom << endl;
	if (isAccuracy)
		cout << " Is Accuracy:  YES" << endl;
	else
		cout << " Is Accuracy:  NO" << endl;
	cout << "--------------------------------" << endl;
	viewer.core.show_lines = false;
	Eigen::MatrixXd  Vn;
	Eigen::MatrixXi  Fn;
	Eigen::MatrixXd _V;
	Eigen::MatrixXd _T;
	Eigen::MatrixXd temp_V;
	Eigen::MatrixXd temp_T;
	Eigen::MatrixXd D;
	Eigen::MatrixXd color_D;
	int AXIS;

	if (axis == "X") {
		AXIS = 0;
	}
	else if (axis == "Y") {
		AXIS = 1;
	}
	else if (axis == "Z") {
		AXIS = 2;
	}
	assert(V.rows() != 0 && T.rows() != 0);
	if (isAccuracy) {
		tev::slice(AXIS, accuracy, layer, V, T, _V, _T);
	}
	else {
		tev::slice(AXIS, 1, layer, V, T, temp_V, temp_T);

		cout << radom << endl;
		if (temp_V.rows() > radom ){
			for (int i = 0; i < radom; i++) {
				int num = rand() % temp_V.rows();
				_V.row(i) << temp_V.row(num);
				_T.row(i) << temp_T.row(num);
			}
		}
		else {
			_V = temp_V;
			_T = temp_T;
		}
	}
	tev::deform(_V, _T, Vn, Fn, D);
	viewer.data.clear();
	viewer.data.set_mesh(Vn, Fn);
	
	tev::jet(D.col(0), D.minCoeff(), D.maxCoeff(), color_D);
	viewer.data.set_colors(color_D);
	Vn.resize(0, 0);
	Fn.resize(0, 0);
	_V.resize(0, 0);
	_T.resize(0, 0);
	temp_T.resize(0, 0);
	temp_V.resize(0, 0);
	D.resize(0, 0);
	color_D.resize(0, 0);
	return true;
	
}
