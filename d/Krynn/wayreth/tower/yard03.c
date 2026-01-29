/*
   Wayreth. Courtyard in front of the towers.

   yard03.c
   --------

   Coded ........: 95/05/31
   By ...........: Jeremiah

   Latest update : 96/11/28
   By ...........: Teth

*/

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include <composite.h>

inherit WAYOUTROOM;

public mixed prevent_teleport();

void
create_wayreth_room()
{
   set_short("Southeast courtyard");
   set_long("This is the southeastern courtyard in the complex " +
      "that surrounds the Tower of High Sorcery. To the southeast " +
      "is a guard tower, while the Tower itself stands to the " +
      "northwest. The main courtyard can be seen to the north. " +
      "The ground is covered with a black tile, a gridded solid " +
      "sheet.\n");
   add_item(({"black tile","tile","sheet","solid sheet",
      "gridded sheet","gridded solid sheet","tiles","black tiles"}),
      "This layer of black tiles covers the ground, and they " +
      "are embedded firmly. They make walking in the courtyard " +
      "quite a relaxing affair.\n");
   add_item("guard tower", "This tower stands empty, and is composed " +
      "of a dusky black rock.\n");
   add_item(({"dusky black rock","dusky rock","black rock","rock"}),
      "A closer examination reveals nothing special about it.\n");
   add_item("courtyard","You are standing in it.\n");
   add_item(({"Tower","tower","Tower of High Sorcery"}), "The Tower " +
      "of High Sorcery stands to the northwest from here. It has " +
      "walls of polished obsidian. No windows can be seen in its " +
      "smooth surface.\n");
   add_item(({"walls","walls of polished obsidian","surface",
      "smooth surface"}),"The walls of the Tower are a glossy " +
      "black, and seem to be enchanted with magic.\n");

   add_exit(WTOWER + "yard02", "north", 0);
   add_exit(WTOWER + "wall_tower02", "southeast", 0);

   add_prop(ROOM_M_NO_TELEPORT, prevent_teleport);
   add_prop(ROOM_M_NO_ATTACK, "Magical runes of tranquility have been incorporated " +
       "into the walls surrounding the Tower of High Magic. There will be no violence " +
       "allowed on these grounds.\n");
}

public mixed
prevent_teleport()
{
    if(!this_player())
	return 0;

    if(this_player()->query_is_wohs())
	return 0;

    return "Something prevents you from teleporting there.";
}

