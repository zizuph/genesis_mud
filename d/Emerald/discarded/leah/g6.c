inherit "/std/room";
 
#include "/d/Emerald/defs.h"

object sybille;

void
reset_room()
{


    if (sybille)
	return;
    sybille = clone_object(VILLAGE_DIR + "npc/sybille");
    sybille->move_living("into a room", this_object());
}

void
create_room()
{
   object door;
   add_prop(ROOM_I_INSIDE,1);
   set_short("In a cottage");
   set_long("   This is a pretty little cottage with a single window"+
            " in the southwest corner. There is a table with two chairs near the center of"+
            " the room and a large, sumptuous bed against the north wall.\n\n");

   add_item(({"table"}),"A pretty little wooden table.\n");
   add_item(({"chairs", "chair"}),"The type you might see in an"+
           " ice cream parlour.\n");
   add_item(({"bed"}),"It takes up most of the space in this "+
           "room.\n");
   add_item(({"window"}),"It is just big enough for you to climb"+
           " out.  There appears to be a wisteria vine growing outside.\n");

   door=clone_object(VILLAGE_DIR + "doors/door_d");
   door->move(this_object());
   reset_room();
}
 
void
init()
{
   ::init();
   add_action("climb", "climb");
}

int
climb(string arg)
{
   notify_fail("Climb where?\n");
   if (arg!= "out window" && arg != "window" && arg != "out" &&
       arg !="out of window")
     return 0;
   set_dircmd(arg);
   this_player()->move_living("out window", VILLAGE_DIR + "garden4");
   return 1;
}
