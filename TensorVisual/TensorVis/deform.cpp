#include "deform.h"
#include <Eigen/Core>
#include<igl\readOFF.h>
#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include<string.h>
#include <math.h>
#include <iostream>
#include<windows.h>
#include<stdio.h>
#include "atlstr.h "

using namespace std;
using namespace Eigen;

bool tev::scaled(Eigen::MatrixXd & S, Eigen::MatrixXd & O, Eigen::MatrixXd & N)
{
	N.resize(O.rows(), 3);
	N = O*S;
	N = N / 100;
	return true;
}

bool tev::rotate(Eigen::MatrixXd & R, Eigen::MatrixXd & O, Eigen::MatrixXd & N)
{
	N = O*R.transpose();
	return true;
}

bool tev::translate(Eigen::MatrixXd & T, Eigen::MatrixXd & O, Eigen::MatrixXd & N)
{
	N.resize(O.rows(), 3);
	N = O.array() + T.array();
	return true;

}

bool tev::deform(Eigen::MatrixXd & V, Eigen::MatrixXd & Ten, Eigen::MatrixXd & Vn, Eigen::MatrixXi & Fn, Eigen::MatrixXd & D)
{
	Eigen::MatrixXd Vs, S, R, T, evalue, evector, Vc;
	Eigen::MatrixXi Fs;
	Eigen::MatrixXd tensor(3, 3);
	Vn.resize(0, 3);
	Fn.resize(0, 3);
	D.resize(0, 1);
	TCHAR szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;//删除文件名，只获得路径字串
	CString str_url = szFilePath;
	string str(str_url.GetBuffer(str_url.GetLength()));
	igl::readOFF(str + "sphere.off", Vs, Fs);
	int vrow = Vs.rows();
	Eigen::MatrixXi VROW = RowVector3i(vrow, vrow, vrow).replicate(Fs.rows(), 1);
	for (int i = 0; i < V.rows(); i++) {
		int indexV = Vn.rows();
		int indexF = Fn.rows();
		int indexD = D.rows();
		Vn.conservativeResize(Vn.rows() + Vs.rows(), 3);
		Fn.conservativeResize(Fn.rows() + Fs.rows(), 3);
		D.conservativeResize(D.rows() + Vs.rows(), 1);

		tensor << Ten(i, 0), Ten(i, 3), Ten(i, 5),
			Ten(i, 3), Ten(i, 1), Ten(i, 4),
			Ten(i, 5), Ten(i, 4), Ten(i, 2);
		//Eigen value and Eigen Vector
		Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> es(tensor);
		Eigen::Vector3d eigenvalue = es.eigenvalues();

		Eigen::Vector3d absValue(fabs(eigenvalue(0)), fabs(eigenvalue(1)), fabs(eigenvalue(2)));
		double minAxis = absValue.minCoeff();
		Eigen::Vector3d sValue = absValue;
		//double diff = sqrt((sValue.array() - sValue.mean()).matrix().squaredNorm());
		//double diff = log(sValue.maxCoeff() - sValue.minCoeff()+1);
		//cout << diff << endl;
		//cout <<"absolute" <<endl<<absValue << endl;
		//cout << "value" << endl << eigenvalue << endl;
		Eigen::MatrixXd evalue = absValue.asDiagonal();
		evalue /= minAxis;
		evalue(0, 0) = log(evalue(0, 0)) + 1;
		evalue(1, 1) = log(evalue(1, 1)) + 1;
		evalue(2, 2) = log(evalue(2, 2)) + 1;
		double up = sqrt((sValue.array() - sValue.mean()).matrix().squaredNorm());
		double down = sqrt(absValue.squaredNorm());
		double diff = sqrt(3.0 / 2.0)*up / down;
		//cout << diff << endl;
		//cout << "evalue" << endl << evalue << endl;
		evector = es.eigenvectors();
		//Deform
		Eigen::MatrixXd rotat(3, 3);
		rotat.col(0) << evector.col(0);
		rotat.col(1) << evector.col(1);
		Eigen::Vector3d col1, col2;
		col1 << evector.col(0);
		col2 << evector.col(1);
		rotat.col(2) << col1.cross(col2);
		//cout << "evector:" << endl << rotat << endl;
		scaled(evalue, Vs, S);
		//rotate(evector, S, R);
		rotate(rotat, S, R);
		Vc = V.row(i).replicate(Vs.rows(), 1);
		translate(Vc, R, T);
		for (int j = 0; j < Vs.rows(); j++) {
			Vn.row(indexV + j) << T.row(j);
			D.row(indexD + j) << diff;
			//cout << Vn.row(indexV + j) << endl;
		}
		for (int k = 0; k < Fs.rows(); k++) {
			Fn.row(indexF + k) = Fs.row(k);
			//cout << Fn.row(indexF + k) << endl;
		}
		Fs += VROW;
	}
	Vs.resize(0, 0);
	S.resize(0, 0);
	R.resize(0, 0);
	T.resize(0, 0);
	evalue.resize(0, 0);
	evector.resize(0, 0);
	Vc.resize(0,0);
	return true;
}
