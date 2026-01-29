/* -*- Mode: C -*-
 *
 * obj/arm/cloak.c
 *
 * Skippern 20(c)02
 *
 */
inherit "/std/armour";

#include <formulas.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define ARM 2

void
create_armour()
{
    set_name("cloak");
    add_name("ArguckAssassinItem");
    set_adj("dark");
    set_short("dark cloak");
    set_pshort("dark cloaks");
    set_long("This is a dark robe.\n");

    set_default_armour(ARM, A_ROBE, (({ 0, 3, 1})), 0);

    add_prop(OBJ_I_WEIGHT, 550);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARM) + random(20) - 5);
}
