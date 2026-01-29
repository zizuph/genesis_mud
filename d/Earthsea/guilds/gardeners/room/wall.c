#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/d/Earthsea/herbs/specials/hs";

#include "/d/Earthsea/herbs/herb_sets/park_herbs.h"
#include <macros.h>

#define PARK_ROOM ("/d/Earthsea/gont/gont_city/rooms/park_6")
#define SHED_ROOM ("/d/Earthsea/guilds/gardeners/room/shed")

public void
create_room()
{
    set_short("Secret garden");
    set_long("Here lies a small but luscious and delightful garden " +
        "hidden within a mossy, walled area. Countless rows of " +
        "deep green have been delicately planted here, as well as " +
        "several tall birch trees with thick foliage. A small shed " +
        "has been erected alongside the garden wall.\n");
    set_up_herbs(select_herb_files(PARK_HERBS), PARK_LOCATIONS, 3);
    add_item(({"foliage","sprouts"}),"The new birch sprouts"+
        " growing everywhere here makes it very difficult"+
        " to walk around.\n");
    add_item("wall","A low stone wall surrounds you,"+
        " in bad repair with moss growing thick on and"+
        " between the black cut rocks it is built from. " +
        "You can easily climb over the wall.\n");
    add_item("moss","Green, humid moss grows thick on the"+
        " old stone wall.\n"); 
    add_item(({"row","rows","green","deep green","greenery"}),
        "Dozens of carefully planted rows of common herbs.\n");
    add_item(({"shed", "small shed", "garden shed", "small garden shed"}),
        "Just an ordinary tool shed. Perhaps you could enter it?\n");
}

public int
climb_wall(string str)
{
    object tp = this_player();

    if(!str || !parse_command(str, this_object(),
        "[over] [the] [low] [stone] [garden] 'wall'"))
        return notify_fail("Climb over what?\n");

    write("You easily climb over the low stone wall.\n");
    say(QCTNAME(tp) + " climbs over the low stone wall.\n");
    tp->move_living("M", PARK_ROOM, 1);
    say(QCTNAME(tp) + " arrives, climbing over the low stone wall to " +
        "the north.\n");
    return 1;
}

public int
enter_shed(string str)
{
   if(!str || !parse_command(str, this_object(),
      "[the] [small] [garden] 'shed'"))
   {
      return notify_fail("Enter what?\n");
   }

   set_dircmd("shed");
   this_player()->move_living("shed", SHED_ROOM, 0);
   return 1;
}

public void
init()
{
    ::init();
    add_action(climb_wall, "climb");
    add_action(enter_shed, "enter");
}
