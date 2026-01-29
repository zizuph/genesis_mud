
/*  

    The board room for Cadets of Gelan

    Coded by Maniac@Genesis, March 1997

    Copyright (C) Miguel Leith 1997

    Revised, 27/4/99, Maniac

*/

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <money.h>
#include "cadet.h"

#define SIGN_TEXT \
         "Xorfin draws your attention the guidelines of " + \
         "the cadet board. Do not spam the board e.g. do not post several " + \
         "short notes in a row where one will do. Do not post flames " + \
         "i.e. notes with an emphasis of conveying insults. Do not " + \
         "post notes containing profanities. Do not post any information " + \
         "about quests.\n"


int
gc_query_private_room()
{
    return 1;
}


void
create_room()
{
    set_short("Cadet discussion room");
    set_long("The focal point of the discussion room is a board on " +
             "the north wall, pinned to which is a collection of " +
             "parchments with articles about guild-related " +
             "matters. Fixed above it is a plaque. " +
             "Three windows set in the east wall let in the " +
             "daylight and provide a view of the school " +
             "courtyard. " +
             "An oak writing desk and chair sit beneath the central " +
             "window. On the desk is a pile of blank parchments, " +
             "a quill and a pot of ink.\n");  

    add_item(({"desk", "writing desk", "oak desk", "oak writing desk"}), 
             "The oak writing desk has a wide matt-varnished " +
             "surface. A pile of parchments sits on one side, " +
             "a pot of ink and a quill on the other.\n"); 

    add_item(({ "chair", "oak chair" }),  
             "The oak chair has a matt-varnished surface.\n"); 

    add_item(({"blank parchments", "pile", "pile of parchments", 
               "pile of blank parchments" }), 
             "The pile of blank parchments on the writing desk " +
             "is used in writing articles about guild matters to " +
             "pin on the discussion board.\n"); 

    add_item(({"parchments", "parchment" }),  
             "The parchments in this room are of decent quality, " +
             "they don't crumble or tear easily.\n");  

    add_item(({"collection", "articles"}), 
             "The articles are pinned to the board.\n"); 

    add_item(({"pin", "pins"}), 
             "They are drawing pins of various colours.\n");  

    add_item(({"pot of ink", "ink", "pot"}), 
             "The small earthenware pot is filled with black " +
             "ink.\n"); 

    add_item(({"quill"}), 
             "It's a black quill in good condition.\n"); 

    add_item(({"window", "windows"}), 
             "The windows on the east wall are square " +
             "with matt-varnished oak frames. " +
             "They provide a view of the school courtyard.\n"); 

    add_item(({"benches", "bench"}), 
             "Looking through a window, you see that the benches " +
             "around the edge of the inner area of the courtyard " +
             "are fixed sturdy wooden structures.\n"); 

    add_item(({"view", "school courtyard", "courtyard" }),  
             "Through a window you see a wide courtyard " + 
             "with elm trees growing in rows down either " +
             "side of a perimiter walkway paved with " +
             "rectangular beige stones. " + 
             "The inner courtyard has a gravel surface and " +
             "benches line its edge at regular intervals. " +
             "An oval pond, " +
             "which seems to be popular with the local " +
             "ducks and geese, occupies the centre of the " +
             "courtyard, surrounded by a bank of short grass. " +
             "Several students are out there in the sun.\n");  

    add_item(({"walkway", "perimiter walkway", "perimiter"}), 
             "Looking through a window, you see that the " +
             "perimiter walkway is a few yards wide. " +
             "Double doors open out onto it from the " +
             "school buildings on the north and south sides " +
             "of the courtyard.\n"); 

    add_item(({"elm tree", "elm trees", "elm", "elms" }), 
             "Looking through a window, you see that the " +
             "elms are still young and slender. Their branches " +
             "sway on the light breeze.\n"); 

    add_item(({"student", "students" }), 
             "Looking through a window, you see students " +
             "on the walkway, others sitting on benches " +
             "and others sitting on the bank of grass " +
             "next to the pond.\n"); 

    add_item(({"gravel", "gravel surface"}), 
              "Looking through a window, you see that that it's fine " +
              "packed gravel, consisting of light coloured stones.\n"); 

    add_item(({"beige stones", "rectangular beige stones", 
               "paving stones" }), 
              "Looking through a window, you see that the paving " +
              "stones are neatly swept save for a few elm leaves " +
              "and the gaps between them have been kept mostly " +
              "free of weeds.\n"); 

    add_item(({"pond", "oval pond"}), 
             "Looking through a window, you see that the oval pond " + 
             "has clear water that is still but for the ripples " +  
             "caused by ducks of geese. Sunlight glints on its surface, " +
             "which reflects the highest floors of the school buildings. " +
             "Around it is a bank of grass.\n"); 

    add_item(({ "bank", "grass", "bank of grass", "short grass",
                "bank of short grass" }), 
             "Looking through a window, you see that the bank of " + 
             "short grass has been neatly cut and grows densely.\n"); 

    add_item(({"duck", "ducks"}), 
             "Looking through a window, you see ducks " +
             "waddling around on the grass quacking hopefully at " +
             "students or swimming around in the pond quacking " +
             "uncertainly at geese.\n"); 

    add_item(({"goose", "geese"}), 
             "Looking through a window, you see geese " +
             "waddling around on the grass honking hopefully at " +
             "students or swimming around in the pond honking " +
             "irritably at ducks.\n"); 

    add_item(({"wall", "north wall", "south wall", "east wall", "west wall" }), 
              "The walls have matt-varnished oak panels.\n"); 

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({ "sign", "plaque" }), SIGN_TEXT);  
    add_cmd_item(({ "sign", "plaque" }), "read", SIGN_TEXT);  

    add_exit(GC_STARTROOM, "west"); 
    clone_object(GC_BOARD)->move(this_object()); 
}

