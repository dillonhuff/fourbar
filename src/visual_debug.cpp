#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkCellArray.h>
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

    cout << "# of cells = " << pd->GetNumberOfPolys() << endl;
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
      cout << "# of polys in pd = " << pd->GetNumberOfPolys() << endl;
      auto pda = polydata_actor(pd);
      actors.push_back(pda);
    }

    cout << "Starting viz" << endl;

    visualize_actors(actors);

    cout << "Done with viz" << endl;
  }

  void visualize_points(const quadrilateral& q) {
    vector<vec2> points = q.crank_sample(0.5);
    polydata pd = polydata_for_points(points);

    visualize_polydatas({pd});
  }

}
