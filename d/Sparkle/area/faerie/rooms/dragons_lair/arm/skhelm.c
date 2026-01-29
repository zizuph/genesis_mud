/*
 *
 * blackened tungsten helm.
 * Nerull, 21/2/09.
 */

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../defs.h";

inherit "/std/armour";

void
create_armour()
{
    set_name("helm");
    set_adj("tungsten");
    set_adj("blackened");
    set_short("blackened tungsten helm");
    set_long("This is a blackened helm of tungsten. It covers much " +
    "of the head and neck, and partically some of the lower facial " +
    "areas.\n");
    set_ac(40);
    set_at(A_HEAD);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE, 1450);
}
