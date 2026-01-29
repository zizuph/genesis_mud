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

#define ADJ1 "slender"
#define ADJ2 "ivory-inlaid"
#define WEAPON  "short sword"

int hit = 35 + random(5),
    pen = 35 + random(5);
void
create_faerun_weapon()
{

    set_name("sword");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This is a " + short() + ". The weapon looks old and probably " +
        "belonged to a noble at one time. The blade is still sharp and " +
        "has a few knicks in it. The ivory is set into the handle, and " +
        "is carved into the shape of fancy scrollwork.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 

    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));

    set_hands(W_ANYH); 
}
