
/* 
   This is the standard fish meat to go on sea creatures.
   Other features will probably be added at a later date. 

   Coded by Maniac 24/9/96

   Modified, Maniac, 28/9/96, 3/10/96
*/ 

#pragma save_binary

inherit "/std/food"; 

#include <stdproperties.h>

#define FOOD_VALUE(am) (3 + ((am * am) / 600)) 

void
create_fish_meat()
{
}

nomask void
create_food()
{
    remove_prop(OBJ_M_NO_SELL); 
    create_fish_meat(); 
    add_prop(HEAP_I_UNIT_VALUE, FOOD_VALUE(query_amount())); 
    add_prop(HEAP_I_UNIT_VOLUME, query_prop(HEAP_I_UNIT_WEIGHT)); 
}

void
config_split(int new_num, mixed orig)
{
    ::config_split(new_num, orig);
    add_prop(OBJ_M_NO_SELL, orig->query_prop(OBJ_M_NO_SELL)); 
    add_prop(HEAP_I_UNIT_VOLUME, orig->query_prop(HEAP_I_UNIT_VOLUME)); 
    add_prop(HEAP_I_UNIT_VALUE, FOOD_VALUE(query_amount())); 
}

