#include "saveMesh.h"
#include <cstdio>
#include <fstream>
bool tev::saveMesh(const std::string str, Eigen::MatrixXd & V, Eigen::MatrixXi & F)
{
	using namespace std;
	using namespace Eigen;
	assert(V.cols() == 3 && "V should have 3 columns");
	ofstream s(str);
	if (!s.is_open())
	{
		fprintf(stderr, "IOError: writeOFF() could not open %s\n", str.c_str());
		return false;
	}

	s <<
		"OFF\n" << V.rows() << " " << F.rows() << " 0\n" <<
		V.format(IOFormat(FullPrecision, DontAlignCols, " ", "\n", "", "", "", "\n")) <<
		(F.array()).format(IOFormat(FullPrecision, DontAlignCols, " ", "\n", "3 ", "", "", "\n"));
	return true;
}

bool tev::saveMesh(const std::string str, Eigen::MatrixXd & V, Eigen::MatrixXi & F, Eigen::MatrixXd & C)
{
	using namespace std;
	using namespace Eigen;
	assert(V.cols() == 3 && "V should have 3 columns");
	assert(C.cols() == 3 && "C should have 3 columns");

	if (V.rows() != C.rows())
	{
		fprintf(stderr, "IOError: writeOFF() Only color per vertex supported. V and C should have same size.\n");
		return false;
	}

	ofstream s(str);
	if (!s.is_open())
	{
		fprintf(stderr, "IOError: writeOFF() could not open %s\n", str.c_str());
		return false;
	}

	//Check if RGB values are in the range [0..1] or [0..255]
	int rgbScale = (C.maxCoeff() <= 1.0) ? 255 : 1;
	Eigen::MatrixXd iglRGB = rgbScale * C;

	s << "COFF\n" << V.rows() << " " << F.rows() << " 0\n";
	for (unsigned i = 0; i< V.rows(); i++)
	{
		s << V.row(i).format(IOFormat(FullPrecision, DontAlignCols, " ", " ", "", "", "", " "));
		s << iglRGB(i, 0) << " " << iglRGB(i, 1) << " " << iglRGB(i, 2) << " 255\n";
	}

	s << (F.array()).format(IOFormat(FullPrecision, DontAlignCols, " ", "\n", "3 ", "", "", "\n"));
	return true;
}
