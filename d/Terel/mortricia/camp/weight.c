/*
   An heavy weight, for the wrestler
 */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("weight");
    set_short("heavy weight");
    set_long("It's a heavy weight, made out of iron.\n");
    add_prop(OBJ_I_VALUE, 100 + random(11));
    add_prop(OBJ_I_WEIGHT, 70000);
    add_prop(OBJ_I_VOLUME, 1000);
}

