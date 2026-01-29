/*
 * /d/Gondor/common/dwarf_guild/arm/b_apron.c
 *
 * This is the apron that is worn by the bartender in the pub.
 *
 * /Mercade 29 july 1993
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

#define ARMOUR_CLASS 2

void
create_armour()
{
    set_name("apron");
    set_pname("aprons");

    add_adj("white");
    add_adj("cotton");
    add_adj("small");

    set_short("white apron");
    set_pshort("white aprons");

    set_long(BSN("This is an apron, use by bartenders. It is rather small " +
        "and made of white cotton. On it you see embroidery."));

    add_item( ({ "embroidery" }),
        BSN("The embroidery is made of crewel and it depicts a dwarf in " +
        "a traditional bartenders uniform. It was embroided with great " +
        "patience and skill."));

    set_ac(ARMOUR_CLASS);
    set_at(A_WAIST);
    set_am( ({ 0, 0, 0 }) );

    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE,  F_VALUE_ARMOUR(ARMOUR_CLASS) + random(51) - 25);
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