#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

string
get_tells()
{
      string room_tell;
	  room_tell = one_of_list(({"You overhear guttural noises coming "
      +"from nearby.","Scratching can be heard in the distance","You hear "
      +"water dripping in the distance", "You hear what sounds like a "
      +"conversation echoing within the caves.", "The sounds of combat "
      +"can be heard in the distance.", "Sounds echo through the caves.",
      "A Saurian Shaman brushes past you, quickly, muttering.", "A group "
      +"of Saurian Warriors push past you carrying supplies."}));
	  return room_tell;
}  