/*
 * /d/Gondor/guilds/rangers/obj/ith_gauntlets.c
 *
 * Coded by ?
 *
 * A pair of gauntlets sold in the Ithilien shop.
 */
inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("pair of gauntlets");
    add_name("gauntlets");
    add_name("armour");
    add_name("pair");
    set_adj("ranger");
    set_adj("green");
    set_short("pair of green gauntlets");
    set_long("This is a pair of green gauntlets. \n");
    set_default_armour(16, A_HANDS, (({ -1, -1, 2})), 0);
    add_prop(OBJ_I_WEIGHT, 360);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(16) + random(20));
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
