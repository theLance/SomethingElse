#ifndef OBJECTCREATOR_HPP_INCLUDED
#define OBJECTCREATOR_HPP_INCLUDED

#include <vector>

#include "Defines.h"


class ObjectCreator
{
public:
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

  static std::vector<Coordinates> get_random_object();

private:
  static std::vector<Coordinates> get_object(ObjectType type);
};


#endif // OBJECTCREATOR_HPP_INCLUDED
