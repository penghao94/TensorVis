#include "batch_ten.h"
#include "stdNode.h"
#include "stdElement.h"
#include "elem_to_face.h"
#include "extractTen.h"
#include "extractPten.h"
#include "generateOFF.h"
#include "igl\file_dialog_open.h";
void tev::batch_ten(std::string file)
{	
	int num;
	int identity;
	char str[1024];
	std::string out_filename;
	const char* batchfile = file.c_str();
	FILE *batch = fopen(batchfile, "r");
	if (batch == NULL) {
		printf("Can not open batch file.\n");
		return;
	}
	printf("Open batch file: %s\n", batchfile);
	fscanf(batch, "%d %d\n",&identity,&num);
	if (identity == 1) {
		fscanf(batch, ">> %s\n", &str);
		 out_filename= str;
	}
	printf("The count of file is: %d\n", num);
	for (int i = 0; i < num; i++) {
		fscanf(batch, ">> %s\n", &str);
		printf("The %d file: %s\n", i + 1, str);
		std::string filename = str;
		stdNode(filename);
		stdELement(filename);
		elem_to_face(filename);
		if(identity==1)
			extractTen(out_filename,filename);
		else
			extractTen(filename, filename);
		extractPten(filename);
		generateOFF(filename);
		std::cout << std::endl;
	}
}

void tev::batch_ten()
{
	std::string batch = "";
	batch = igl::file_dialog_open();
	if(batch!="")
		batch_ten(batch);
}
