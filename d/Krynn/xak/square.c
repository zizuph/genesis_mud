/* Xak Tsorath coded by Percy */

#include "xlocal.h"

inherit XAKOUTROOM

#include "/sys/ss_types.h"
#include <macros.h>

void
create_xak_room() 
{
    set_short("The main courtyard");
    set_long("This is the main square in the ruins of Xak Tsaroth"
	     + ". In the center of the courtyard lies the ruins of a well"
	     + ". All around you lie the ruined streets of this once"
	     + " glorious holy city. Now only evil seems to pervade"
	     + " its shattered shell. Much of the city now lies below ground"
	     + " dragged down there by the tremendous force of the great"
	     + " cataclysm that took place many years ago. To the north"
	     + " the street is still passable.\n");
    
    add_exit(TDIR + "outtemple.c", "north", 0);
    add_exit(TDIR + "entrance.c", "south", 0);
    OUTSIDE;
    LIGHT;
    add_item("well", "@@well");
    add_item("ladder", "@@ladder");
    add_item(({"street", "streets", "houses", "city", "ruins"}), "@@ruins");
}

void
init()
{
    ::init();
    ADA("climb");
}

int
climb(string str)
{
    NF("Climb what?\n");
    if ((str == "down") || (str == "ladder") || (str == "down ladder")
	|| (str == "down well") || (str == "well"))
      {
	  if (TP->query_skill(SS_CLIMB) < 20)
	    {
		write("You begin to climb down the ladder but suddenly"
		      + " you notice that the next few rungs on the ladder are "
		      + "missing. You don't think you are a good enough climber"
		      + " to continue on down so you return to the surface.\n");
		SAY(" tries to climb down the well but a few"
		    + " moments later returns to the surface.");
		return 1;
	    }
	  write("You skillfully climb down the ladder past a few missing rungs.\n");
	  SAY(" climbs skillfully down the ladder in the well.");
	  TP->move_living("M", TDIR + "downwell.c", 1);
	  return 1;
      }
    return 0;
}

string
well()
{
    write("The well lies in ruins, much more just a hole"
	  + " in the ground. You notice that the well is also"
	  + " much larger in diameter than usual wells and you"
	  + " can't help but wonder why. "
	  + "The well looks very deep and you notice a rusty"
	  + " ladder that decends into its dark depths.\n");
    SAY(" studies the well carefully.");
    return "";
}

string
ladder()
{
    write("The ladder look well worn and rusty, at places it"
	  + " looks like it is barely attached to the well side."
	  + " Perhaps it wouldn't be safe to climb down it?\n");
    SAY(" studies the ladder carefully.");
    return "";
}

string
ruins()
{
    write("The ruins of this city are pityful indeed. Wrought by the"
	  + " massive forces of the cataclysm that took place in Krynn many"
	  + " years earlier the streets of this city are all either totally"
	  + " blocked by rubble or they have been dragged underground."
	  + " The only passable streets that you can see lie to you south"
	  + " and to your north.\n");
    return "";
}
