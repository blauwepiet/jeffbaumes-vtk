#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkOrderedTriangulator.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkUnstructuredGrid.h"
#include "vtkShrinkFilter.h"

int main( int argc, char *argv[] )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  //Create some points
  vtkPoints *pts = vtkPoints::New();
  pts->SetNumberOfPoints(8);
  pts->SetPoint(0,0.0,0.0,0.0);
  pts->SetPoint(1,1.0,0.0,1.0);
  pts->SetPoint(2,0.0,0.0,1.0);
  pts->SetPoint(3,1.0,0.0,0.0);
  pts->SetPoint(4,1.0,1.0,0.0);
  pts->SetPoint(5,0.0,1.0,1.0);
  pts->SetPoint(6,0.0,1.0,0.0);
  pts->SetPoint(7,1.0,1.0,1.0);

  // triangulate the points    
  vtkOrderedTriangulator *o = vtkOrderedTriangulator::New();
  o->InitTriangulation(pts->GetBounds(),5);
  o->InsertPoint(0,pts->GetPoint(0),0);
  o->InsertPoint(1,pts->GetPoint(1),0);
  o->InsertPoint(2,pts->GetPoint(2),0);
  o->InsertPoint(3,pts->GetPoint(3),0);
  o->InsertPoint(4,pts->GetPoint(4),0);
//  o->InsertPoint(5,pts->GetPoint(5),0);
//  o->InsertPoint(6,pts->GetPoint(6),0);
//  o->InsertPoint(7,pts->GetPoint(7),0);
  o->Triangulate();

  vtkUnstructuredGrid *ugrid = vtkUnstructuredGrid::New();
  o->GetTetras(0,ugrid);
  
  vtkShrinkFilter *shrink = vtkShrinkFilter::New();
  shrink->SetInput(ugrid);
  shrink->SetShrinkFactor(0.8);

  vtkDataSetMapper *mapper = vtkDataSetMapper::New();
  mapper->SetInput(shrink->GetOutput());
  
  vtkActor *actor = vtkActor::New();
  actor->SetMapper(mapper);
  
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1);
  renWin->SetSize(300,300);

  // interact with data
  renWin->Render();

  iren->Start();
}
