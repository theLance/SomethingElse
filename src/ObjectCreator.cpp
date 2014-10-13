#include <ObjectCreator.hpp>

#include <cstdlib>


namespace
{
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
}

const std::vector<Coordinates> ObjectCreator::SQUARE = returnSquare();
const std::vector<Coordinates> ObjectCreator::LINE = returnLine();
const std::vector<Coordinates> ObjectCreator::LBLOCK = returnLblock();
const std::vector<Coordinates> ObjectCreator::JBLOCK = returnJblock();
const std::vector<Coordinates> ObjectCreator::SBLOCK = returnSblock();
const std::vector<Coordinates> ObjectCreator::ZBLOCK = returnZblock();
const std::vector<Coordinates> ObjectCreator::TBLOCK = returnTblock();

std::vector<Coordinates> ObjectCreator::get_random_object()
{
  return get_object(ObjectType(rand() % 7 + 1));
}

std::vector<Coordinates> ObjectCreator::get_object(ObjectType type)
{
  switch(type)
  {
    case OT_SQUARE:
    {
      return SQUARE;
    }
    case OT_LINE:
    {
      return LINE;
    }
    case OT_LBLOCK:
    {
      return LBLOCK;
    }
    case OT_JBLOCK:
    {
      return JBLOCK;
    }
    case OT_SBLOCK:
    {
      return SBLOCK;
    }
    case OT_ZBLOCK:
    {
      return ZBLOCK;
    }
    case OT_TBLOCK:
    {
      return TBLOCK;
    }
  }
}
