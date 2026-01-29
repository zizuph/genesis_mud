
/*
 *  Filename:       sword.c
 *  Description:    A sword for people riding the caravan
 *
 *
 *  Copyright (c) Dec. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("sword");
    set_adj(({"curved", "solamnian"}));
    set_short("curved solamnian sword");
    set_pshort("curwed solamnian swords");
    set_long("The sword looks quite deadly, with a curved blade poised " +
        "ready to strike. Some solamnian words are written on the side " +
        "of the handle, indicating it to be created in the smithy of a " +
        "solamnian city.\n");

    set_dt(W_SLASH);
    set_hands(W_ANYH);
    set_hit(35);
    set_pen(35);
    set_wt(W_SWORD);

    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 35));
}
