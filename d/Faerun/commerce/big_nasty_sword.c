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
    set_name("sword");
    set_adj(({"big", "nasty"}));

    set_short("big nasty sword");
    set_pshort("big nasty swords");
    set_long("This is a big and nasty sword.\n");

    set_hit(150); /* this is to make aob gasp */
    set_pen(-40); /* this is to make aoc gasp */

    set_commodity_name("big_nasty_sword");
    set_commodity_value(3000); /* in cc */

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
}
