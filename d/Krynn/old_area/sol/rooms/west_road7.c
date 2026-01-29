/*
* The village Solace
*
* By Rastlin
*/
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

object shindig;

void
reset_solace_room()
{
    if (shindig)
      return;
    shindig = clone_object(NPC + "shindig");
    shindig->move_living("xx", TO);
    shindig->seq_new("do_thing");
    shindig->seq_addfirst("do_thing",
			  ({"@@arm_me", "@@start_patrol"}));
}

void
create_solace_room()
{
   set_place(WESTROAD);
   
   set_long_desc("The two tracks from west and north merge here and forms " +
      "the West road that leads southeast through the forest " +
      "into the tree village Solace. The track to the west " +
      "leads down to a pier at Crystalmir Lake, the beautiful " +
      "lake. The track to the north, mostly used by hunters " +
      "and fishers, runs along the lake.");
   
   add_exit(C_LAKE, "north");
   add_exit(C_SHIP, "west");
   add_exit(TDIR + "west_road6", "southeast");
}

