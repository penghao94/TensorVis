#pragma once
#ifndef PRINTPNG_H_
#define PRINTPNG_H_
#include <iostream>
#include <igl\viewer\Viewer.h>
namespace tev {
	bool printPNG(igl::viewer::Viewer &viewer);
	bool printPNG(igl::viewer::Viewer &viewer,const std::string file);
}

#endif // !PRINTPNG_H_
