/* The graveyard
 * grave0.c
 * 14-04-94
 * Nick & Dorak
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h> /* QCTNAME */
inherit GRAVE_STD;

void
create_solace_room()
{
    set_short("Graveyard");
    set_long(BS(
	"You are standing in a graveyard. All around you are graves. This " +
	"place looks quite dead. You get that strange tingle that you alwa" +
	"ys get when you enter a graveyard.  North is the entrance to this" +
        " graveyard.", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

/* add_item without descriptives  - they are found below */

   add_item(({"maple tree", "a maple tree", "maple trees",
		"the maple trees", "tree", "a tree", "trees",
		"the trees"}), "@@mpl_trees");
   add_item(({"the bushes", "bushes", "a bush", "bush"}), "@@bush");
   add_item(({"the forest", "forest"}), "@@forest");
   add_item(({"the stone wall", "stone wall"}), "@@swall");

/* add_item with descriptive included */

   add_item(({"wall", "the wall"}), "Do you mean the stone wall?.\n");
   add_item(({"entrance", "graveyard entrance"}),
	    BS("It is the graveyard entrance, but you will have to go " +
	       "there if you want to see it more clearly.", 70));
   add_item(({"path", "the path"}),
	 BS("This is a well worn path showing the signs of much use.  " +
	    "It wanders in and out between the gravestones and thick b" +
	    "ushes.", 70));

    add_exit(TDIR + "grave_entr", "north");
    add_exit(TDIR + "grave1", "east");
    add_exit(TDIR + "grave5", "south");

	OUTSIDE

}

/* add action items */
void
init() 
{
   ::init();
   ADA("climb");
   ADA("look");
}

int
climb(string str) 
{
    NF("Climb what?\n");
    if ((str == "wall") || (str == "stone wall") || (str == "the wall")
	|| (str == "the stone wall"))
      {
	  write(BS("You try to climb the wall but it is just too smooth.  T" +
		   "here are no cracks or rough spots on it anywhere.  It is truely " +
		   "a remarkabel piece of masonory.", 70));
	  say(QCTNAME(TP) + " tries to climb the stone wall, but fails.\n");
	  return 1;
      }
    if ((str == "tree") || (str == "maple") || (str == "maple tree")
	|| (str == "a tree") || (str == "a maple tree") || (str == "a maple"))
      {
	  write(BS("You try to climb one of the near by maple tree, but all the" +
		   " limbs are too high for you to reach and the trunk is too b" +
		   "ig around to allow you to shimmy up it.", 70));
	  say(QCTNAME(TP) + " tryes to climb a nearby maple tree, but is unable\n"
	      + "to do so.\n");
	  return 1;
      }
    return 0;
}

int
look(string str) 
{
    NF("Look where?\n");
    if ((str == "up") || (str == "u"))
      {
	  write("The sky is crystal clear.\n");
	  say(QCTNAME(TP) + " looks into the sky.\n");
	  return 1;
      }
    if ((str == "down") || (str == "d"))
      {
	  write(BS("There is a path here.  It runs east and nor" +
		   "th-south, becoming a road to the north.", 70));
	  say(QCTNAME(TP) + " looks down.\n");
	  return 1;
      }
    if((str == "n") || (str == "north"))
      {
	  write("The graveyard entrance is to the north of here.\n");
	  say(QCTNAME(TP) + " looks north.\n");
	  return 1;
      }
    if ((str == "nw") || (str == "northwest") || (str == "w")
	|| (str == "west") || (str == "sw") || (str == "southwest"))
      {
	  write("There is a forest here.\n");
	  say(QCTNAME(TP) + " is looking around.\n");
	  return 1;
      }
    if ((str == "ne") || (str == "northeast"))
      {
	  write("There are trees, bushes and a wall here.\n");
	  say(QCTNAME(TP) + " looks towards the gravekeepers estate.\n");
	  return 1;
      }
    if ((str == "s") || (str == "south") || (str == "se")
	|| (str == "southeast") || (str == "e") || (str == "east"))
      {
	  write("There are gravestones extending off into the bushes.\n");
	  say(QCTNAME(TP) + " is looking around the graveyard.\n");
	  return 1;
      }
    return 0;
}


/* default descriptives for looking in directions */
string
swall()
{
    write(BS("Here is a very well kept sturdy tall smooth stone wall.  I" +
	     "t is old and of such incredible workmanship it must have be" +
	     "en made by dwarves.  There are maple trees and bushes betwe" +
	     "en it and the graveyard.", 70));
    say(QCTNAME(TP) + " looks to the northeast.\n");
    return "";
}

string
forest()
{
    write(BS("There is a dark and unpassable forest here.", 70));
    say(QCTNAME(TP) + " gazes into the forest.\n");
    return "";
}

/* add_item descriptions */
string
mpl_trees()
{
    write(BS("These are large majestic maple trees that seperate the gra" +
	     "veyard from the graveyard keepers estate.", 70));
    say(QCTNAME(TP) + " looks at some trees near by.\n");
    return "";
}

string
bush()
{
    write(BS("The bushes here are common harmless undergrowth to Krynn.  A" +
	     "lthough harmless, they usually grow in thick patches that ma" +
	     "ke movement through them difficult or impossible.", 70));
    say(QCTNAME(TP) + " looks at the bushes.\n");
    return "";
}

int
query_grave_room() 
{ 
    return 0; 
}
