#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

string
get_tells()
{
      string room_tell;
	  room_tell = one_of_list(({"The lanterns flicker on the wall.",
      "Soft chanting can be heard from prayers nearby.",
      "Screams can be heard in the distance.",
      "Oil can be heard trickling through the pipes on the walls.",
      "Footsteps can be heard in the distance.","Loud footfalls can be "
      +"heard on the marble floors growing ever quicker before suddenly "
      +"stopping with a thump"}));
	  return room_tell;
}  