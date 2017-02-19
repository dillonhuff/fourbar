#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include "quadrilateral.h"

namespace fourbar {

  typedef vtkSmartPointer<vtkPolyData> polydata;

  void visualize_points(const quadrilateral& q);
}
