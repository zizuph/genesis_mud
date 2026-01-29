/*
 * This file is NCAMP_ARM + "hhelm.c"
 */
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour() 
{
    set_name(({"helm","tall helm","helmet","tall helmet"}));
    set_pname("helms");
    add_pname("helmets");
    set_short("tall helm");
    set_adj("tall");
    set_pshort("tall helms");
    set_long("This helmet looks old and tarnished from years of disuse. It "
        + "looks like it would still protect your skull.\n");
    set_default_armour(8, A_HEAD, ({ -2, 1, 1, }), 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR( 8, A_HEAD) + random(501));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8) + random(25));
}
