/*
 * /d/Calia/central/toad_in_oak/specials/stream.c
 *
 * This is an invisble stream object that people can drink from. 
 * This eliminates the old mess of using a .h 
 * 
 * HISTORY: [00-01-15] Created by Kcirderf  
 *
 * Copyright (C): Kcirderf 2000
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

// GLOBAL VARIABLES

string Object = "stream"; 
string Liquid = "water"; 
int Amount = 250; 

// FUNCTIONS 

/* Forward Declarations */ 

int drink(string command); 
void set_amount(int new_amount); 
void set_liquid(string new_liquid); 
void set_object(string new_object); 


/*  Function    drink
    Purpose     parses and executes players drink command
    Arguments   command typed by player
    Returns     Success */ 
int 
drink(string command) 
{
    object player = this_player(); 
    int success = 1; 

    if (command && 
        (parse_command(command, 
            this_object(), 
            "[" + Liquid + "] 'from' [the] '" + Object + "'") || 
        parse_command(command, 
            this_object(), 
            "'" + Liquid + "'")) )
    {
        if (player->drink_soft(Amount, 0))
        {

            write("You drink some " + Liquid + " from the " + Object + 
                ". It tases very refreshing.\n"); 
            say(QCTNAME(player) + " drinks some " + Liquid + " from the " + 
                Object + ".\n"); 
        }
        else
        {
            write("You're already full and have no room for any " + 
                Liquid + ".\n"); 
        }
    }
    else
    {
        success = 0;
    }

    return success; 
}

/*  Function    set_amount
    Purpose     Change the amount a person gets each time they drink    
    Arguments   integer new amount
    Returns     Nothing */ 
void
set_amount(int new_amount)
{
    Amount = new_amount; 
}

/*  Function    set_liquid
    Purpose     Change the name of what the player drinks
    Arguments   string new liquid
    Returns     Nothing */ 
void
set_liquid(string new_liquid)
{
    Liquid = new_liquid; 
}

/*  Function    set_object
    Purpose     Change the name of what the player drinks from
    Arguments   string new object
    Returns     Nothing */ 
void
set_object(string new_object)
{
    Object = new_object; 
}

// OBJECY DEFINITION

void 
create_object()
{
    set_name("stream"); 
    set_long("A crystal clear stream.\n"); 

    add_prop(OBJ_M_NO_GET, 1); 
    set_no_show_composite(1); 
}

void
init()
{
    ::init(); 

    add_action(drink, "drink"); 

    return;
}

