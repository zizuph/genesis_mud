/*
 * orc weapon for Kryptgarden
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

#define ADJ1        "bloody"
#define ADJ2        "steel"
#define WEAPON_NAME "morningstar"
#define WEAPON      "club"
#define WEP_TYPE    W_CLUB
#define DAMAGE      W_BLUDGEON


int hit = 35,
    pen = 35;

void create_faerun_weapon()
{
    set_name(WEAPON_NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is a " + short() + ". It resembles a mace. It has a long handle with a spiked ball set on the top. The handle is wrapped in leather. The ball has several long spikes sticking out from it. There are flecks of dried blood and flesh on the tips of some of the spikes.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));

    set_hands(W_ANYH); 

}

void
init()
{
}
