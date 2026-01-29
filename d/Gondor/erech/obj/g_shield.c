/*
 * g_shield.c
 * By Skippern
 * June 2000
 */
inherit "/std/armour";

#include "../erech.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
    set_name("shield");
    set_short("round tarished shield");
    set_pshort("round tarished shields");
    set_adj("round");
    add_adj("tarished");
    set_long("This round shield is tarished by time, it is dificoult to " +
        "make out any paintings or symbols on it. Between the rusty spots " +
	"some small spots of paint can be seen. The shield have most " +
	"likely been painted white.\n");

    set_default_armour(20,A_SHIELD,({ -1, 1, 0}),0);

    add_prop(OBJ_I_WEIGHT, 2800);
    add_prop(OBJ_I_VOLUME, 860);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20) + random(10) - 30);
}
