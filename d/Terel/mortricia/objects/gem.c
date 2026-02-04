/*
    A small gem
 */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("gem");
    set_short("blue gem");
    set_long("It's a small blue gem. Unfortunately, it looks rather cheap.\n");
    set_adj(({"small", "blue"}));
    add_prop(OBJ_I_VALUE, 100 + random(11));
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
}

