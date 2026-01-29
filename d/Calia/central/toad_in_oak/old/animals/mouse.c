/*
 * /d/Calia/central/toad_in_oak/animals/mouse.c
 *
 * This is the famous long-tusked boar mouse of Calia. 
 *
 * HISTORY: [99-09-08] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/animals/base_animal";

#include <defs.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

#define A_BITE 0 
#define A_TUSK 1
#define H_HEAD 0 
#define H_BODY 1
#define H_TAIL 2

// GLOBAL VARIABLES

string* Colours = ({"white", "gray", "black", "brown"}); 

// FUNCTIONS

/*  Name:       toad_in_oak_mouse()
    Purpose:    Identifies this object as being a mouse.
    Arguments:  None
    Returns     1
*/ 
int 
toad_in_oak_mouse()
{
    return 1; 
}

// CREATURE DEFINITION

int
special_attack(object victim)
{
    object me = this_object(); 
    object here = environment(me); 

    if (! random(3))
    {
        tell_room(here, QCTNAME(me) + " decides that " + query_pronoun() + 
            "isn't interested in fighting.\n"); 
        
        perform_move(); 
    }

    return 1; 
}

void
create_tio_animal()
{
    string colour = Colours[random(sizeof(Colours))]; 
    int weight = 15 + random(25); 
    int volume = 65 + random(10); 

    set_name("mouse"); 
    set_race_name("mouse"); 
    set_adj(({"long-tusked", "tusked", "boar", colour})); 
    
    set_short("long-tusked boar mouse"); 
    set_pshort("long-tusked boar mice"); 
    set_long("This looks like any other mouse with its long whiskers, " + 
        "coarse " + colour + " fur, and long pink tail. That is, it looks " +
        "like any other mouse with two long boar-like tusks growing from " + 
        "its snout.\n"); 

    add_prop(OBJ_M_NO_GET, 0); 
    add_prop(OBJ_I_WEIGHT, weight); 
    add_prop(OBJ_I_VOLUME, volume); 
    add_prop(CONT_I_WEIGHT, weight); 
    add_prop(CONT_I_VOLUME, volume);

    set_act_time(8); 

    add_act_normal("emote squeeks."); 
    add_act_normal("emote sniffs around, looking for food."); 
    add_act_normal("emote twitches " + query_possessive() + " whiskers."); 
    add_act_normal("emote sits up and looks around for possible danger."); 

    set_m_out("scurries"); 
    set_m_in("scurries in"); 
    set_mm_out("runs off at high speed."); 
    set_mm_in("runs in at high speed and suddenly stops."); 

    set_home(TOAD_IN_OAK_ROOMS_LOW + "pub"); 
    set_restlessness(20); 

    set_attack_unarmed(A_BITE, 5, 5, W_IMPALE, 30, "bite"); 
    set_attack_unarmed(A_TUSK, 10, 10, W_IMPALE, 70, "tusks"); 
    set_hitloc_unarmed(H_HEAD, 5, 40, "head"); 
    set_hitloc_unarmed(H_BODY, 5, 40, "body"); 
    set_hitloc_unarmed(H_TAIL, 10, 20, "tail"); 

}


