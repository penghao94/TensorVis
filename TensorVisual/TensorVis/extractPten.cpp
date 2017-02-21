#include "ExtractPten.h"
#include "Vonmises.h"
void tev::extractPten(std::string file)
{
	int nodecount = 0;
	int elecount = 0;
	int tensorcount = 0;
	int index = 0;
	double** ntensor;
	double** etensor;
	int** enode;
	std::string file_n = file + "_e.node";
	std::string file_e = file + "_e.ele";
	std::string file_t = file + "g.ten";
	std::string file_s = file + "g.sca";
	std::string file_pt = file + "g.pten";
	std::string file_ps = file + "g.psca";
	const char* node_o = file_n.c_str();
	const char* ele_o = file_e.c_str();
	const char* ten_o = file_t.c_str();
	const char* sca_o = file_s.c_str();
	const char* pten_n = file_pt.c_str();
	const char* psca_n = file_ps.c_str();
	FILE *node_r = fopen(node_o, "r");
	if (node_r == (FILE*)NULL) {
		printf("Cnanot read standard node file.\n");
		return;
	}
	FILE *ele_r = fopen(ele_o, "r");
	if (ele_r == (FILE*)NULL) {
		printf("Cnanot read standard element file.\n");
		return;
	}
	FILE *ten_r = fopen(ten_o, "r");
	if (ten_r == (FILE*)NULL) {
		printf("Cnanot read standard tensor file.\n");
		return;
	}
	FILE *pten_w = fopen(pten_n, "w");
	if (pten_w == (FILE*)NULL) {
		printf("Cannot write point tensor file.\n");
		return;
	}
	FILE *psca_w = fopen(psca_n, "w");
	if (psca_w == (FILE*)NULL) {
		printf("Cannot write point scalar file.\n");
		return;
	}

	fscanf(node_r, "%d  3  0  0\n", &nodecount);
	fscanf(ele_r, "%d  8  0\n", &elecount);
	fscanf(ten_r, "%d 6\n", &tensorcount);
	fprintf(pten_w, "%d %d\n", nodecount, 6);
	fprintf(psca_w, "%d %d\n", nodecount, 1);

	ntensor = new double*[nodecount];
	etensor = new double*[tensorcount];
	enode = new int*[elecount];

	for (int i = 0; i < nodecount; i++) {
		ntensor[i] = new double[7];
		ntensor[i][0] = ntensor[i][1] = ntensor[i][2] = ntensor[i][3] = ntensor[i][4] = ntensor[i][5] = ntensor[i][6] = 0;
	}

	for (int j = 0; j < elecount; j++) {
		enode[j] = new int[9];
		fscanf(ele_r, "%d %d %d %d %d %d %d %d %d %d\n",
			&index, &enode[j][0], &enode[j][1], &enode[j][2], &enode[j][3], &enode[j][4], &enode[j][5], &enode[j][6], &enode[j][7], &enode[j][8]);
	}

	for (int k = 0; k < tensorcount; k++) {
		etensor[k] = new double[6];
		fscanf(ten_r, "%lf %lf %lf %lf %lf %lf\n",
			&etensor[k][0], &etensor[k][1], &etensor[k][2], &etensor[k][3], &etensor[k][4], &etensor[k][5]);
	}

	for (int i = 0; i < elecount; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 6; k++) {
				ntensor[enode[i][j]][k] += etensor[enode[i][8]][k];
			}
			ntensor[enode[i][j]][6]++;
		}
	}

	for (int i = 0; i < nodecount; i++) {
		for (int j = 0; j < 6; j++) {
			ntensor[i][j] /= ntensor[i][6];
		}
		fprintf(pten_w, "%lf %lf %lf %lf %lf %lf\n", ntensor[i][0], ntensor[i][1], ntensor[i][2], ntensor[i][3], ntensor[i][4], ntensor[i][5]);
		fprintf(psca_w, "%lf\n", tev::Vonmises(ntensor[i][0], ntensor[i][1], ntensor[i][2], ntensor[i][3], ntensor[i][4], ntensor[i][5]));
	}

	for (int i = 0; i < nodecount; i++) {
		delete(ntensor[i]);
	}
	delete(ntensor);

	for (int j = 0; j < elecount; j++) {
		delete(enode[j]);
	}
	delete(enode);

	for (int k = 0; k < tensorcount; k++) {
		delete(etensor[k]);
	}
	delete(etensor);

	fclose(node_r);
	fclose(ele_r);
	fclose(ten_r);
	fclose(pten_w);
	fclose(psca_w);
	remove(ten_o);
	remove(sca_o);
	printf("Write point tensor file to %s\n", pten_n);
	printf("Write point scalar file to %s\n", psca_n);
}
