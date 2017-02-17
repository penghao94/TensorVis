#include "stdElement.h"

void tev::stdELement(std::string file)
{
	int elecount = 0;
	int index, tensor;
	int a, b, c, d, e, f, g, h;

	std::string file_r = file + ".ele";
	std::string file_w = file + "_e.ele";
	const char*ele_o = file_r.c_str();
	const char*ele_n = file_w.c_str();

	FILE *ele_r = fopen(ele_o, "r");
	if (ele_r == (FILE*)NULL) {
		printf("File I/O Error: Cannot read element file.\n");
		return;
	}
	FILE *ele_w = fopen(ele_n, "w");
	if (ele_w == (FILE*)NULL) {
		printf("File I/O Error: Cannot write element file.\n");
	}

	while (!feof(ele_r)) {
		fscanf(ele_r, "%d %d %d %d %d %d %d %d %d   %d\n", &index, &a, &b, &c, &d, &e, &f, &g, &h, &tensor);
		elecount++;
	}

	fprintf(ele_w, "%d  8  0\n", elecount);
	rewind(ele_r);
	for (int i = 0; i < elecount; i++) {
		fscanf(ele_r, "%d %d %d %d %d %d %d %d %d   %d\n", &index, &a, &b, &c, &d, &e, &f, &g, &h, &tensor);
		fprintf(ele_w, "%d %d %d %d %d %d %d %d %d %d\n", i, a - 1, b - 1, c - 1, d - 1, e - 1, f - 1, g - 1, h - 1, tensor - 1);
	}

	fclose(ele_r);
	fclose(ele_w);
	printf("write standard element file to %s\n", ele_n);
}
