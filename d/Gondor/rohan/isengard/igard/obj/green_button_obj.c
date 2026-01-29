/*
 * object for green button
 */


inherit "/std/object";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

object tcup;

void
create_object()
{
    set_name("_green_button_pushed_");
    set_short("a green thing");
    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "Get what?\n");
    add_prop(OBJ_I_VOLUME,      1000);
    add_prop(OBJ_I_WEIGHT,      1000);
}

