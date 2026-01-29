/*
 * ancient dwarven battleaxe
 * wielded by revenants of Kryptgarden
 * This is the non-magical version
 * -- Finwe, October 2007
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
#define ADJ2        "steel"
#define WEAPON_NAME "battleaxe"
#define WEAPON      "axe"
#define WEP_TYPE    W_AXE
#define DAMAGE      W_SLASH


int hit = 35,
    pen = 35;

void create_faerun_weapon()
{
    set_name(WEAPON_NAME);
    add_name("battle axe");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is a " + short() + ". It has two half moon shaped blades attached to a long handle. The blades are razor sharp and strong enough to cleave an enemy in two. Forged in ages long past, it has still retained its edge even though the weapon looks scratched from countless battles.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, 8500);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));

    set_hands(W_ANYH); 

}

void
init()
{
}
