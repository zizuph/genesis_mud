/*  
 * /d/Gondor/guilds/rangers/obj/travel_boots.c
 *
 * Coded by ?
 *
 * The travel-boots of the Rangers of the North
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
    add_adj(({"high", "leather"}));
    set_short("pair of high boots");
    set_pshort("pairs of high boots");
    set_long("These high boots are made of nice supple leather, but " + 
        "have seen much wear, and are now caked with mud.\n");
    set_af(TO);
    set_default_armour(5, A_LEGS | A_ANKLES | A_FEET, (({ -1, 1, 0})), 0);
    add_prop(OBJ_I_WEIGHT, 360);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5)+random(20));
}

mixed
wear(object ob)
{
    write("You wear the " + query_short() + " on your feet and " +
        "legs.\n");
    say(QCTNAME(TP) + " wears the " + query_short() + ".\n");
    return 1;
}
