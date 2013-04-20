#include <ObjectCreator.hpp>

#include <cstdlib>


std::vector<Coordinates> ObjectCreator::get_random_object()
{
  return get_object(ObjectType(rand() % 7 + 1));
}

std::vector<Coordinates> ObjectCreator::get_object(ObjectType type)
{
  std::vector<Coordinates> obj_coords;
  obj_coords.push_back(Coordinates(0, 0));

  switch(type)
  {
    case OT_SQUARE:
    {
      obj_coords.push_back(Coordinates(0, -1));
      obj_coords.push_back(Coordinates(1, -1));
      obj_coords.push_back(Coordinates(1, 0));
      break;
    }
    case OT_LINE:
    {
      obj_coords.push_back(Coordinates(0, -1));
      obj_coords.push_back(Coordinates(0, 1));
      obj_coords.push_back(Coordinates(0, 2));
      break;
    }
    case OT_LBLOCK:
    {
      obj_coords.push_back(Coordinates(0, -1));
      obj_coords.push_back(Coordinates(0, 1));
      obj_coords.push_back(Coordinates(1, 1));
      break;
    }
    case OT_JBLOCK:
    {
      obj_coords.push_back(Coordinates(0, -1));
      obj_coords.push_back(Coordinates(0, 1));
      obj_coords.push_back(Coordinates(-1, 1));
      break;
    }
    case OT_SBLOCK:
    {
      obj_coords.push_back(Coordinates(1, 0));
      obj_coords.push_back(Coordinates(0, 1));
      obj_coords.push_back(Coordinates(-1, 1));
      break;
    }
    case OT_ZBLOCK:
    {
      obj_coords.push_back(Coordinates(-1, 0));
      obj_coords.push_back(Coordinates(0, 1));
      obj_coords.push_back(Coordinates(1, 1));
      break;
    }
    case OT_TBLOCK:
    {
      obj_coords.push_back(Coordinates(-1, 0));
      obj_coords.push_back(Coordinates(1, 0));
      obj_coords.push_back(Coordinates(0, -1));
      break;
    }
  }
  return obj_coords;
}
