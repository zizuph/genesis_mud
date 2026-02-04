inherit "std/room";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message,75)
#define PS(message)     process_string(message)
#define TP              this_player
#define TO              this_object

void
init()
{
    ::init();
    add_action("do_climb","climb");
}

void
create_room(){

   set_short("Copse of Willow");
   set_long(break_string("This small gathering of willows gleams in the " +
      "valley sun, their long branches draping down " +
      "to the ground. The earth is very damp. To the south the copse "
      + "continues.\n",75));
   
   add_exit("/d/Terel/mecien/valley/copse1", "south",0);
    add_exit("/d/Terel/mecien/valley/copse4", "east", 0);
   add_exit("/d/Terel/mecien/valley/copse3", "north", 0);
   add_item(({"trees","tree","willow","willows"}),break_string("These "
   + "majestic trees fill you with a sense of peace and serenity. Their "
   + "branches, which approach the thickness of the "
   + "trunk, root the ancient trees to the ground with such solidity you doubt a "
   + "hurricane could uproot them.\nOne tree seems like it might be easy "
   + "to climb.\n",75));
}

int
do_climb(string str)
{
    if (str=="tree" || str =="willow")
    {
	write("Sure enough, you scamper easily up the tree.\n");
	say(QCTNAME(this_player())+ " scampers up the tree.\n");
	this_player()->move("/d/Terel/mecien/valley/uptree.c");
	return 1;
    }
    else
    {
	notify_fail("Climb what?\n");
	return 0;
    }
}
