/*
 * Weapon for the halfling guards
 * by Finwe, December 2015
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

#define ADJ1        "double-bladed"
#define ADJ2        "steel"
#define WEAPON      "axe"
#define WEP_TYPE    W_AXE
#define DAMAGE      W_SLASH



int hit = 30 + random(5),
    pen = 25 + random(5);

void create_faerun_weapon()
{
    set_name("battleaxe");
    add_name("battle axe");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This is a " + short() + ". It has two crescent blades attached to a steel rod which is connected to a wooden shaft. The shaft is made from dark wood and has a steel cap on the bottom. On each blade is etched a faceted gem.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));

    set_hands(W_ANYH); 
}
