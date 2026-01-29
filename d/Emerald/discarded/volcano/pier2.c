inherit "/std/room";

#include "/d/Emerald/defs.h"

inherit SHIP_ROOM_BASE;

public void
create_room()
{
   set_short("Pier");
    set_long("This is the end of the long wooden dock. "+
         "Eventually a ship may land here, but it is not in use yet. "+
         "The water pounds under your feet and seagulls soar over your " +
         "head.\n");
   
    add_item(({"seagulls", "birds", "sky"}), "The seagulls swoop and "+
         "dive above you in graceful patterns.\n");
    add_item(({"water", "surf"}), "The water surges and recedes under "+
          "the pier causing to to sway gently.\n");
    add_item(({"pier", "dock", "boards"}), "The dock seems to be in "+
          "pretty good shape though it is obvoiusly not in use yet.\n");
   
   add_exit(VOL + "pier1.c", "east");
    add_exit(VOL + "cove", "north");
}
