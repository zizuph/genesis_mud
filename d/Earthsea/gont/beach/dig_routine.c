#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "defs.h"

#define CLAMS_MAX 5
#define DIG_PARALYZE "/d/Earthsea/gont/beach/dig_paralyze.c"

void
dig_clams(object player, object room)
{
  object paralyze;
  player->catch_msg("You kneel down on the sand and start digging " +
		    "a hole next to the sea.\n");
  tell_room(room, QCTNAME(player) + " kneels down on the sand and starts " +
	    "digging a hole in the sand next to the sea.\n",
	    player);
  paralyze = clone_object(DIG_PARALYZE);
  paralyze->set_room(room);
  paralyze->move(player);
}
