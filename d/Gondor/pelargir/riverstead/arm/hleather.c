/*
 * This file is NCAMP_ARM + "hleather.c"
 */
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_armour() 
{
    set_name("leather armour");
    add_name("armour");
    add_name("leather");
    set_pname("armours");
    set_short("patched leather armour");
    set_pshort("patched leather armours");
    set_adj("leather");
    set_adj("patched");
    set_long("This armour looks to have been worn by a veteran of wars fought "
        + "long ago. Its leather is cracked and faded, and several holes are "
        + "covered with patches. It still feels as if it might turn a blade "
        + "or two.\n");
    set_default_armour(7, A_BODY, ({ 0, 1, -1}), 0);
    add_prop(OBJ_I_WEIGHT, 3800);
    add_prop(OBJ_I_VOLUME, 1100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(7) + random(24));
}
