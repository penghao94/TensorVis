#include "extractTen.h"
#include "Vonmises.h"
/*
this function is used to extract tensor information from OOFEM outfile
*/
void tev::extractTen(std::string outfile,std::string file)
{
	int start, end;
	int line = 0;
	int index = 0;
	int tensorcount = 0;
	double *temp = new double[6];
	double *mean = new double[6];
	char file_str[1024];

	std::string file_o = outfile + ".out";
	std::string file_t = file + "g.ten";
	std::string file_s = file + "g.sca";
	const char* out_o = file_o.c_str();
	const char* ten_n = file_t.c_str();
	const char* sca_n = file_s.c_str();

	FILE *out_r = fopen(out_o, "r");
	if (out_r == (FILE*)NULL) {
		printf("Cannot read out file.\n");
		return;
	}
	FILE *ten_w = fopen(ten_n, "w");
	if (ten_w == (FILE*)NULL) {
		printf("Cannot write ten file.\n");
		return;
	}
	FILE*sca_w = fopen(sca_n, "w");
	if (sca_w == (FILE*)NULL) {
		printf("Cannot write sca file.\n");
		return;
	}

	while (fgets(file_str, sizeof(file_str), out_r)) {
		if (strstr(file_str, "Element output:")) {
			start = line + 2;
			//printf("tensor start line: %d\n", start);
		}
		if (strstr(file_str, "	R E A C T I O N S  O U T P U T:")) {
			end = line - 4;
			//printf("tensor end line : %d\n", end);
		}
		line++;
	}

	rewind(out_r);

	tensorcount = (end - start) / 17;
	fprintf(ten_w, "%d %d\n", tensorcount, 6);
	fprintf(sca_w, "%d %d\n", tensorcount, 1);

	while (index < start) {
		fgets(file_str, sizeof(file_str), out_r);
		index++;
	}

	for (int i = 0; i < tensorcount; i++) {
		for (int j = 0; j < 6; j++) {
			temp[j] = 0;
			mean[j] = 0;
		}

		for (int k = 0; k < 17; k++) {
			if (k > 0 && (k % 2) == 0) {
				fscanf(out_r, "              stresses %lf %lf %lf %lf %lf %lf\n",
					&temp[0], &temp[1], &temp[2], &temp[3], &temp[4], &temp[5]);

				for (int l = 0; l < 6; l++) {
					mean[l] += temp[l];
				}
			}
			else
				fgets(file_str, sizeof(file_str), out_r);
		}

		for (int l = 0; l < 6; l++) {
			mean[l] /= 8;
		}

		fprintf(ten_w, "%lf %lf %lf %lf %lf %lf\n", mean[0], mean[1], mean[2], mean[3], mean[4], mean[5]);
		fprintf(sca_w, "%lf\n", tev::Vonmises(mean[0], mean[1], mean[2], mean[3], mean[4], mean[5]));
	}

	fclose(out_r);
	fclose(ten_w);
	fclose(sca_w);
	delete(mean);
	delete(temp);
	printf("Write tensor file to %s\n", ten_n);
	printf("Write scalar file to %s\n", sca_n);
}
