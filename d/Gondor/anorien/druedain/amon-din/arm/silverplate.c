/*
 *  /d/Gondor/anorien/druedain/amon-din/arm/steelplate.c
 *
 *  Armour for the beacon attendant
 *  Gorboth, January 1996
 */
#pragma strict_types
inherit "/std/armour";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("breastplate");
    add_name( ({ "plate", }) );
    set_short("polished silver breastplate");
    set_adj(({"polished", "silver"}));

    set_long(BSN("This breastplate is of a craftsmanship which has"
        + " been lost or forgotten in Gondor. Embossed in its"
        + " glittering silver surface is a tree crowned with seven"
        + " stars. Such armour is either reserved for the very finest"
        + " soldiers in the Steward's army, or passed down through"
        + " generations of Dunadan heritage."));

    set_default_armour(38, A_BODY, ({0,0,0}), TO);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(38)+random(750)+400);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(38,A_BODY)+random(1400)-700);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
}
