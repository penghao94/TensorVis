#pragma once
#ifndef JET_H_
#define JET_H_
#include <iostream>
#include <Eigen/core>
namespace tev {
	void jet(const Eigen::VectorXd &Field, const double min, const double max, Eigen::MatrixXd &C);
	void jet(const double x_in, double &r, double &g, double &b);
}
#endif // !JET_H_

