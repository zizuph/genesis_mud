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
    set_name("bone");
    add_name("broken bone");
    add_name("_broken_bone");
    set_short("broken bones");
    set_adj(({"broken"}));
    set_long("The bone is broken, like it has been chewed on by " +
        "trolls. One end is splintered and cracked.\n");

    add_prop(OBJ_I_WEIGHT,75);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE, 25+random(100));
}
