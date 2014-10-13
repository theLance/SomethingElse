#ifndef OBJECTCREATOR_HPP_INCLUDED
#define OBJECTCREATOR_HPP_INCLUDED

#include <vector>

#include "Defines.h"


class ObjectCreator
{
public:
  static std::vector<Coordinates> get_random_object();

private:
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

  static std::vector<Coordinates> get_object(ObjectType type);

  static const std::vector<Coordinates> SQUARE;
  static const std::vector<Coordinates> LINE;
  static const std::vector<Coordinates> LBLOCK;
  static const std::vector<Coordinates> JBLOCK;
  static const std::vector<Coordinates> SBLOCK;
  static const std::vector<Coordinates> ZBLOCK;
  static const std::vector<Coordinates> TBLOCK;
};


#endif // OBJECTCREATOR_HPP_INCLUDED
