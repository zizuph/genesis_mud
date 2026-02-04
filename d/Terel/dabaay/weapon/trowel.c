/*
 *  trowel.c
 *
 *  A small trowel, wielded and/or used by halflings and kobolds
 *    in and around Dabaay
 *
 *  Goldberry July 1999
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

void
create_weapon()
{
    set_name(({"trowel"}));
    set_adj("small");
    set_short("small trowel");
    set_pshort("small trowels");
    set_long(
        "A small trowel with an iron blade and a wooden handle. "+
        "Suitable for digging small holes and tending to the "+
        "finer details of a good garden, this trowel has a nice "+
        "balance to it. It might serve as a suitable weapon in "+
        "a pinch.\n");

    set_default_weapon(10,10,W_KNIFE,W_SLASH|W_IMPALE,W_ANYH,TO);
    add_prop(OBJ_I_VOLUME,query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10,10)-random(25));
}

