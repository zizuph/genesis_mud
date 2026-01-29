/*
 * /d/Calia/central/toad_in_oak/animals/duck.c
 *
 * This is a duck to inhabit the pond in Toad-in-Oak. 
 *
 * HISTORY: [99-07-13] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/animals/base_animal";

#include <defs.h>
#include <stdproperties.h>

// GLOBAL VARIABLES

string *Allowed_Room = ({   "pond_surface", 
                            "pond_shore", 
                            "path_02", 
                            "path_03", 
                            "path_11"   }); 


// FUNCTIONS

/*  Name:       perform_move    (Why perform_move? to match perform_(c)act) 
    Purpose:    Moves the animal, usually at random. 
    Arguments:  None
    Returns:    Nothing
*/ 
void
perform_move()
{
    /*  Get the current room.  */ 
    object room = environment(this_object());
    string *exits; 
    int choice; 

    if (room -> toad_in_oak_pond_room()) 
    {
        exits = room->query_pond_exits(); 
        command(exits[random(sizeof(exits))]); 
            
    }
    else
    {
        ::perform_move(); 
    }

    return; 

}



/*  Name:       toad_in_oak_duck()
    Purpose:    Identifies this object as being a duck.
    Arguments:  None
    Returns     1
*/ 
int 
toad_in_oak_duck()
{
    return 1; 
}

// CREATURE DEFINITION

create_tio_animal()
{
    set_name("duck"); 
    set_race_name("duck"); 
    set_adj("white", "snow-white"); 

    set_short("snow-white duck"); 
    set_long("This duck is covered in snowy white feathers except for " + 
        query_possessive() + " webbed feet and long bill.\n"); 

    add_prop(OBJ_M_NO_ATTACK, "Leave the duck alone.\n"); 
    add_prop(OBJ_M_NO_GET, 0); 
    add_prop(OBJ_I_WEIGHT, 3000); 
    add_prop(OBJ_I_VOLUME, 3000); 
    add_prop(CONT_I_WEIGHT, 3000); 
    add_prop(CONT_I_VOLUME, 3000);
 
    set_act_time(5); 
    
    add_act_normal("emote quacks."); 
    add_act_normal("emote flaps " + query_possessive() + " wings."); 

    set_m_out("waddles"); 
    set_m_in("waddles in"); 
    set_mm_out("takes off and flies away."); 
    set_mm_in("lands on the ground nearby."); 
 
    set_home(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 
    set_restlessness(5); 

}
