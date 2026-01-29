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

#define ADJ1        "rusty"
#define ADJ2        "iron"
#define WEAPON_NAME "falchion"
#define WEAPON      "sword"
#define WEP_TYPE    W_SWORD
#define DAMAGE      W_SLASH


int hit = 35,
    pen = 35;

void create_faerun_weapon()
{
    set_name(WEAPON_NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is a " + short() + ". The blade is a single-edge sword with a slight curve on the blade towards the point. The handle is short and made of dark metal. The crossguard is twisted and extends upwards slightly.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2000);
//    add_prop(OBJ_I_VALUE,700+random(200));

    set_hands(W_ANYH); 

}

void
init()
{
}
