/* 
 * /d/Gondor/guilds/rangers/obj/leather_boots.c
 *
 * The travel-boots of the rangers of the north
 *
 * Gwyneth, 6 May 2004 - Updated
 */
inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("boots");
    add_name("armour");
    set_adj("ranger");
    set_adj("supple");
    set_adj("leather");
    set_adj("high");
    set_short("pair of supple leather boots");
    set_long("These high boots are nicely made of supple leather, " +
        "but have seen much wear, and are now caked with mud.\n");
    set_default_armour(8, A_ANKLES | A_FEET, (({ -1, 1, 0})), 0);

    add_prop(OBJ_I_WEIGHT, 360);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE,  F_VALUE_ARMOUR(8) + random(20));

    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
}
