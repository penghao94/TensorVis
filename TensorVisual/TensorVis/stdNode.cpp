#include "stdNode.h"
/*
this function is used to convert non-standard node file to standard node file.
*/
void tev::stdNode(std::string file)
{

	int nodecount = 0;
	int index;
	double x, y, z;

	std::string file_r = file + ".node";
	std::string file_w = file + "_e.node";
	const char* node_o = file_r.c_str();
	const char* node_n = file_w.c_str();
	FILE *node_r = fopen(node_o, "r");

	if (node_r == (FILE*)NULL) {
		printf("IO Error: Cannot read node file.\n");
		return;
	}
	FILE*node_w = fopen(node_n, "w");
	if (node_w == (FILE*)NULL) {
		printf("IO Error: Cannot write node file.\n");
		return;
	}

	while (!feof(node_r)) {
		fscanf(node_r, "node %d %lf %lf %lf\n", &index, &x, &y, &z);
		nodecount++;
	}

	rewind(node_r);//restart to file header

	fprintf(node_w, "%d  3  0  0\n", nodecount);

	for (int i = 0; i < nodecount; i++) {
		fscanf(node_r, "node %d %lf %lf %lf\n", &index, &x, &y, &z);
		fprintf(node_w, "%d  %lf  %lf  %lf\n", i, x, y, z);
	}

	fclose(node_r);
	fclose(node_w);
	printf("Write standard node file to %s\n", node_n);
}
