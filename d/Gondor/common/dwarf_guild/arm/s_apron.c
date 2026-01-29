/*
 * /d/Gondor/common/dwarf_guild/arm/s_apron.c
 *
 * This is the apron that is worn by the smith in the dwarf guild.
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

#define ARMOUR_CLASS 20

void
create_armour()
{
    set_name("apron");
    set_pname("aprons");

    add_adj("leather");

    set_short("leather apron");
    set_pshort("leather aprons");

    set_long(BSN("This is an apron, specially designed for and used by " +
        "blacksmith' It is made of leather and consists of several layers."));

    set_ac(ARMOUR_CLASS);
    set_at( (A_BODY | A_LEGS) ); /* Is this possible? */
    set_am( ({ -2, 1, 1 }) );

    add_prop(OBJ_I_WEIGHT, 6200);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE,  F_VALUE_ARMOUR(ARMOUR_CLASS) + random(151) - 75);
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