/*
 * File name: steel_halberd.c
 * Ordinary steel halberd used by city guards in Palanthas.
 *
 * 9.11.2003
 * Blizzard
 */
 
inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("halberd");
    set_adj("long");
    add_adj("steel");
    add_name("polearm");
    set_short("long steel halberd");
    set_long("This is a six-foot long pole with an axe head mounted at the " +
        "top. It is extremely slow and is quite clumsy to wield, but the " +
        "damage its huge, arcing swings can inflict is unmatched.\n");
        

    set_hit(29);
    set_pen(38);
    set_wt(W_POLEARM);
    set_dt(W_SLASH);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29, 38));
}

