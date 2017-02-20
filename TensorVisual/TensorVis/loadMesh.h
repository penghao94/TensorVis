#pragma once
#ifndef LOADMESH_H_
#define LOADMESH_H_
#include<iostream>
#include<Eigen/core>
namespace tev {
	bool loadMesh(Eigen::MatrixXd &V, Eigen::MatrixXi &F, Eigen::MatrixXd &S, Eigen::MatrixXd &T);
	bool loadMesh(const std::string filename, Eigen::MatrixXd &V, Eigen::MatrixXi &F, Eigen::MatrixXd &S, Eigen::MatrixXd &T);
}
#endif // !LOADMESH_H_

