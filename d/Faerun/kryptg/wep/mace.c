/*
 * Weapon for the Insectmen in Kryptgarden
 * by Finwe, August 2006
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

#define ADJ1        "fine"
#define ADJ2        "steel"
#define WEAPON      "mace"
#define WEP_TYPE    W_CLUB
#define DAMAGE      W_BLUDGEON | W_IMPALE



int hit = 35,
    pen = 35;

void create_faerun_weapon()
{
    set_name("mace");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This is a " + short() + ". This sturdy weapon is crafted " +
        "out of high-steel, and has been fashioned in such a way that it " +
        "is balanced perfectly. The mace was forged by ancient dwarves " +
        "and plundered from one of their hordes. A large ball is set " +
        "on a metal handle.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen)-500);

    set_hands(W_ANYH); 
}
