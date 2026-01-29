/*
 * Mace for the Lizardmen
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

#define ADJ1        "rusty"
#define ADJ2        "spiked"
#define WEAPON      "mace"
#define WEP_TYPE    W_CLUB
#define DAMAGE      W_BLUDGEON | W_IMPALE



int hit = 35 + random(5),
    pen = 35 + random(5);
void
create_faerun_weapon()
{

    set_name("club");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This is a " + short() + ". The handle is long and made of" +
        "iron. It is topped with a spiked ball. The weapon is rusty from " +
        "age, but still dangerous looking. There is some dried blood on " +
        "the spiked ball.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));

    set_hands(W_ANYH); 
}
