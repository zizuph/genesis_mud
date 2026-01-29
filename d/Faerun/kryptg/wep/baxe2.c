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

#define ADJ1        "serrated"
#define ADJ2        "steel"
#define WEAPON      "battleaxe"
#define WEP_TYPE    W_AXE
#define DAMAGE      W_BLUDGEON | W_SLASH



int hit = 35 + random(5),
    pen = 35 + random(5);

void create_faerun_weapon()
{
    set_name("battleaxe");
    add_name("battle axe");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON);
    set_long("This is a " + short() + ". The battleaxe was forged by ancient dwarves and plundered from one of their hordes. Its huge serrated blades are sharpened to a razored edge, and jagged runes have been cut into its haft.\n");

    add_item(({"runes"}),
        "They are cut into the haft of the battle axe. The runes are a set of symbols that glow slightly in the light.\n");
    add_item(({"haft", "handle"}),
        "The handle is made of smooth wood. Jagged runes have been carved into it.\n");


    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE);
    set_dt(DAMAGE);

    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen)-500);

    set_hands(W_ANYH);
}
