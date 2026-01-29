/*
 *  IGARD_LIB + "deep_funcs.c"
 *
 *  Various functions common to Isengard deep rooms.
 *
 *  Last modified by Alto, 24 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"
#include "/sys/formulas.h"

/* PROTOTYPES */

public int           underground_add_items();
public string        stairwell_long_desc();
public int           stairwell_add_items();


public int
underground_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"rock", "black rock", "stone"}), "This area is delved "
        + "into the black rock of Isengard, which is in places natural and "
        + "in others carved by the hands of Men.\n");
    add_item(({"isengard", "fortification"}), "You are somewhere below "
        + "the fortification of Isengard.\n");
    add_item(({"plain", "great plain", "plain of isengard", 
        "great plain of isengard"}), "It is somewhere above you.\n");
    add_item(({"wall", "walls"}), "The walls are delved from black rock "
        + "beneath the plain of Isengard. The rock glistens in the guttering "
        + "torchlight.\n");
    add_item(({"ceiling", "roof"}), "The ceiling is smooth and solid "
        + "black rock. It seems unbreakable and timeless.\n");
    add_item(({"floor", "ground"}), "The floor here is made from black "
        + "rock and worn smooth by tens of thousands of booted feet over "
        + "many long years.\n");
    add_item(({"torch", "torches"}), "Torches are mounted in iron "
        + "brackets set into the walls. They gutter and "
        + "hiss as the wind of your passing stirs them.\n");
    add_item(({"bracket", "iron bracket", "brackets", "iron brackets"}), 
        "Set into the walls, iron brackets bear torches "
        + "that gutter and hiss in the wind of your passing.\n");
    add_item(({"depths", "depths of isengard"}), "All around you the "
        + "depths of Isengard creak and groan.\n"); 

    return 1;
}


string
stairwell_long_desc()
{
    return "This is a narrow underground stairwell somewhere below "
    + "the great plain of Isengard. The walls are set very close "
    + "together, and the steps are short and steep. Torches gutter "
    + "and hiss in iron brackets set at intervals along the passage. ";
}


public int
stairwell_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"rock", "black rock", "stone"}), "The stairwell is delved "
        + "into the black rock of Isengard, which is in places natural and "
        + "in others carved by the hands of Men.\n");
    add_item(({"wall", "walls"}), "The walls are delved from black rock "
        + "beneath the plain of Isengard. They are close enough that you "
        + "can reach out and touch both simultaneously.\n");
    add_item(({"torch", "torches"}), "Torches are mounted in iron "
        + "brackets set along the wall at intervals. They gutter and "
        + "hiss as the wind of your passing stirs them.\n");
    add_item(({"bracket", "iron bracket", "brackets", "iron brackets"}), 
        "Set at intervals along the stairwell, iron brackets bear torches "
        + "that gutter and hiss in the wind of your passing.\n");
    add_item(({"step", "steps", "stair", "stairs", "stairwell"}), "The "
        + "stairwell is narrow and steep, with short steps set close "
        + "together. Each step is far enough above the one below that "
        + "even those with the longest stride would find them strenuous "
        + "to climb.\n");

    return 1;
}
