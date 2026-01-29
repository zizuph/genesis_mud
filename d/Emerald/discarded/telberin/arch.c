/*
 * The bridge that connects Telberin with the lake side road
 * Coded by Finwe
 * January 1997
 */
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
#include "/d/Emerald/defs.h"
#include "default.h"
 
void create_room()
{
    set_short("The Arch of Telberin");
    set_long("   You stand before the Arch of Telberin. It is " +
        "awe inspiring in size. All that stand before it are " +
        "small in comparison. The Arch is wide enough to allow " +
        "25 elves to walk abreast as they pass through it. The " +
        "inside rises looks to be as tall as a tall tree. Over " +
        "all, the structure is immense. The Arch is decorated " +
        "with reliefs of elven history. The road that leads into " +
        "the city is constructed of interlocking red and white " +
        "marble blocks. Elves stream past you as they pass " +
        "through the Arch. For the most part, they are gaily " +
        "dressed in bright colors. Those leaving the city are " +
        "dressed in neutral colors so that they can blend into " +
        "their surroundings. Happiness and peace pervade the air " +
        "as the elves relax here. A magnificent castle rises " +
        "before you, shining in the sunlight. A beautiful " +
        "staircase descends to the landing at the edge of the " +
        "lake.\n\n");
 
    add_item(({"bird", "birds"}),
        "Many birds fly around here as they dart in and out " +
        "of the trees. They fill the air with their songs.\n");
 
    add_item("west", 
        "All you can see is water, boats, and birds. The bridge " +
        "stretches west into the lake.\n");
    add_item("lake",
        "The water of the lake is a deep blue, almost midnight " +
        "black in color. The surface is alive as birds swoop " +
        "down to catch a meal. Out on the lake, you see " +
        "boats, presumably fishing vessels.\n");
    add_item("landing",
        "The landing is very large. It is connected to the bridge.\n");
    add_item(({"stairs", "staircase"}),
        "The stairs are carved from the island itself. They " +
        "descend to the landing at the lake's edge. They are " +
        "faced with polished marble.\n"); 
    add_item(({"arch", "Arch"}),
        "The Arch dominates this part of town. Made of polished " +
        "white marble, it stands as a sentinal, protecting the " +
        "elves of Telberin. You notice reliefs carved onto the " +
        "Arch.\n");
    add_item(({"elves", "citizens", "elf", "citizen"}),
        "The elves of Telberin are a relaxed yet joyful race. " +
        "They love their city and defend it against all enemies. " +
        "They are dressed in bright colors that reflect their " +
        "disposition.\n");
    add_item( ( {"relief", "reliefs"}),"@@random_relief_desc@@"); 
 
 
    set_alarm(1.0,0.0,"reset_room");
 
    add_exit( THIS_DIR   + "landing", "down", "@@downstairs@@");
    add_exit( AVENUE_DIR   + "ave01", "east");
}
 
void
reset_room()
{
}
 
 
int downstairs()
{
    write ("You descend the stairs to the landing.\n");
 
    say(QCTNAME(TP) + " descends the stairs to landing.\n");
}
 
 
string random_relief_desc()
{
 
  return ({ "You see a carving that depicts the coming of the " +
                "elves to Telberin\n",
            "You see a depiction of the wedding of the Princess " +
                "and a foreign prince.\n",
            "You see the King defeating their enemies in a war.\n",
            "Across the top of the Arch, you see the elves arrive " +
                "in Telberin.\n",
            "You see the wedding of the King and Queen.\n",
            "Inside the Arch, you see relief carvings of " +
                "roses growing up and over the walls.\n",
        })[random(5)];
}

void
init()
{
  ::init();
  LOAD_CLONE_HANDLER("/d/Emerald/telberin/clone_handler");
}
