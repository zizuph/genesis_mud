/*
 * Scimitar for Troll Patrols in Underdark
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
    add_name("scimitar");
    set_adj("sharp");
    set_adj("bloody");
    set_short("sharp bloody scimitar"); 
    set_long("This is a " + short() + ". The blade is wide and slightly " +
        "curved and used most often by goblins. The blade has blood on " +
        "it from recent fights.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 

    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));

    set_hands(W_ANYH); 
}
