/*
 * /d/Gondor/common/dwarf_guild/arm/k_sweater.c
 *
 * This sweater is worn by the shopkeeper in the dwarven race guild.
 * It is a sweater lined with metal rings, making it stronger than one
 * made of wool.
 *
 * /Mercade, 3 august 1993
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define ARMOUR_CLASS 25

void
create_armour()
{
    set_name("sweater");
    add_name("mail");

    set_adj("comfortable");
    add_adj("wool");
    add_adj("ringed");

    set_short("comfortable wool sweater");
    set_pshort("comfortable wool sweaters");

    set_long(BSN("This sweater is made of wool and looks very comfortable. " +
        "And it is comfortable. However on the inside you see that it also " +
        "is a ring mail with many small metal rings making this sweater to " +
        "a rather good mail."));

    add_item( ({ "rings", "metal rings", "small rings", "small metal rings" }),
        BSN("The small metal rings make these pants into a strong pair of " +
        "greaves."));

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ -2, 4, -2 }) );

    add_prop(OBJ_I_WEIGHT, 5400);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(151) - 75);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
