/*
   Wayreth. Courtyard in front of the tower.

   yard02.c
   --------

   Coded ........: 95/05/31
   By ...........: Jeremiah

   Latest update : 96/10/23
   By ...........: Teth
   added add_items, new long desc

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
   set_short("The courtyard of the Tower of High Sorcery");
   set_long("You are standing in the courtyard of the Tower of High Sorcery. "+
            "Twin towers of High Sorcery rise high above you, like a huge "+
            "taloned claw. A pair of open gates lead east out of the "+
            "courtyard, while to your west a foretower provides entry to " +
            "the twin towers. Small towers stand at the northeast and southeast "+
            "corner of the complex, and considering the triangular shape of "+
            "the surrounding walls, you assume a third tower stands on the "+
            "other side of the courtyard. The courtyard continues to the north " +
            "and south, and "+
            "circumvents the Tower to the southwest and northwest.\n");
   AI(({"tower","towers","Tower of High Sorcery","Tower of Wayreth",
        "tower of wayreth","tower of high sorcery","twin towers"}),
        "Two towers of High Sorcery looms above you like a huge taloned claw " +
        "of slick obsidian. You are awed " +
        "by the magic that emanates from the cold surface of the Tower. A " +
        "foretower to your west provides entry to the two towers.\n");
   AI("foretower","A foretower stands open to your west, providing entry " +
      "to the two towers that rise above you.\n");
   AI(({"slick walls","walls of obsidian","slick obsidian",
        "obsidian walls","walls"}),"These sheer black walls seem to be " +
        "made of polished glass, however that is a quality of obsidian. " +
        "The walls don't seem to be made for the purpose of keeping things " +
        "out, but rather to keep things in!\n");
   AI(({"open gates","gates"}),"These delicate gates seem to be made of " +
        "thin fibres of gold and silver, interwoven with magic. It seems " +
        "that the rare metals are simply ornamental, and the gate itself " +
        "is a structure composed of the physical essence of magic.\n");
   AI("surrounding walls","The surrounding walls are made of the same " +
        "material as the main tower. They surround the complex.\n");
   AI("complex","The complex consists of the main Towers, and a triangle " +
        "of outer walls, with a tower in each of the corners.\n");
   AI(({"small towers","corner towers"}),"These smaller towers " +
        "serve no apparent purpose other than design. This complex " +
        "certainly does not need guards posted, due to the strong magics " +
        "contained within the walls.\n");
   AI("courtyard","The courtyard is neither welcome nor unwelcome in " +
        "appearance, but rather decidedly neutral. The Tower of High " +
        "Sorcery demands your attention, and the open gates are pleasant " +
        "to look at, but other than that, there appears to be little " +
        "detail.\n");

   add_exit(WTOWER + "yard01", "north", 0);
   add_exit(WFOREST + "clearing", "east", 0);
   add_exit(WTOWER + "yard03", "south", 0);
   add_exit(WTOWER + "yard04", "southwest", "@@around_tower");
   add_exit(WTOWER + "foretower", "west", "@@enter_tower");
   add_exit(WTOWER + "yard04", "northwest", "@@around_tower");

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


int
around_tower()
{
   write("You follow the obsidian wall of the Tower in a semi circle " +
         "and arrive on the western side of the complex.\n");
   return 0;
}

int
enter_tower()
{
   write("\nWelcome to the Tower of High Sorcery!\n\n");
   return 0;
}
