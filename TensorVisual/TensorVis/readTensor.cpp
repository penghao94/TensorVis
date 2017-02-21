#include "readTensor.h"
#include "igl/list_to_matrix.h"
/*
this function is used to read tensor field file
*/
void tev::readTensor(const std::string Tensor_file_name, std::vector<std::vector<double>>& T)
{
	FILE * tensor_file = fopen(Tensor_file_name.c_str(), "r");
	if (NULL == tensor_file)
	{
		printf("IOError: %s could not be opened...\n", Tensor_file_name.c_str());
	}
	else {
		T.clear();
		int tenrow, tencol;
		int tenindex = 0;
		fscanf(tensor_file, "%d %d\n", &tenrow, &tencol);
		T.resize(tenrow);
		while (tenindex < tenrow) {

			if (tencol == 1) {
				std::vector<double> vertex;
				vertex.resize(tencol);
				fscanf(tensor_file, "%lf\n", &vertex[0]);
				T[tenindex] = vertex;
				//printf("%lf\n", vertex[0]);
			}
			else if (tencol == 6) {
				std::vector<double> vertex1;
				vertex1.resize(tencol);
				fscanf(tensor_file, "%lf %lf %lf %lf %lf %lf\n",
					&vertex1[0], &vertex1[1], &vertex1[2], &vertex1[3], &vertex1[4], &vertex1[5]);
				T[tenindex] = vertex1;
				//printf("%lf %lf %lf %lf %lf %lf\n", vertex1[0], vertex1[1], vertex1[2], vertex1[3], vertex1[4], vertex1[5]);
			}


			tenindex++;
		}
	}

}

void tev::readTensor(const std::string str, Eigen::MatrixXd & T)
{
	std::vector<std::vector<double>> T1;
	readTensor(str, T1);
	igl::list_to_matrix(T1, T);
}
