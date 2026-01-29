/*
 * STORAGE.c
 * Storage Room in the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_room()
{
   set_short("Storage Room");
   set_long("   This dark, damp room looks as though at one point "+
	    "it may have been a useful, well-stocked storage room. You "+
	    "can still smell the sour, sweet odor of ale and whiskey "+
	    "gone bad. Broken kegs and bottles are strewn about the room, "+
	    "some of them still have little puddles of liquid underneath "+
	    "them. To the east you can see some light filtering into "+
	    "the main passageway.\n\n");
   
   add_item("spout",
	    "It is a typical spout. When the keg was full, if you turned "+
	    "the handle, the contents would spill out.\n");

   add_item(({"kegs","broken kegs","keg","broken keg"}),
	    "The keg is made of oak.  It has two big, black iron rings "+
	    "that hold the top and bottom of it together.  The flat part "+
	    "of the keg has a hole with a spout. It looks like some very "+
	    "potent liquid used to reside inside it.\n");

   add_item(({"bottle","bottles","broken bottle","broken bottles"}),
	    "The bottle is made of a dark brown glass fired in the ovens "+
	    "of Emerald.  It seems to have held a sour liquid of some sorts. "+
	    "Maybe an alcohol.\n");

   add_item("handle",
	    "It turns the spout on and off.\n");

   add_exit(THIS_DIR + "main1", "east");
}

void
init()
{
   ::init();
   add_action("passage","turn");
   return;
}

int
passage(string arg)
{
   NF("Turn what?\n");
   if(!arg)
      return 0;
   if(arg == "handle")
      {
	write("As you turn the handle, you notice the ground "+
             "beneath you give way as you begin falling!!!\n\n");
	say("The ground beneath "+QTNAME(TP)+" gives way and "+
	    TP->query_pronoun()+" falls down out of sight!\n");
	TP->move_living("falling through a hole",THIS_DIR+"school");
	tell_room(ENV(TP),QCTNAME(TP)+" drops in from above.\n",TP);
	return 1;
      }
   else
     return 0;
   return 1;
}
