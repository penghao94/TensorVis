#include "generateOFF.h"
/*
this function is used to convert node file and face file to OFF format file
*/
void tev::generateOFF(std::string file)
{
	int nodecount = 0;
	int facecount = 0;
	int edge = 3;
	int temp;
	int a, b, c;
	double x, y, z;

	std::string file_n = file + "_e.node";
	std::string file_f = file + "_e.face";
	std::string file_e = file + "_e.ele";
	std::string file_g = file + "g.off";
	const char* node_o = file_n.c_str();
	const char* face_o = file_f.c_str();
	const char* ele_o = file_e.c_str();
	const char* off_n = file_g.c_str();

	FILE *node_r = fopen(node_o, "r");
	if (node_r == (FILE*)NULL) {
		printf("Cannot read standard Node file.\n");
		return;
	}
	FILE *face_r = fopen(face_o, "r");
	if (face_r == (FILE*)NULL) {
		printf("Cannot read standard face file.\n");
		return;
	}
	FILE *off_w = fopen(off_n, "w");
	if (off_w == (FILE*)NULL) {
		printf("Cannot write off file.\n");
		return;
	}

	fscanf(node_r, "%d  3  0  0\n", &nodecount);
	fscanf(face_r, "%d  0\n", &facecount);
	fprintf(off_w, "OFF\n");
	fprintf(off_w, "%d %d 0\n", nodecount, facecount);

	for (int i = 0; i < nodecount; i++) {
		fscanf(node_r, "%d  %lf  %lf  %lf\n", &temp, &x, &y, &z);
		fprintf(off_w, "%lf %lf %lf\n", x, y, z);
	}
	for (int j = 0; j < facecount; j++) {
		fscanf(face_r, "%d   %d   %d   %d\n", &temp, &a, &b, &c);
		fprintf(off_w, "%d %d %d %d\n", edge, a, b, c);
	}

	fclose(node_r);
	fclose(face_r);
	fclose(off_w);
	remove(node_o);
	remove(face_o);
	remove(ele_o);
	printf("Write off file to %s\n", off_n);
}
