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

#define ADJ1        "ancient"
#define ADJ2        "slender"
#define WEAPON      "shortsword"
#define WEP_TYPE    W_SWORD
#define DAMAGE      W_SLASH | W_IMPALE

int hit = 28 + random(10),
    pen = 28 + random(10);
void
create_faerun_weapon()
{
    set_name("sword");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This is a " + short() + ". The blade is made of steel and " +
        "looks deadly. Both edges are sharpened. A narrow groove runs " +
        "from the hilt to the tip of the blade.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit,pen) + random(50) - 20);

    set_hands(W_ANYH);
}
