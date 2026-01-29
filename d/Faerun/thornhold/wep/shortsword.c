/*
 * Sword for Lances
 * -- Finwe, September 2008
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

#define ADJ1        "stout"
#define ADJ2        "steel"
#define WEAPON_NAME "shortsword"
#define WEAPON      "sword"
#define WEP_TYPE    W_SWORD
#define DAMAGE      W_SLASH | W_IMPALE


int hit = 25+random(5),
    pen = 30+random(5);

void create_faerun_weapon()
{
    set_name(WEAPON_NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is a " + short() + ". The blade is wide and forged of steel, etched with common dwarven runes. Both edges have been sharpenend making it good for slashing and cutting. The handle is long and made from a dark wood, and the hilt is made of steel.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2000);

    set_hands(W_ANYH); 
}

void
init()
{
    ::init();
}
