#include <ObjectCreator.hpp>

#include <cstdlib>
#include <map>


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

  const std::vector<Coordinates> SQUARE = returnSquare();
  const std::vector<Coordinates> LINE = returnLine();
  const std::vector<Coordinates> LBLOCK = returnLblock();
  const std::vector<Coordinates> JBLOCK = returnJblock();
  const std::vector<Coordinates> SBLOCK = returnSblock();
  const std::vector<Coordinates> ZBLOCK = returnZblock();
  const std::vector<Coordinates> TBLOCK = returnTblock();

  std::map< ObjectType, std::vector<Coordinates> > returnMap()
  {
    std::map< ObjectType, std::vector<Coordinates> > objs;
    objs[OT_SQUARE] = SQUARE;
    objs[OT_LINE] = LINE;
    objs[OT_LBLOCK] = LBLOCK;
    objs[OT_JBLOCK] = JBLOCK;
    objs[OT_SBLOCK] = SBLOCK;
    objs[OT_ZBLOCK] = ZBLOCK;
    objs[OT_TBLOCK] = TBLOCK;
    return objs;
  }

  const std::map< ObjectType, std::vector<Coordinates> > OBJECT_MAP = returnMap();
}

std::vector<Coordinates> ObjectCreator::get_random_object()
{
  return OBJECT_MAP.at(ObjectType(rand() % 7 + 1));
}
