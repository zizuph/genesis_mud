#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";

object *shore_rooms =
({"/d/Earthsea/gont/beach/karg_landing/karg_landing01",
  "/d/Earthsea/gont/beach/karg_landing/karg_landing02",
  "/d/Earthsea/gont/beach/karg_landing/karg_landing03",
  "/d/Earthsea/gont/beach/karg_landing/karg_landing04",
  "/d/Earthsea/gont/beach/karg_landing/karg_landing05",
  "/d/Earthsea/gont/beach/beach_rooms/beach18",
  "/d/Earthsea/gont/beach/beach_rooms/beach19"});


void create_earthsea_room()
{
  set_short("Under water");
  set_long("You are disoriented. You remember falling into the " +
	   "water when the deck on the longship collapsed below you. " +
	   "However, you cannot tell which way is up or down as you " +
	   "look for the surface of the sea to gasp for a breath of " +
	   "air.\n");
  set_tell_time(10);
  add_tell("You swallow a large gulp of water.\n");
  add_tell("You flail around in vain looking for the surface.\n");
  add_tell("You feel like you are drowning.\n");
  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_UNDERSEA);
  add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
}

public void wash_ashore(object player)
{
  int i;

  i = random(sizeof(shore_rooms));
  tell_room(shore_rooms[i],
	    QCTNAME(player) + " washes ashore.\n");
  player->catch_msg("You wash ashore.\n");
  player->move(shore_rooms[i]);
}

public void enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (living(ob))
    {
      set_alarm(45.0, 0.0, &wash_ashore(ob));
    }
}
