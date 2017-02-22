#pragma once
#ifndef BATCHPRINT_H_
#define BATCHPRINT_H_
#include <iostream>
#include <igl\viewer\Viewer.h>
#include "loadMesh.h"
namespace tev {
	bool batch_print(igl::viewer::Viewer &viewer, 
		Eigen::MatrixXd &V,
		Eigen::MatrixXi &F,
		Eigen::MatrixXd &S,
		Eigen::MatrixXd &T,
		double SCALAR_MAX,
		const std::string axis,
		double accuracy,
		int radom,
		int layer,
		bool isaccuracy
		);
	bool batch_print(igl::viewer::Viewer &viewer,
		const std::string batch, 
		Eigen::MatrixXd &V,
		Eigen::MatrixXi &F,
		Eigen::MatrixXd &S,
		Eigen::MatrixXd &T,
		double SCALAR_MAX,
		const std::string axis,
		double accuracy,
		int radom,
		int layer,
		bool isaccuracy
	);
}
#endif // !BATCHPRINT_H_

