/*
 * Rapier for questnpc5.
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

    set_name("rapier");
    add_name("cord");
    
    set_adj("thin");
    add_adj("sharp");
    
    set_short("thin sharp rapier");
    
    set_long("Like a neddle, this thin but sharp rapier "
    +"will have no issues piercing a heart or a lung "
    +"if used by a skilled swordsman. It is simple in "
    +"construction and shiny as if recently "
    +"polished. Definitely good craftmanship.\n");
    
    set_hit(32);
    set_pen(30);
    set_wt(W_SWORD); 
    set_dt(W_IMPALE); 

    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(32,30));

    set_hands(W_ANYH); 
}
