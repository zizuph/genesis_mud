/*
 * Base file for orc towers in Faerie
 * By Finwe, December 2007
 *
 * Non-obvious exit changed from "o" to "out" to avoid NPC confusion.
 * Aeg 2010
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit S_LIB_CLOCK;
inherit COMMON_BASE;

void create_tower_room() {}

// tower_num is assigned in the room that leads into a tower or exits out to the camp
string tower_num = "Bad tower num. Please report this to a wizard.";

public void
create_room()
{

    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    create_tower_room();
//    reset_faerie_room();

    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room

    add_item(({"walls"}),
        "The walls are made of roughly hewn logs and held together with braided leather. They look sturdy and have probably been standing for years.\n");
    add_item(({"floor", "ground"}),
        "The floor is dirty and made of logs cut in half with the flat sides up. Debris lies scattered around, a lot of it pushed to the walls as the orcs race through the tower.\n");
    add_item(({"leather"}),
        "It is thick strips of animal hide and braided together to hold the walls together. The leather is dried and durable looking.\n");
    add_item(({"logs"}),
        "They are of various sizes and rough looking. Some stand vertical and make up the walls. Others have been cut in half with the flat sides up for the floors.\n");
    add_item(({"ceiling"}),
        "It is made of roughly hewn logs.\n");
    add_item(({"ladder"}),
        "It is simply made of logs tied together, providing a way to travel through the tower.\n");
}

void add_tower_stuff()
{

    add_item(({"windows", "holes"}),
        "They are openings in the wall and allow the guards to look out over the camp.\n");
    add_item(({"camp", "orc camp"}),
        "It is spread out before you beneath the tower. It is messy and a hive of activity from the orcs below.\n");
    add_item(({"forest"}),
        "The forest is full of trees, and blocks your view into it.\n");
}
string tower_desc(string str)
{
    return short() + ". It is circular and solidly constructed. The tower is made of logs that have been tied together with leather. Debris litters the floor. A large ladder leads up.\n";
}

string tower_lower(string str)
{
    return short() + ". The walls have been scratched and clawed by the orcs. Holes are crudely cut into the walls to let the guards look out over the camp. It is dirty here from all the orcs. A ladder sits in a corner, allowing travel between the levels.\n";
}

string tower_middle(string str)
{
    return short() + ". The walls are scratched and look dirty from all the activity up here. Debris is scattered around, cluttering the tower. Holes in the wall provide some light here, and a ladder sits in a corner, allowing travel between the levels.\n";
}

string tower_top(string str)
{
    return short() + ". The scratched walls support a rough ceiling, which provides protection from the elements. From up here the guards see the entire camp and can shout orders to the soldiers below." + str + "\n";
}

/* adds shortcuts for tower entrance/exits 
 *
 * changing the exit "o" to "out" to avoid ncps leaving o.
 * Aeg 2010
 */

// tower exits
void add_tower_exit()
{
    add_exit(OC_DIR + tower_num, "out",0,1,1);
}
