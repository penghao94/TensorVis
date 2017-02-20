#include "slice.h"
#include "igl/sort.h"

/*
this function is used to slice all
*/
using namespace std;
bool tev::slice(const int axis, double accuracy, int level, Eigen::MatrixXd & V, Eigen::MatrixXd & T, Eigen::MatrixXd & Vn, Eigen::MatrixXd & Tn)
{
	bool success;
	level -= 1;
	Eigen::MatrixXd Vt, Tt, Vs, Vt2, Tt2;
	slice(axis, V, T, Vt, Vs,Tt);

	if (level > Vs.rows() - 1) {
		std::cout << "The last layer is:" << Vs.rows() << std::endl;
		level = Vs.rows() - 1;
	}
	//printf("The current layer is: %d\n", level);
	
	if (level == Vs.rows() - 1) {
		Vt2 = Vt.block(Vs(level, 1), 0, Vt.rows() - Vs(level, 1), Vt.cols());
	}
	else
		Vt2 = Vt.block(Vs(level, 1), 0, Vs(level + 1, 1) - Vs(level, 1), Vt.cols());
	if (level == Vs.rows() - 1) {
		Tt2 = Tt.block(Vs(level, 1), 0, Tt.rows() - Vs(level, 1), Tt.cols());
	}

	else
		Tt2 = Tt.block(Vs(level, 1), 0, Vs(level + 1, 1) - Vs(level, 1), Tt.cols());
	
	Eigen::MatrixXi matV;
	slice(axis, Vt2, matV);
	int row = floor(matV.rows()*accuracy);
	int col = floor(matV.cols()*accuracy);
	double vacc = 1 / accuracy;
	Vn.resize(0, 3);
	Tn.resize(0, 6);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int value = matV(round(vacc*i), round(vacc*j));
			if (value != -1000000) {
				Vn.conservativeResize(Vn.rows() + 1, 3);
				Tn.conservativeResize(Tn.rows() + 1, 6);
				Vn.row(Vn.rows() - 1) = Vt2.row(value);
				Tn.row(Tn.rows() - 1) = Tt2.row(value);
			}

		}
	}
	Vt.resize(0, 0);
	Tt.resize(0, 0);
	Vs.resize(0, 0);
	Vt2.resize(0, 0);
	Tt2.resize(0,0);
	matV.resize(0, 0);
	return true;
}
/*
this function is used to slice model into layer
*/
bool tev::slice(const int axis, Eigen::MatrixXd & V, Eigen::MatrixXd & T, Eigen::MatrixXd & Vn, Eigen::MatrixXd & Vlist, Eigen::MatrixXd & Tn)
{
	Eigen::MatrixXd Y;
	Eigen::MatrixXi I;

	Eigen::MatrixXd AXIS = V.col(axis);
	//printf("The tensor slice axis is: %d\n", axis);
	Vn.resize(V.rows(), V.cols());
	Tn.resize(T.rows(), T.cols());
	igl::sort(AXIS, 1, true, Y, I);

	Vlist.resize(1, 2);
	Vlist.row(0) << Y(0, 0), 0;
	Vn.row(0) << V.row(I(0, 0));
	Tn.row(0) << T.row(I(0, 0));

	for (int i = 1; i < V.rows(); i++) {
		if (Y(i, 0) > Y(i - 1, 0)) {
			Vlist.conservativeResize(Vlist.rows() + 1, 2);
			Vlist.row(Vlist.rows() - 1) << Y(i, 0), i;
		}
		Vn.row(i) << V.row(I(i, 0));
		Tn.row(i) << T.row(I(i, 0));

	}
	return true;
	Y.resize(0, 0);
	I.resize(0, 0);
	AXIS.resize(0, 0);
}
/*
this function is used to slice layer
*/
bool tev::slice(const int axis, Eigen::MatrixXd & V, Eigen::MatrixXi & matV)
{
	int MaxC = 0;
	Eigen::MatrixXd Y;
	Eigen::MatrixXi I;
	Eigen::MatrixXd AXIS, Vs;
	switch (axis) {
	case 0:
		AXIS = V.col(1);
		break;
	case 1:
		AXIS = V.col(0);
		break;
	case 2:
		AXIS = V.col(0);
		break;
	}
	igl::sort(AXIS, 1, true, Y, I);
	
	Vs.resize(1, 2);
	Vs.row(0) << Y(0, 0), 0;
	 
	for (int i = 1; i < V.rows(); i++) {
		if (Y(i, 0) > Y(i - 1, 0)) {
			Vs.conservativeResize(Vs.rows() + 1, 2);
			Vs.row(Vs.rows() - 1) << Y(i, 0), i;
		}
	}
	Vs.conservativeResize(Vs.rows() + 1, 2);
	Vs.row(Vs.rows()-1) << Y(V.rows()-1, 0), V.rows();
	

	for (int i = 1; i < Vs.rows(); i++) {
		if ((Vs(i, 1) - Vs(i-1, 1)) > MaxC)
			MaxC = int(Vs(i, 1) - Vs(i-1, 1));
	}
	matV.setOnes(Vs.rows()-1, MaxC);
	
	matV *= -1000000;
	for (int i = 0; i < Vs.rows(); i++) {
		for (int j = 0; j < (Vs(i + 1, 1) - Vs(i, 1)); j++) {
			matV(i, j) = I(int(Vs(i, 1) + j));
			
		}
		
	}
	return true;
}
