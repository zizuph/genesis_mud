/*
 * The bridge that connects Telberin with the lake side road
 * Coded by Finwe
 * January 1997
 */
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
#include "/d/Emerald/carriages/carriage.h"
#include "/d/Emerald/defs.h"
#include "default.h"
 
void create_room()
{

    set_short("A landing");
    set_long("   You stand on a landing that is connected to " +
        "the bridge. The landing juts out to the lake and " +
        "connects the bridge to the island. It is large and can " +
        "hold many elves that pass this way. At the landing is a " +
        "series of stairs that goes up to the grand arch of " +
        "the city of Telberin, the capital of the elven nation. " +
        "The stairs are large, stately, and made of polished " +
        "marble. You see elves above you on the island going " +
        "about their business.\n\n");
 
    add_prop(IS_CARRIAGE_STOP, 1);
    add_item(({"bird", "birds"}),
        "All kinds of birds fly above you. You see gulls, " +
        "terns, kingfishes, and other birds that live on the water.\n");
    add_item("bridge", 
        "You stand on an ornate bridge. It is wide and constructed " +
        "thick planks of wood. You notice that the bridge can " +
        "easily be destroyed. It is connected to the landing.\n");
    add_item("east",
        "You see the Island of Telberin, The capital of the elves.\n");
    add_item("west", 
        "All you can see is water, boats, and birds.\n");
    add_item("lake",
        "The water of the lake is a deep blue, almost midnight " +
        "black in color. The surface is alive as birds swoop " +
        "down to catch a meal. Out on the lake, you see " +
        "boats, presumably fishing vessels.\n");
    add_item(({"plank", "planks", "wood"}),
        "The planks of the bridge are constructed from wood " +
        "that has been waterproofed. They don't show signs of rot " +
        "or decay and look to be in excellent condition. You don't " +
        "detect any seams where the wood was joined together, but " +
        "you still feel secure on the bridge.\n");
    add_item("landing",
        "The landing is very large. It is a natural spur that " +
        "juts out into the water. The elves enlarged it by carving " +
        "into the island. The spur was enlarged and shaped by the " +
        "elves to accommodate all the traffic that passes this " +
        "way. Now, it marks the unofficial entrance to the city " +
        "since all traffic must past this way. Many boats are " +
        "moored on the outer edges of the landing.\n");
    add_item(({"stairs", "staircase"}),
        "The stairs are carved from the island itself. They " +
        "climb up the island to the Arch. The stairs are faced " +
        "with polished marble.\n"); 
 
    set_alarm(1.0,0.0,"reset_room");
 
    add_exit( THIS_DIR   + "arch", "up", "@@upstairs@@");
    add_exit( THIS_DIR   + "bridge4", "west");
}

void
init()
{
  ::init();
  LOAD_CLONE_HANDLER("/d/Emerald/kroad/clone_handler");
}
 
int upstairs()
{
    write ("You ascend the stairs to Telberin.\n");
 
    say(QCTNAME(TP) + " ascends the stairs to Telberin.\n");
}
