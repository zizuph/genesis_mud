
/* 
    ~Calia/fireball/inherit/outside_room.c

    The inheritable room for Firedrome rooms outside the arena. 

    Coded by Maniac@Genesis, 1997/1998

    Copyright(C) Miguel Leith 1997/1998. 
*/ 

#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <language.h> 
#include <macros.h>
#include "defs.h"
#include FIREBALL_HEADER

inherit "/std/room";
inherit FIREBALL_HELP_SUPPORT; 

nomask int
check_fireball_outside_room() 
{
    return 1;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 
    if (!IS_FIREBALL_OUTSIDE_ROOM(from) && living(ob))      
        FIREBALL_GAME_HANDLER->enter_outside(ob, from, this_object()); 
}


void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest); 
    if (!IS_FIREBALL_OUTSIDE_ROOM(dest) && living(ob))      
        FIREBALL_GAME_HANDLER->leave_outside(ob, this_object(), dest); 
}

void
init()
{
    ::init(); 
    init_help_support(); 
}
