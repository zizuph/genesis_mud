
/*
 *  Filename:       hammer.c
 *  Description:    A hammer for people riding the caravan
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
    set_name("hammer");
    set_adj(({"flat-headed", "steel"}));
    set_short("flat-headed steel hammer");
    set_pshort("flat-headed steel hammers");
    set_long("The tree handle leads up to a flat-headed steel head " +
        "giving quite good damage on impact. The hammer seems designed " +
        "as a working tool, but enhanced with a better head and a better " +
        "grip, allowing for bigger damage.\n");

    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_hit(34);
    set_pen(35);
    set_wt(W_CLUB);

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(34, 35));
}
