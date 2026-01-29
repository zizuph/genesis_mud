/*
    /d/Calia/argos/nowhere/objects/lemon.c

    This is a lemon that can be picked from the tree in Nowhere. 
    (/d/Calia/argos/nowhere/rooms/ouside/road_02.c)

    HISTORY:    2003-07-18 - Created by Kcirderf

    Copyright: Sean Dunphy (Kcirderf) 2003
*/ 

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit "/d/Calia/std/fruit.c"; 

// OBJECT DEFINITION

void 
create_fruit()
{
    set_name("lemon"); 
    add_name("fruit"); 
    set_adj(({"ripe", "yellow", "round"})); 
    set_short("yellow lemon");
    set_long("A nice round ripe yellow lemon.\n"); 
    set_fruit_amount(7); 
    set_mana_add(0); 
    set_hp_add(5); 
    set_fatigue_add(10); 
}




