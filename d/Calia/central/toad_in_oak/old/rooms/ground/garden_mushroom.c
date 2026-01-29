/*
 * /d/Calia/central/toad_in_oak/rooms/ground/garden_mushroom.c
 *
 * This is the Toad-in-Oak mushroom garden. 
 * 
 * HISTORY: [99-06-15] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("The Toad-in-Oak mushroom garden"); 

    set_long("You stand in a small gap between the trees that seems to be " +
        "dark and damp even by the standards of the rest of the forest. It " +
        "might have something to do with the circle of tall shrubs that " + 
        "all bend inwards to form a ceiling a couple of feet above you. " + 
        "A multitude of mushrooms are flourishing in the dank and gloomy " +
        "conditions.\n"); 

//    set_long("This is the elves mushroom garden. They grow a few varieties " +
//        "to add flavor to their meals. Players should be able to pick " + 
//        "some of these, which may have odd affects when eaten.\n"); 

    /*  Properties  */     

    add_prop(ROOM_I_LIGHT, 0); 

    /*  Exits  */ 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_06", "west"); 

    /* items */ 

    add_item(({"trees", "oaks", "forest"}), "Oddly enough, you can't see " + 
        "the trees of the forest from here. You have a sneaking suspicion " +
        "this might have something to do with the dense circle of shrubs " + 
        "that surrounds you.\n"); 

    add_item(({"shrubs", "circle", "wall", "ceiling", "dome"}), "These " + 
        "evergeen shrubs seem to be a bit out of place despite the fact " + 
        "that they are healthy and growing well. They form a tight circle " +
        "around this spot execept for a small gap leading west. Everyone " +
        "bends towards the center of the circle, where their very tops " + 
        "meet, forming a sort of domed ceiling that keeps light out and " +
        "water in.\n"); 

    add_item(({"mushrooms"}), "There are several varieties growing here, " +
        "thriving in the dark and damp environment. 
}
