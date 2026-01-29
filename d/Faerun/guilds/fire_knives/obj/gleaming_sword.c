/*
 * Gleaming sword for questnpc1.
 *
 * Nerull 2019 
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

void
create_faerun_weapon()
{

    set_name("broadsword");
    add_name("sword");
    set_adj("gleaming");
    
    set_short("gleaming broadsword");
    
    set_long("This masterwork weapon is obviously a special "
    +"commission for a ranking officer. On the blade some words "
    +"seem to have been written.\n");
    
    add_item(({"words"}),
    "The words says: I solemnly swear to serve Cormyr and her interests above all "
    +"else. I vow to answer any call from the crown, the royal "
    +"family, recognized nobles, and citizens in need, to the "
    +"best of my ability. I promise that in time of war, I will "
    +"return to my sworn position and bear arms in service to "
    +"crown and country.\n");
    

    set_hit(35);
    set_pen(39);
    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 

    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35,39));

    set_hands(W_ANYH); 
}
