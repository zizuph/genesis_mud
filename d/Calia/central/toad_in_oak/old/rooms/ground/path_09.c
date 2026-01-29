/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_09.c
 *
 * A path on the ground level of Toad-in-Oak, on the eastern side of the 
 * village itself. This is one of only two places where the stream can be
 * crossed
 *
 * HISTORY: [99-03-10] Created by Kcirderf 
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
void create_tio_ground_room()
{

    set_short("A path beneath a village in the trees"); 

    set_long("You are standing next to a small stream that runs " + 
        "between the massive oaks that dominate this part of " + 
        "the forest. There is little light here, but green grass " + 
        "covers the ground between the trees anyway. To the north " + 
        "a small wooden bridge crosses the stream here, leading " + 
        "to an area filled with colourful flowers.\n"); 

    /*  Properties  */ 

    add_prop(ROOM_I_TYPE, ROOM_BEACH); /*   Not a beach beach, but by 
                                            a stream */ 
    add_prop(OBJ_I_CONTAIN_WATER, -1); 

    /* Obejects */ 

    Stream = clone_object(STREAM); 
    Stream->move(this_object(),1); 
    Stream->set_long("A babbling stream of sparkling water flows under " + 
        "the bridge and towards the west. The water is crystal " + 
        "clear, allowing you to see every detail of the stream " + 
        "bed.\n"); 
    Stream->set_adjectives(({"clear", "small", "sparkling"})); 
    Stream->add_item(({"water", "sparkling water"}), Stream->query_long()); 

    /*  Exits  */ 

    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "flowers_south", "north"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_08", "southwest"); 

    
    /*  Items  */ 

    add_item(({"path", "trail", "grass"}), 
        "The grass here is green and healthy despite the poor " + 
        "light. You can make out a faint path through the grass " + 
        "that starts at the bridge and leads towards the " + 
        "southwest.\n"); 

    add_item(({"trees", "tree", "oaks", "oak", "branches"}), 
        "The trees here are large and strong, " + 
        "supporting an entire village among their branches. They " + 
        "reach high into the sky and greedily intercept most of " + 
        "the sunlight before it can get to you down here.\n"); 

    add_item(({"village", "walkways"}), 
        "All you can see of the village from this angle is the " +
        "underside of the walkways that connect the trees.\n"); 

    add_item(({"bed", "bottom", "stream bed", "rocks", "mud", 
        "sand"}), 
        "The bottom of the stream consists of rocks, mud, " + 
        "pebbles, and sand. A red fish is swimming around under " + 
        "the bridge. You think that it may be a herring of some " + 
        "sort.\n"); 

    add_item(({"fish", "herring", "red herring", "trout", "red trout"}), 
        "Upon closer inspection it turns out that the fish is " +
        "only a red trout, not the elusive red herring.\n"); 

    add_item(({"bridge", "root"}), 
        "This remarkable little bridge crosses the stream in a " + 
        "graceful arch. The surface is flat and wide except at " + 
        "the very edges, which curve upwards to prevent anyone " + 
        "from falling off. You find no sign of the wood being " + 
        "joined anywhere, as if it was carved from a single piece " +
        "of wood.\n"); 

    add_item(({"flowers"}), 
        "You can see a great number of flowers growing among the " +
        "trees on the far side of the stream, filling the area " + 
        "with colour.\n");  
}
