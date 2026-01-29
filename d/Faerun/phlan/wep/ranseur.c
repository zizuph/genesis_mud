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

#define ADJ1        "long"
#define ADJ2        "steel-bladed"
#define WEAPON_NAME "ranseur"
#define WEAPON      "polearm"
#define WEP_TYPE    W_POLEARM
#define DAMAGE      W_IMPALE



int hit = 24 + random(5),
    pen = 26 + random(5);

void create_faerun_weapon()
{
    set_name(WEAPON_NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is a " + short() + ". The eight foot long wooden"
        +" pole is capped with a slender, tapering, double-edged spear"
        +" blade with two long flukes about half the length of the spear"
        +" point. Mostly used in formation with other long polearms,"
        +" it can service by itself in the hands of a skilled wielder.\n");
        
    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(pen,W_SWORD)+random(50)-25);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen)+random(20)-10);

    set_hands(W_BOTH); 
}
