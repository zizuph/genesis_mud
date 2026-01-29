/*
   Wayreth. Courtyard in front of the towers.

   yard01.c
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

void
create_wayreth_room()
{
   set_short("Northeast courtyard");
   set_long("This is the northeastern courtyard in the complex " +
      "that surrounds the Tower of High Sorcery. To the northeast " +
      "is a guard tower, while the Tower itself stands to the " +
      "southwest. The main courtyard can be seen to the south. " +
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
      "of High Sorcery stands to the southwest from here. It has " +
      "walls of polished obsidian. No windows can be seen in its " +
      "smooth surface.\n");
   add_item(({"walls","walls of polished obsidian","surface",
      "smooth surface"}),"The walls of the Tower are a glossy " +
      "black, and seem to be enchanted with magic.\n");

   add_exit(WTOWER + "yard02", "south", 0);
   add_exit(WTOWER + "wall_tower01", "northeast", 0);
}

