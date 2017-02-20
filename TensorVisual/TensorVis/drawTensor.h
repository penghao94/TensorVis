#pragma once
#ifndef DRAWTENSOR_H_
#define DRAWTENSOR_H_
#include <iostream>
#include <igl/viewer/Viewer.h>
#include <Eigen/core>
namespace tev {
	bool drawTensor(
		igl::viewer::Viewer &viewer,
		const std::string axis,
		double accuracy,
		int radom,
		int layer,
		Eigen::MatrixXd &V,
		Eigen::MatrixXd &T,
		bool isAccuracy
	);
}
#endif // !DRAWTENSOR_H_

