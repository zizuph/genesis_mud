#pragma strict_types

inherit "/d/Earthsea/std/room";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

#define SIGN SPARK_LINE + "sign1.c"

private object sign, ship;

public int
restart_ship()
{
  //ship->start_ship(0);
}

void
reset_room()
{
  /* object to = this_object();
    if (!objectp(ship))
    {
	ship = clone_object(SPARK_LINE + "ship");
	ship->move(to);
	ship->start_ship(0);
  } */
}

void
create_earthsea_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("End of the East Pier");
    set_long(break_string("You have come to the end of the east pier"+
	" stretching out into the bay of Gont Port, and"+
	" everywhere around you can see different kinds of"+
	" ships anchored. This is a very busy harbour with"+
	" a forest of masts swaying back and forth in the"+
	" breeze coming in from the sea. At this pier"+
	" there are mostly traders, but also a few"+
	" passenger ships with destinations to far away lands."+
	" You hear the sound of hawsers creaking against"+
	" woodwork when the ships rock in the small waves."+
	" A salty smell of sea and fish is in the air.\n", 70));

    add_item("pier", "The pier is built form sturdy timber"+
      " logs, stretching far out in the bay. There are"+
      " many ships anchored along the side, coming from"+
      " different places of the Archipelago.\n");
    add_item("ships","A great number of ships are anchored"+
      " in Gont Port with masts swaying back and forth in"+
      " the small waves coming in. You see galleys, sloops,"+
      " caravels and many other types.\n");
    add_item("masts","The masts are swaying back and forth"+
      " in the breeze.\n");
    add_item("harbour","This is the Port of Gont, a busy"+
      " trading harbour with many ships visiting every"+
      " year.\n");
    add_item("waves","The waves are very small here, finding"+
      " their way through the narrow canal between the Armed"+
      " Cliffs.\n");
    add_item("cliffs","Almost straight to the"+
      " south are the Armed"+
      " Cliffs, and between them the canal leading into the"+
      " secluded bay.\n");
    add_item(({"trader", "traders"}),
        "This pier is used mostly by trading ships. A number of " +
        "merchants and crewmen can be seen going back and forth " +
        "from the city to their boats.\n");

    sign = clone_object(SIGN);
    sign->move(TO);
    reset_room();
    add_exit(AVENIR_LINE + "east_pier1.c", "east");
}

