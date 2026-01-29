/*
 *  Generic weapons for Phlan shops
 *  Tharizdun, 2021
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

#define ADJ1        "fullered"
#define ADJ2        "steel"
#define WEAPON_NAME "longsword"
#define WEAPON      "sword"
#define WEP_TYPE    W_SWORD
#define DAMAGE      W_SLASH


int hit = 27+random(5),
    pen = 24+random(5);

void create_faerun_weapon()
{
    set_name(WEAPON_NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is a " + short() + ". Nearly four feet long with a"
        +" pointed double-edged blade, this is a slashing weapon. Fullers, or"
        +" grooves along the sides of the blade give it more resilience to"
        +" withstand strong impact even against plate armours. A brass"
        +" crossguard protects the wielder's hand while a round brass pommel"
        +" helps balance the weight for a quicker recovery time. The handle"
        +" is of leather wrapped wood, fitted for a single hand to wield.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(pen,W_SWORD)+random(50)-25);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen)+random(20)-10);

    set_hands(W_ANYH); 
}

void
init()
{
    ::init();
}
