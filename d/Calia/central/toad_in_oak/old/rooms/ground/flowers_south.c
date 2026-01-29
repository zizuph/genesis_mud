/*
 * /d/Calia/central/toad_in_oak/rooms/ground/garden_flower_south.c
 *
 * This is the southern corner of the Toad-in-Oak flower garden
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

#define STREAM TOAD_IN_OAK_OBJECTS + "stream.c"

// GLOBAL VARIABLES

object Stream; 

// ROOM DEFINITION

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("The Toad-in-Oak flower garden"); 

    set_long("This is the Toad-in-Oak flower garden. It will be full of " + 
        "colourful flowers. There will be common flowers of many types for " + 
        "mortals to pick, and a few rare unique types. Somewhere in the " + 
        "area there should be a few benches and so on. Butterflies will " + 
        "move around here, and there may be a florist of sorts. This rooms " +
        "particular needs to have the stream and a bridge.\n"); 

    /*  Properties  */     

    add_prop(ROOM_I_TYPE, ROOM_BEACH); /*   Not a true beach, but 
                                            next to a stream. */ 
    add_prop(OBJ_I_CONTAIN_WATER, -1); /*   Infinite water due to the stream */ 

    /* Obejects */ 

    Stream = clone_object(STREAM); 
    Stream->move(this_object(),1); 
//    Stream->set_long("The water of the small stream is clear and bright, " +
//        "and sparkles as it flows into the pond.\n"); 
    Stream->set_adjectives(({"clear", "small", "sparkling"})); 
    Stream->add_item(({"water", "sparkling water"}), Stream->query_long()); 

    /*  Exits  */ 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_east" , "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_01" , "northeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_09" , "south"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_west", "northwest");     

    /* items */ 

}
