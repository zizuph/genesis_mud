/*
 *  A simple gold ring.
 *
 *  Arman, January 2021.
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"

inherit "/lib/keep";

#define ARMOUR_CLASS 1

void
create_armour()
{
    set_name("ring");
    set_pname("rings");
    set_adj("gold");
    set_short("gold ring");
    set_pshort("gold rings");
    set_long("This is a simple unadorned ring of gold.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_FINGERS);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS) + 500);
}
