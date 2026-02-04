/*
    A small gem
 */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("needle");
    set_short("silver needle");
    set_long("It is a small silver needle.\n");
    set_adj(({"small", "silver"}));
    add_prop(OBJ_I_VALUE, 550 + random(100));
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 50);
}

