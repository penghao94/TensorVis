#pragma once
#ifndef SAVEMESH_H_
#define SAVEMESH_H_
#include <Eigen/Core>
#include <string>

namespace tev {
	bool saveMesh(const std::string str, Eigen::MatrixXd &V, Eigen::MatrixXi &F);
	bool saveMesh(const std::string str,Eigen::MatrixXd &V,Eigen::MatrixXi &F,Eigen::MatrixXd &C);
}
#endif // !SAVEMESH_H_
