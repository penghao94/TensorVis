#pragma once
#ifndef SLICE_H_
#define SLICE_H_
#include<iostream>
#include<Eigen/core>
namespace tev {
	bool slice(const int axis, double accuracy, int level, Eigen::MatrixXd &V, Eigen::MatrixXd &T, Eigen::MatrixXd &Vn, Eigen::MatrixXd &Tn);
	bool slice(const int axis, Eigen::MatrixXd &V, Eigen::MatrixXd &T, Eigen::MatrixXd &Vn, Eigen::MatrixXd &Vlist,Eigen::MatrixXd &Tn);
	bool slice(const int axis, Eigen::MatrixXd &V, Eigen::MatrixXi &matV);
}
#endif // !SLICE_H_
