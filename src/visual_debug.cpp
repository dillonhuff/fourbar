#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkVertex.h>

#include "visual_debug.h"

using namespace std;

namespace fourbar {

  polydata polydata_for_points(const std::vector<vec2>& pts) {
    vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> vertexes =
      vtkSmartPointer<vtkCellArray>::New();

    for (auto pt : pts) {
      vtkIdType i1 = points->InsertNextPoint(pt.x(), pt.y(), 0);

      vtkSmartPointer<vtkVertex> vertex =
	vtkSmartPointer<vtkVertex>::New();

      vertex->GetPointIds()->SetId(0, i1);

      vertexes->InsertNextCell(vertex);
    }

    // Create a polydata object
    vtkSmartPointer<vtkPolyData> pd =
      vtkSmartPointer<vtkPolyData>::New();
 
    // Add the geometry and topology to the polydata
    pd->SetPoints(points);
    pd->SetVerts(vertexes);

    return pd;
  }

  vtkSmartPointer<vtkActor> polydata_actor(vtkSmartPointer<vtkPolyData> polyData)
  {
    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);
 
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    return actor;
  }
  
  void visualize_actors(const std::vector<vtkSmartPointer<vtkActor> >& actors)
  {
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    // Create axes
    vtkSmartPointer<vtkAxesActor> axes =
      vtkSmartPointer<vtkAxesActor>::New();

    renderer->AddActor(axes);
    for (auto actor : actors) {
      actor->GetProperty()->SetPointSize(5);
      renderer->AddActor(actor);
    }
    renderer->SetBackground(0.5, 0.5, 0.5);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindow->Render();
    renderWindowInteractor->Start();
  }
  
  void visualize_polydatas(const std::vector<polydata>& pds) {
    std::vector<vtkSmartPointer<vtkActor> > actors;

    for (auto& pd : pds) {
      auto pda = polydata_actor(pd);
      actors.push_back(pda);
    }

    visualize_actors(actors);
  }

  void visualize_points(const quadrilateral& q) {
    vector<vec2> points = q.crank_sample(0.5);
    polydata pd = polydata_for_points(points);

    visualize_polydatas({pd});
  }

  void color_polydata(vtkSmartPointer<vtkPolyData> data,
		      const unsigned char red,
		      const unsigned char green,
		      const unsigned char blue) {
    unsigned char color[3];
    color[0] = red;
    color[1] = green;
    color[2] = blue;

    // Create a vtkUnsignedCharArray container and store the colors in it
    vtkSmartPointer<vtkUnsignedCharArray> colors =
      vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3);
    for (vtkIdType i = 0; i < data->GetNumberOfCells(); i++) {
      colors->InsertNextTupleValue(color);
    }
 

    data->GetCellData()->SetScalars(colors);

  }
  
}
