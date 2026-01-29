
/* 
 *  /d/Calia/fireball/obj/ball.c 
 * 
 *  This is the ball to be used in Fireball.  
 * 
 *  Coded by Maniac@Genesis, 23/7/97
 *  Revised by Maniac, May 1998, June 1998
 *   
 *  Copyright (C) Miguel Leith 1997/1998
 */ 

#include "defs.h"
#include FIREBALL_HEADER

inherit "/std/object"; 

#include <stdproperties.h>
#include <macros.h>
#include <const.h>

object current_dribbler; 
int active; 


void
create_object()
{
    set_name("ball"); 
    add_name("ball"); 
    set_long("It is a spherical ball made of several layers of " +
             "thick leather wrapped around an inflated pig's bladder. " +
             "You can dribble or kick it, but picking it up is against " +
             "the rules.\n"); 
    add_prop(OBJ_I_VOLUME, 5000);  
    add_prop(OBJ_I_WEIGHT, 5000);   
    add_prop(OBJ_M_NO_GET, "It's against game rules to pick up the " +
                           "ball.\n"); 
    current_dribbler = 0; 
    set_adj("void");
    active = 0;  
    seteuid(getuid()); 
}


void
set_active()
{
    object ball; 

    seteuid(getuid()); 
    ball = FIREBALL_GAME_HANDLER->query_ball(); 
    if (objectp(ball) && (ball == this_object()))  {
        remove_adj("void"); 
        add_name(FIREBALL_BALL_ID); 
        active = 1; 
    } 
}


void
enter_env(object dest, object old)
{
    ::enter_env(dest, old); 
    if (active)
        FIREBALL_GAME_HANDLER->update_ball_location(this_object(), 
                                                    old, dest); 
}


/*
 * Function:     query_current_dribbler
 * Description:  Returns the player currently dribbling the ball
 */ 
object
query_current_dribbler()
{
    if (!objectp(current_dribbler))
        return 0;

    if (!objectp(present(current_dribbler, environment(this_object()))))
        current_dribbler = 0; 

    return current_dribbler; 
}


/*
 * Function:     set_current_dribbler
 * Description:  Sets the player currently dribbling the ball
 */ 
void
set_current_dribbler(object ncd)
{
    current_dribbler = ncd; 
}

