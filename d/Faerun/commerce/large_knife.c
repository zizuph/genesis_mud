/*
 * Sample commodity for commerce module
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

inherit "/std/weapon";
inherit "/d/Genesis/lib/commodity";

void
create_weapon()
{
    set_name("knife");
    set_adj(({"large", "sharp"}));

    set_short("large sharp knife");
    set_pshort("large sharp knives");
    set_long("This is a large sharp knife.\n");

    set_hit(20); /* this is to make aob gasp */
    set_pen(20); /* this is to make aoc gasp */

    set_commodity_name("large_knife");
    set_commodity_value(200); /* in cc */

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 500);
}
