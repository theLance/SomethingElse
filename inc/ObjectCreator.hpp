#ifndef OBJECTCREATOR_HPP_INCLUDED
#define OBJECTCREATOR_HPP_INCLUDED

#include <vector>

struct Coordinates;


class ObjectCreator
{
public:
  static std::vector<Coordinates> get_random_object();
};


#endif // OBJECTCREATOR_HPP_INCLUDED
