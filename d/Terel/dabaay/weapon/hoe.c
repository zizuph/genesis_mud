/*
 *  hoe.c
 *
 *  A garden hoe, wielded and/or used by halflings and kobolds
 *    in and around Dabaay
 *
 *  Goldberry June 1999
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

void
create_weapon()
{
    set_name(({"hoe"}));
    set_adj("garden");
    set_short("garden hoe");
    set_pshort("garden hoes");
    set_long(
        "A sturdy, well-made garden hoe.  The hardwood handle "+
        "shows evidence of lots of use.  The iron blade at the end "+
        "looks as though it could easily cleave through the toughest "+
        "of soils.  It might serve as a suitable weapon in a pinch.\n");

    set_default_weapon(21, 28, W_POLEARM, W_SLASH, W_BOTH, TO);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VALUE, 380);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(21,W_POLEARM)-random(250));
    add_prop(OBJ_I_VOLUME,query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(21,28)-random(50));

}

