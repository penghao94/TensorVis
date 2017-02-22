#include "batch_print.h"
#include <igl\file_dialog_open.h>
#include "jet_tensor.h"
#include "printPNG.h"
#include "drawTensor.h"
bool tev::batch_print(igl::viewer::Viewer & viewer,
	Eigen::MatrixXd &V, 
	Eigen::MatrixXi &F, 
	Eigen::MatrixXd &S,
	Eigen::MatrixXd &T,
	double SCALAR_MAX,
	const std::string axis,
	double accuracy,
	int radom,
	int layer,
	bool isaccuracy)
{
	std::string batch = "";
	batch = igl::file_dialog_open();
	if (batch != "")
		batch_print(viewer,batch,V,F,S,T,SCALAR_MAX,axis,accuracy,radom,layer,isaccuracy);
	return true;
}

bool tev::batch_print(igl::viewer::Viewer & viewer, 
	const std::string file, 
	Eigen::MatrixXd &V,
	Eigen::MatrixXi &F, 
	Eigen::MatrixXd &S,
	Eigen::MatrixXd &T,
	double SCALAR_MAX,
	const std::string axis,
	double accuracy,
	int radom,
	int layer,
	bool isaccuracy)
{
	viewer.data.clear();
	std::cout << "-------Batch Print Information-------" << std::endl;
	Eigen::MatrixXd C;
	int num;
	int identity;
	char str[1024];
	const char* batchfile = file.c_str();
	FILE *batch = fopen(batchfile, "r");
	if (batch == NULL) {
		printf("Can not open batch file.\n");
		return false;
	}
	printf("Open batch file: %s\n", batchfile);
	fscanf(batch, "%d %d\n", &num, &identity);
	if (identity == 1) {
		fscanf(batch, ">> %s\n", &str);
	}
	printf("The count of file is: %d\n", num);
	for (int i = 0; i < num; i++) {
		viewer.data.clear();
		fscanf(batch, ">> %s\n", &str);
		printf("The %d file: %s\n", i + 1, str);
		std::string filename = str;
		tev::loadMesh(filename, V, F, S, T);
		viewer.data.set_mesh(V,F);
		tev::jet(S.col(0), 0, SCALAR_MAX, C);
		viewer.data.set_colors(C);
		tev::printPNG(viewer, filename + "-s.png");
		std::cout << "scalar Field:" << filename << "-s.png" << std::endl;
		viewer.data.clear();
		tev::drawTensor(viewer, axis, accuracy, radom, layer, V, T, isaccuracy);
		tev::printPNG(viewer, filename + "-t.png");
		std::cout << "Tensor Field:" << filename << "-t.png" << std::endl;
	}
	std::cout << "-------------------------------------" << std::endl;
	return true;
}


