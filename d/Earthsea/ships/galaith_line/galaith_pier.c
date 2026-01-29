#pragma strict_types

/*
* End of the west pier of Gont City.
*
* Coded by Porta 971018.
* Damaris 01/2006 - Removed the boat from Galaith Isle 
*/

inherit "/d/Earthsea/std/room.c";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_earthsea_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Small Pier");
    set_long("You are standing at the end of a wooden pier"+
	" stretching out into the bay of Gont Port and"+
	" everywhere around you can see different kinds of"+
	" ships anchored. This is a very busy harbour with"+
	" a forest of masts swaying back and forth in the"+
	" breeze coming in from the sea. At this pier"+
	" there is only a berth for a much smaller boat. It extends"+
	" some distance out into the water. A salty smell of sea"+
	" and fish is in the air.\n");

    add_item("pier", "The pier is built from sturdy timber"+
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
    add_item("cliffs","Almost straight south are the Armed"+
      " Cliffs, and between them the canal leading into the"+
      " secluded bay.\n");

    add_exit(SHIRE_LINE + "shire_pier", "west");
    reset_room();



}
