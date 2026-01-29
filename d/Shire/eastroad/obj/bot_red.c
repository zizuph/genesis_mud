/*
 * Broken bottle for well trash
 * Finwe, May 2020
 */

#include "/d/Shire/sys/defs.h" 
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";

create_object()
{
    set_name("bottle");
    add_name("_well_bottle_");
    add_name("bottle");
    add_name("shattered");
    add_name("red");

    set_short("shattered red bottle");
    set_long("This is a " + short() + ". The bottom has broken off " +
        "from being dropped. The only part remaining is the neck and " +
        "a jagged edge. It looks like it was once a beautiful bottle, but " +
        "now it's worthless.\n");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 3);
    add_prop(OBJ_I_VALUE, 100);
}
