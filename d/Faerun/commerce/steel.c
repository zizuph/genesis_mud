/*
 * Sample commodity for commerce module
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

inherit "/std/object";
inherit "/d/Genesis/lib/commodity";

void
create_object()
{
    set_name("steel");
    set_adj(({"small", "steel"}));

    set_short("small steel ingot");
    set_pshort("small steel ingots");
    set_long("This is a small steel ingot.\n");

    set_commodity_name("faerun_steel");
    set_commodity_value(500); /* in cc */

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
}
