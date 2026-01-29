/*
 *  Scimitar for use by Daari Van Horn - high quality
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

#define ADJ1        "exotic"
#define ADJ2        "broad-bladed"
#define WEAPON_NAME "scimitar"
#define WEAPON      "sword"
#define WEP_TYPE    W_SWORD
#define DAMAGE      W_SLASH


int hit = 35 + random(5),
    pen = 45 + random(5);
void
create_faerun_weapon()
{

    set_name(WEAPON_NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is an " + short() + ". The bronzewood ivory handle"
        +" is affixed with polished brass pins, inlaid with silver. A cold"
        +" iron crossguard curves back slightly towards the hand of the wielder"
        +" and forward slightly along the spine of the weapon. The blade is"
        +" nearly three and a half feet long, curved, and widening closer to"
        +" the tip, before angling sharply to a point. This point not withstanding,"
        +" this sword is for cutting, not thrusting. Along the spine of the"
        +" blade are seven nickel rings which jingle as it is moved. Weighted"
        +" considerably towards the tip of the weapon, it is hard to recover"
        +" from a blow but should do considerable damage when it hits.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(pen,W_CLUB)+random(50)-25);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen)+random(20)-10);

    set_hands(W_BOTH); 
}
