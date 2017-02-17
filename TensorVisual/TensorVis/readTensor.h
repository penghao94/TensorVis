#pragma once
#ifndef READTENSOR_H_
#define READTENSOR_H_
#include <iostream>
#include <vector>
#include <Eigen/core>
namespace tev {
	void readTensor(const std::string Tensor_file_name, std::vector<std::vector<double>>&T);
	void readTensor(const std::string str, Eigen::MatrixXd &T);
}
#endif // !READTENSOR_H_

