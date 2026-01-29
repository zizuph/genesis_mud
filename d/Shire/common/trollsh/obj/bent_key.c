/*
 * Miscellaneous junk found in the Trollshaws
 * Designed for no purpose other than to be sold
 * -- Finwe, September 2001
 */
inherit "/std/object";
#include "/d/Shire/common/defs.h"

#include "/sys/stdproperties.h"

create_object()
{
    set_name("key");
    add_name("bent key");
    add_name("_bent_key");
    set_short("tarnished bent key");
    set_adj(({"tarnished","bent"}));
    set_long("This is a tarnished bent key. It is made of brass " +
        "and has a slight bend in it. The key looks pretty worthless.\n");

    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,15);
    add_prop(OBJ_I_VALUE, 50+random(100));
}
