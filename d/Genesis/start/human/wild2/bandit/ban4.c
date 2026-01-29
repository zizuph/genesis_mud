/*
 * Varian - October 5 2015
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

static object bandit, bandit2, origan;

void

create_room()

{
    set_short("Underground chamber");
    set_long("You are standing in the middle of a large, underground " +
        "chamber. The walls of the chamber, just like the floor and " +
        "ceiling, are made from a hard-packed dirt, held in place and " +
        "supported by a system of wooden posts and beams. A few torches " +
        "have been mounted on the walls, embedded in the dirt, and " +
        "providing just enough light to see by. Aside from a long " +
        "table made of wood, which stands in the middle of the chamber, " +
        "the rest of the room is empty. A dark corridor trails off to " +
        "the north, leading the way back to the surface.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling here is made of dirt, cleverly packed and " +
        "supported by some wooden beams.\n");
    add_item(({"wall", "walls"}),
        "All of the walls here look the same, they are just packed " +
        "dirt, with the occasional wooden post that helps to support " +
        "the ceiling beams above your head.\n");
    add_item(({"torches", "torch"}),
        "A handful of small torches have been embedded into the walls of " +
        "the chamber, burning brightly and casting their light across " +
        "the entire room.\n");
    add_item(({"floor", "down", "ground"}),
        "The floor here is just packed dirt. There are many footprints " +
        "left all around from previous occupants.\n");
    add_item(({"prints", "footprints"}),
        "Dozens of sets of footprints cover the floor of this chamber, " +
        "it is quite obvious that people come here frequently.\n");
    add_item(({"beam", "beams", "post", "posts"}),
        "Every beam is supported at a joint with two posts to keep the " +
        "ceiling stable above your head. There is nothing special about " +
        "them.\n");
    add_item(({"join", "joint"}),
        "These joints are rather simple, yet effective in keeping the " +
        "structure of this chamber together so that the dirt walls and " +
        "ceiling do not come crashing down.\n");
    add_item(({"ladder", "simple ladder", "wooden ladder"}),
        "This is a very simple ladder, with rough slabs of wood nailed " +
        "to each other, forming a ladder that can be climbed up to reach " +
        "the trapdoor.\n");
    add_item(({"dirt", "brown dirt", "brown soil", "soil"}),
        "Dirt, dirt, dirt. Almost everywhere you look, it seems like " +
        "that is all you can see here. Brown and hard-packed, the soil fills " +
        "the ceiling, walls and floor.\n");
    add_item(({"chamber", "room", "large chamber", "here", "underground"}),
        "You are standing in the middle of a large, underground " +
        "chamber. The walls of the chamber, just like the floor and " +
        "ceiling, are made from a hard-packed dirt, held in place and " +
        "supported by a system of wooden posts and beams. A few torches " +
        "have been mounted on the walls, embedded in the dirt, and " +
        "providing just enough light to see by. Aside from a long " +
        "table made of wood, which stands in the middle of the chamber, " +
        "the rest of the room is empty. A dark corridor trails off to " +
        "the north, leading the way back to the surface.\n");
    add_item(({"tunnel", "corridor"}),
        "A long, dark corridor tunnels north, back towards the surface " +
        "and fresh air.\n");
    add_item(({"table", "wooden table"}),
        "A long, wooden table stands in the middle of the room. Perhaps " +
        "somewhat curiously, there are no chairs surrounding it.\n");
    
    add_exit(THIS_DIR + "ban3", "north");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);

    reset_room();

}

void
reset_room() 
{
    if(!bandit) bandit = clone_object(NPC_DIR + "bandit.c");
    if (!present(bandit)) bandit->move(this_object());

    if(!bandit2) bandit2 = clone_object(NPC_DIR + "bandit2.c");
    if (!present(bandit2)) bandit2->move(this_object());

    if(!origan) origan = clone_object(NPC_DIR + "origan.c");
    if (!present(origan)) origan->move(this_object());
}