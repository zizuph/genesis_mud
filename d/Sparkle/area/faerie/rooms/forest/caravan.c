/*
 * A gypsy caravan
 * By Finwe, January 2006
 */
 
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/std/room";
inherit COMMON_BASE;

void add_stuff();
 
void
create_room()
{
    set_short("Inside a caravan");
    set_long("This is a large caravan. It is long, cramped, and bow shaped. " +
        "It has a barrel shaped roo. The walls are garishly painted yellow " +
        "and crowded with shelves, instruments and paintings. A few beds " +
        "line the walls, a cupboard sits in a corner, and a stove sits in " +
        "another. A large rug covers the floor.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"rug", "carpet"}),
        "The rug is red and covers the whole floor. It is plain looking.\n");
    add_item(({"walls", "wall"}),
        "The walls are round and curve upwards. They are crowded with shelves, pictures, and instruments.\n");
    add_item(({"shelf", "shelves"}),
        "The shelves are made of wood and line the walls. The shelves are stuffed with lots of things.\n");
    add_item(({"instruments"}),
        "Hanging from the walls are various instruments. Many of them are unrecognizable, but some of them you do know include harps, tamborines, lutes, and recorders.\n");
    add_item(({"harp", "harps"}),
        "These are upright triangular shaped instruments. They consist of a pillar, a curved neck, and a hollow back with a sounding board. Many strings are strung from the neck of the harp to the soundboard, and vary in width and length.\n");
    add_item(({"lyre", "lyres"}),
        "\n");
    add_item(({"soundboard", "soundboards"}),
        "These are think pieces of wood that are part of the harps and lyres. They vibrate with sound whenever the strings are played and improve the sound of the instrument. \n");
    add_item(({"pillar", "pillars"}),
        "They are vertical pieces of wood of the harps and lyres. Some are ornately carved.\n");
    add_item(({""}),
        "\n");
    add_item(({""}),
        "\n");
    add_item(({""}),
        "\n");
    add_item(({""}),
        "\n");
    
    add_exit(GO_DIR + "road19", "out");
    add_exit(GO_DIR + "road19", "o", 0,0,1);


 
}

void reset_room() 
{ 
    add_stuff();
}

void
add_stuff()
{
//    object testelf;
/*
    if(!present("testelf"))
    {
        testelf = clone_object(NPC_DIR + "test_elf");
        testelf->move(TO);
    }
*/
}