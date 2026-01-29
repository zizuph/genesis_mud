/*
 * Weapon for the Insectmen in Kryptgarden
 * by Finwe, August 2006
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

#define ADJ1        "large"
#define ADJ2        "double-bladed"
#define WEAPON      "axe"
#define WEP_TYPE    W_AXE
#define DAMAGE      W_SLASH



int hit = 35 + random(5),
    pen = 35 + random(5);

void create_faerun_weapon()
{
    set_name("battleaxe");
    add_name("battle axe");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This is a " + short() + ". It was forged by dwarves ages ago " +
        "and plundered from, one of their hordes. The blade is made of " +
        "steel and set on a sturdy iron handle.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));

    set_hands(W_ANYH); 
}
