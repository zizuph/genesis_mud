/*
 * Sword for the Lizardmen
 * by Finwe, July 2005
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

int hit = 40,
    pen = 40;
void
create_faerun_weapon()
{

    set_name("sword");
    set_adj("ancient");
    set_adj("steel");
    set_short("ancient steel sword"); 
    set_long("This is a " + short() + ". It looks like it has been in " +
        "countless battles, and laid forgotten. There are a few nicks " +
        "in the blade but looks like it is still deadly. \n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 

    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));

    set_hands(W_ANYH); 
}
