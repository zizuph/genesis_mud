/*
 * Dagger for the Assassins in the cave in the
 * Mere of Dead Men
 * by Nerull, 2019
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

#define DAGGER_ENCHANTED    "_dagger_enchanted"


void
create_faerun_weapon()
{
    add_name("dagger");
    set_adj("curved");
    set_adj("steel");
    set_short("curved steel dagger"); 
    
    set_long("This is a " + short() + ". It fits nicely in your hand and " 
        +"is perfectly balanced. The slight curve of the blade makes it a "
        +"fine weapon to slice arteries with or perforate "
        +"ribcages.\n");

    set_hit(20);
    set_pen(20);
    set_wt(W_KNIFE); 
    set_dt(W_SLASH | W_IMPALE); 

    add_prop(OBJ_I_WEIGHT,1700);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,20) + random(50) - 20);

    set_hands(W_ANYH);
}


// This dagger don't dull unless
int
set_dull(int du)
{
    if (this_object()->query_prop(DAGGER_ENCHANTED) == 1)
    {
        return 0;
    }
    
    return 1;
}
