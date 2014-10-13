#ifndef OBJECTCREATOR_HPP_INCLUDED
#define OBJECTCREATOR_HPP_INCLUDED

#include <vector>

#include "Defines.h"


class ObjectCreator
{
public:
  static std::vector<Coordinates> get_random_object();
};


#endif // OBJECTCREATOR_HPP_INCLUDED
