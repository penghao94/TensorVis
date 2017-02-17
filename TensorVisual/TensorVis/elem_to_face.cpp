#include "elem_to_face.h"
/*
this function is used to convert element file to face file
*/
void tev::elem_to_face(std::string file)
{
	int elecount = 0;
	int faceindex = 0;
	int a, b, c, d, e, f, g, h, index, tensor;

	std::string file_e = file + "_e.ele";
	std::string file_f = file + "_e.face";
	const char* ele_o = file_e.c_str();
	const char* face_n = file_f.c_str();

	FILE* ele_r = fopen(ele_o, "r");
	if (ele_r == (FILE*)NULL) {
		printf("File I/O Error: Cannot read standard element file.\n");
		return;
	}
	FILE* face_w = fopen(face_n, "w");
	if (face_w == (FILE*)NULL) {
		printf("File I/O Error: Cannot write standard face file.\n");
		return;
	}

	fscanf(ele_r, "%d  8  0", &elecount);
	fprintf(face_w, "%d  0\n", 12 * elecount);
	for (int i = 0; i < elecount; i++) {
		fscanf(ele_r, "%d %d %d %d %d %d %d %d %d %d\n", &index, &a, &b, &c, &d, &e, &f, &g, &h, &tensor);
		faceindex = 12 * i;
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex, a, d, b);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 1, d, c, b);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 2, b, c, f);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 3, c, g, f);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 4, e, f, h);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 5, f, g, h);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 6, a, e, d);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 7, e, h, d);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 8, a, b, f);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 9, e, a, f);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 10, c, d, g);
		fprintf(face_w, "%d   %d   %d   %d\n", faceindex + 11, d, h, g);
	}
	fclose(ele_r);
	fclose(face_w);
	printf("Write standard face file to %s\n", face_n);
}
