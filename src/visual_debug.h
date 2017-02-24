#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include "quadrilateral.h"

namespace fourbar {

  typedef vtkSmartPointer<vtkPolyData> polydata;

  void visualize_points(const quadrilateral& q);

  void visualize_polydatas(const std::vector<polydata>& pds);

  polydata polydata_for_points(const std::vector<vec2>& pts);

  void color_polydata(vtkSmartPointer<vtkPolyData> data,
		      const unsigned char red,
		      const unsigned char green,
		      const unsigned char blue);
  
}
