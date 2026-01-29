#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

string
get_tells()
{
      string room_tell;
	  room_tell = one_of_list(({"The lanterns flicker on the wall.",
      "Soft chanting can be heard from prayers nearby.",
      "A Thanarian priest walks past you grasping his medallion.",
      "Screams can be heard in the distance.",
      "Two priests walk past you in deep discussion.",
      "A priest runs past you, fear in his eyes.",
      "Oil can be heard trickling through the pipes on the walls.",
      "Incense wafts from vents in the base of the marble walls.",
	  "An elf arrives screaming profanities before quickly being ushered "
	  +"away by two stern priests.", "Dark shadows are cast across the "
      +"marble floors as a cloud passes in front of the sun.", "Footsteps "
      +"can be heard in the distance.","Loud footfalls can be heard on the "
      +"marble floors growing ever quicker before suddenly stopping."}));
	  return room_tell;
}  