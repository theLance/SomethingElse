#include <ObjectCreator.hpp>

#include <cstdlib>
#include <ctime>
#include <map>

#include "Defines.h"


namespace
{
  enum ObjectType
  {
    OT_SQUARE = 1,
    OT_LINE,
    OT_LBLOCK,
    OT_JBLOCK,
    OT_SBLOCK,
    OT_ZBLOCK,
    OT_TBLOCK
  };

  std::vector<Coordinates> returnSquare()
  {
    std::vector<Coordinates> coords;
    coords.push_back(Coordinates(0, 0));
    coords.push_back(Coordinates(0, -1));
    coords.push_back(Coordinates(1, -1));
    coords.push_back(Coordinates(1, 0));
    return coords;
  }
  std::vector<Coordinates> returnLine()
  {
    std::vector<Coordinates> coords;
    coords.push_back(Coordinates(0, 0));
    coords.push_back(Coordinates(0, -1));
    coords.push_back(Coordinates(0, 1));
    coords.push_back(Coordinates(0, 2));
    return coords;
  }
  std::vector<Coordinates> returnLblock()
  {
    std::vector<Coordinates> coords;
    coords.push_back(Coordinates(0, 0));
    coords.push_back(Coordinates(0, -1));
    coords.push_back(Coordinates(0, 1));
    coords.push_back(Coordinates(1, 1));
    return coords;
  }
  std::vector<Coordinates> returnJblock()
  {
    std::vector<Coordinates> coords;
    coords.push_back(Coordinates(0, 0));
    coords.push_back(Coordinates(0, -1));
    coords.push_back(Coordinates(0, 1));
    coords.push_back(Coordinates(-1, 1));
    return coords;
  }
  std::vector<Coordinates> returnSblock()
  {
    std::vector<Coordinates> coords;
    coords.push_back(Coordinates(0, 0));
    coords.push_back(Coordinates(1, 0));
    coords.push_back(Coordinates(0, 1));
    coords.push_back(Coordinates(-1, 1));
    return coords;
  }
  std::vector<Coordinates> returnZblock()
  {
    std::vector<Coordinates> coords;
    coords.push_back(Coordinates(0, 0));
    coords.push_back(Coordinates(-1, 0));
    coords.push_back(Coordinates(0, 1));
    coords.push_back(Coordinates(1, 1));
    return coords;
  }
  std::vector<Coordinates> returnTblock()
  {
    std::vector<Coordinates> coords;
    coords.push_back(Coordinates(0, 0));
    coords.push_back(Coordinates(-1, 0));
    coords.push_back(Coordinates(1, 0));
    coords.push_back(Coordinates(0, -1));
    return coords;
  }

  std::map< ObjectType, std::vector<Coordinates> > returnMap()
  {
    std::map< ObjectType, std::vector<Coordinates> > objs;
    objs[OT_SQUARE] = returnSquare();
    objs[OT_LINE]   = returnLine();
    objs[OT_LBLOCK] = returnLblock();
    objs[OT_JBLOCK] = returnJblock();
    objs[OT_SBLOCK] = returnSblock();
    objs[OT_ZBLOCK] = returnZblock();
    objs[OT_TBLOCK] = returnTblock();
    return objs;
  }

  const std::map< ObjectType, std::vector<Coordinates> > OBJECT_MAP = returnMap();
}

std::vector<Coordinates> ObjectCreator::get_random_object()
{
  return OBJECT_MAP.at(ObjectType((time(nullptr) + rand()) % 7 + 1));
}
