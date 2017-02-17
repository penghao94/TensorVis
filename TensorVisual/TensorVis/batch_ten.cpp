#include "batch_ten.h"
#include "stdNode.h"
#include "stdElement.h"
#include "elem_to_face.h"
#include "extractTen.h"
#include "extractPten.h"
#include "generateOFF.h"

void tev::batch_ten(std::string file)
{	
	int num;
	char str[1024];
	const char* batchfile = file.c_str();
	FILE *batch = fopen(batchfile, "r");
	if (batch == NULL) {
		printf("Can not open batch file.\n");
		return;
	}
	printf("Open batch file: %s\n", batchfile);
	fscanf(batch, "%d\n", &num);
	printf("The count of file is: %d\n", num);
	for (int i = 0; i < num; i++) {
		fscanf(batch, ">> %s\n", &str);
		printf("The %d file: %s.XXX\n", i + 1, str);
		std::string filename = str;
		stdNode(filename);
		stdELement(filename);
		elem_to_face(filename);
		//extractTen(outfile,filename);
		extractPten(filename);
		generateOFF(filename);
		std::cout << std::endl;
	}
}
