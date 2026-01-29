#include <stdproperties.h>
#include <macros.h>
#include "../lizards.h"

string
get_tells()
{
      string room_tell;
	  room_tell = one_of_list(({"You overhear guttural noises coming "
      +"from nearby.","Scratching can be heard in the distance","You hear "
      +"water dripping in the distance"}));
	  return room_tell;
}  