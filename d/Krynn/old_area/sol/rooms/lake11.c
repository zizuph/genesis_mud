/* created by Splunge, modified by Aridor */
   
#include "../local.h"

inherit SOLACE_ROOM_BASE;

object wildlife;

void
reset_solace_room()
{
    if (!wildlife)
      {
	  wildlife = (random(10) > 5 ?
		      clone_object(STMON+"skunk") :
		      clone_object(STMON+"squirrel"));
	  wildlife->move(TO);
      }
}

void
create_solace_room() 
{
    set_short("Lakeside Road");
    set_long("You are in a small clearing now. There is dense foliage all " +
	     "around, but you may be able to trace back the way you came " +
	     "in. There is a path leading off to the east from here, " +
	     "though, and another to the west.\n");
    add_item(({"foliage","trees"}),
	     "This foliage reminds you of the dark forests you encountered " +
	     "earlier on your journey. However, the noises make you a bit " +
	     "more uncomfortable than before.\n");
    add_item("path",
	     "The path looks like it has been used recently, especially " +
	     "towards the east.\n");
    add_item(({"pits","traps"}),
	     "These traps were not set very professionally at all. Any moron " +
	     "can see these things. However, it does look like some of them " +
	     "have already been sprung.\n");
    add_exit(ROOM + "lake10","south",0);
    add_exit(ROOM + "camp_ent","east",0,3);
    add_exit(ROOM + "lake12","west",0,3);
    reset_room();
}
