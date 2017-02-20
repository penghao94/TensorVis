#include "loadMesh.h"

#include "readTensor.h"
#include <igl/file_dialog_open.h>
#include <igl/readOFF.h>
bool tev::loadMesh(Eigen::MatrixXd & V, Eigen::MatrixXi & F, Eigen::MatrixXd & S, Eigen::MatrixXd & T)
{
	char path_buffer[_MAX_PATH];
	char path_mesh[_MAX_PATH];
	char path_scalar[_MAX_PATH];
	char path_tensor[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	std::string filename = igl::file_dialog_open();
	if (filename.empty()) {
		std::cout << "Loading file first..." << std::endl;
		return false;
	}
	else {
		//cout << filename << endl;
		char *file = const_cast<char *>(filename.c_str());
		_splitpath(file, drive, dir, fname, ext);

		_makepath(path_mesh, drive, dir, fname, ".off");
		_makepath(path_scalar, drive, dir, fname, ".psca");
		_makepath(path_tensor, drive, dir, fname, ".pten");
		//cout << path_color1 << endl;
		//cout << path_color2 << endl;

		FILE * file1 = fopen(path_mesh, "r");
		FILE * file2 = fopen(path_scalar, "r");
		FILE * file3 = fopen(path_tensor, "r");
		if (file1 == (FILE*)NULL) {
			std::cout << "Mesh info must load...";
			return false;
		}
		else {
			igl::readOFF(path_mesh, V, F);
			if (file2 == (FILE*)NULL) {
				std::cout << "Scalar Field loss..." << std::endl;
				S.resize(0, 1);
			}
			else
				tev::readTensor(path_scalar,S);
			if (file3 == (FILE*)NULL) {
				std::cout << "Tensor Field loss..." << std::endl;
				T.resize(0, 6);
			}
			else
				tev::readTensor(path_tensor, T);
			return true;
		}
		fclose(file1);
		fclose(file2);
		fclose(file3);

	}
}

bool tev::loadMesh(const std::string filename, Eigen::MatrixXd & V, Eigen::MatrixXi & F, Eigen::MatrixXd & S, Eigen::MatrixXd & T)
{
	char path_buffer[_MAX_PATH];
	char path_mesh[_MAX_PATH];
	char path_scalar[_MAX_PATH];
	char path_tensor[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	if (filename.empty()) {
		std::cout << "Loading file first..." << std::endl;
		return false;
	}
	else {
		//cout << filename << endl;
		std::string path = filename + "g.off";
		char *file = const_cast<char *>(path.c_str());
		_splitpath(file, drive, dir, fname, ext);

		_makepath(path_mesh, drive, dir, fname, ".off");
		_makepath(path_scalar, drive, dir, fname, ".psca");
		_makepath(path_tensor, drive, dir, fname, ".pten");
		//cout << path_color1 << endl;
		//cout << path_color2 << endl;

		FILE * file1 = fopen(path_mesh, "r");
		FILE * file2 = fopen(path_scalar, "r");
		FILE * file3 = fopen(path_tensor, "r");
		if (file1 == (FILE*)NULL) {
			std::cout << "Mesh info must load...";
			return false;
		}
		else {
			igl::readOFF(path_mesh, V, F);
			if (file2 == (FILE*)NULL) {
				std::cout << "Scalar Field loss..." << std::endl;
				S.resize(0, 1);
			}
			else
				tev::readTensor(path_scalar, S);
			if (file3 == (FILE*)NULL) {
				std::cout << "Tensor Field loss..." << std::endl;
				T.resize(0, 6);
			}
			else
				tev::readTensor(path_tensor, T);
			return true;
		}
		fclose(file1);
		fclose(file2);
		fclose(file3);

	}
}
