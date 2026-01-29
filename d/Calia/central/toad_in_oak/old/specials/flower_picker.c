/*
 * /d/Calia/central/toad_in_oak/specials/flower_picker.c
 *
 * This object is used to allow the picking of flowers in a room.
 * 
 * HISTORY: [00-01-29] Created by Kcirderf  
 *
 * Copyright (C): Kcirderf 2000
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "../objects/flowers.h"

#define FLOWER TOAD_IN_OAK_OBJECTS + "hair_flower.c"

// FUNCTIONS

int
pick(string command)
{
    int success = 1;
    object player = this_player(); 
    object flower; 
    string type, colour, shade; 
    string* parts = explode(command, " "); 

    if(sizeof(parts) == 1) 
    {
        shade = "";
        colour = "";  
        type = parts[0]; 
    }
    else if(sizeof(parts) == 2)
    {
        shade = "";
        colour = parts[0];
        type = parts[1]; 
    }
    else if (sizeof(parts) == 3)
    {
        shade = parts[0]; 
        colour = parts[1]; 
        type = parts[2]; 
    }
    
    flower = clone_object(FLOWER);         

    if (type == "flower" || flower->set_flower(type))
    {
        if (colour != "" && !(flower->set_colour(colour)))
        {
            notify_fail("You can't find a " + colour + " " + type + ".\n"); 
            success = 0;
        }

        if (success && shade != "" && !(flower->set_adjective(shade)))
        {
            notify_fail("You can't find a " + shade + " " + colour + " " +flower + ".\n"); 
            success = 0; 
        }

        if (success && flower->move(player, 1) == 0) 
        {
            say(QCTNAME(player) + " picks a " + flower->query_short()) + ".\n"; 
            write("You pick a " + flower->query_short() + ".\n"); 
        }
        else
        {
            write("You can't carry anymore"); 
        }     
    }
    else
    {
        success = 0; 
    }

    return success;
}

// OBJECT DEFINITION

void 
create_object()
{
    set_name("flower_picker"); 
    set_long("This is invisible, so stop staring at it.\n"); 
    seteuid(getuid()); 

    add_prop(OBJ_M_NO_GET, 1); 
    add_prop(OBJ_I_INVIS, 100); 

}

void
init()
{
    ::init(); 

    add_action(pick, "pick"); 
    
    return;
}
