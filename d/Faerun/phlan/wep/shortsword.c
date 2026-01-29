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

#define ADJ1        "plain"
#define ADJ2        "steel"
#define WEAPON_NAME "shortsword"
#define WEAPON      "sword"
#define WEP_TYPE    W_SWORD
#define DAMAGE      W_SLASH


int hit = 19+random(5),
    pen = 14+random(5);

void create_faerun_weapon()
{
    set_name(WEAPON_NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is a " + short() + ". The is two feet in length"
        +" with a blade designed for slashing and ability to be wielded"
        +" in either hand. The blade is made of average quality steel"
        +" and is sharpened on both sides. It has a brass crossguard to"
        +" protect the wielder's hand and a leather wrapped handle to"
        +" provide a firm grip.\n");

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
