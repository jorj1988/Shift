#ifndef MCPOLYHEDRON_H
#define MCPOLYHEDRON_H

#include "MeshCore.h"
#include "MCCGALSetup.h"
#include "MCKernel.h"
#include "CGAL/Polyhedron_3.h"
#include "CGAL/HalfedgeDS_vector.h"
#include "XProperty"
#include "shift/Properties/sbaseproperties.h"

template <class Refs, class Pt> struct MCVertex : public CGAL::HalfedgeDS_vertex_base<Refs>
  {
  MCVertex()
    {
    }

  typedef Pt Point;

  MCVertex(const Point& pt) : _point(pt)
    {
    }

XProperties:
  XRefProperty(Point, point);
  XRefProperty(Eks::Vector3D, normal);
  };

class MCPolyhedronItems
  {
public:
  template <class Refs, class Traits>
  struct Vertex_wrapper
    {
    typedef typename Traits::Point_3 Point;
    typedef MCVertex<Refs, Point> Vertex;
    };

  template <class Refs, class Traits>
  struct Halfedge_wrapper
    {
    typedef CGAL::HalfedgeDS_halfedge_base<Refs> Halfedge;
    };

  template <class Refs, class Traits>
  struct Face_wrapper
    {
    typedef typename Traits::Plane_3 Plane;
    typedef CGAL::HalfedgeDS_face_base<Refs, CGAL::Tag_true, Plane> Face;
    };
  };

class MCPolyhedron : public CGAL::Polyhedron_3<MCKernel, MCPolyhedronItems>//, CGAL::HalfedgeDS_vector>
  {
public:
  void computeNormals();
  };

typedef MCPolyhedron::Halfedge_handle MCHalfedgeHandle;

class MESHCORE_EXPORT MCPolyhedronProperty
    : public Shift::PODPropertyBase<MCPolyhedron, MCPolyhedronProperty>
  {
  S_PROPERTY(MCPolyhedronProperty, Shift::Property, 0)
public:
  typedef Shift::detail::BasePODPropertyTraits<MCPolyhedronProperty> Traits;
  };

#endif // MCPOLYHEDRON_H
