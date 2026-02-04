/*
 * Cave entrance to vampire guild
 * Louie 2006
 */  
#pragma strict_types
#include "defs.h"

inherit ROOM_DIR + "vamp_room";

#include <stdproperties.h>

void
create_vamp_room()
{
    set_short("cave entrance");
    set_long("You are standing just inside a cave hidden amongst "+
        "the rocks at the bottom of a large cliff surrounded "+
        "by water.  "+
        "Below you, waves lap at the rocks in a slow steady "+
        "rhythm.  "+
        "You could easily enter the water from here.  "+
        "To the east a tunnel leads deeper into the cave.  "+
        "\n");
    
    add_item(({"water","waves","rocks"}),
        "Water laps at the rocks below you.  "+
        "It would be possible to jump down and enter the water, "+
        "if you felt like getting cold and wet.  "+
        "\n");

    add_item(({"cliff", "cliff face"}),
        "The rocks of the cliff are all around you.\n");
    
    add_item(({"tunnel"}),
        "The tunnel leads deeper into the cave.\n");

    add_item(({"cave","cave entrance"}),
        "You are standing inside the cave entrance.  "+
        "To the west you can enter the water, while "+
        "a tunnel east leads deeper into the cave.\n");

    add_prop(ROOM_I_LIGHT, 1);

    add_exit("cave1.c","east");
    add_exit("water_room.c","water");
}


