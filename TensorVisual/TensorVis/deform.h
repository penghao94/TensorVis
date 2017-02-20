#pragma once
#ifndef DEFORM_H_
#define DEFORM_H_
#include <iostream>
#include <Eigen/core>
namespace tev {
	bool scaled(Eigen::MatrixXd &S, Eigen::MatrixXd &O, Eigen::MatrixXd &N);
	bool rotate(Eigen::MatrixXd &R, Eigen::MatrixXd &O, Eigen::MatrixXd &N);
	bool translate(Eigen::MatrixXd &T, Eigen::MatrixXd &O, Eigen::MatrixXd &N);
	bool deform(Eigen::MatrixXd &V, Eigen::MatrixXd &Ten, Eigen::MatrixXd &Vn, Eigen::MatrixXi &Fn, Eigen::MatrixXd &D);
}
#endif // !DEFORM_H_

