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

#define ADJ1        "steel"
#define ADJ2        "arming"
#define WEAPON_NAME "sword"
#define WEAPON      "sword"
#define WEP_TYPE    W_SWORD
#define DAMAGE      W_SLASH || W_IMPALE


int hit = 23+random(5),
    pen = 19+random(5);

void create_faerun_weapon()
{
    set_name(WEAPON_NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is a " + short() + ". Slightly shorter than a longsword"
        +" and often called a knightly sword, this is the preferred weapon"
        +" used as a side-arm when fighting heavily armoured opponents. Thus"
        +" a knight would often use it as the back up for their lance. It is"
        +" just short of two and a half feet long with a straight blade"
        +" sharpened on both sides. It is both a slashing and stabbing"
        +" weapon. It is one handed and has a simple cruciform hilt with"
        +" pommel.\n");

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
