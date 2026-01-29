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
    set_name("bottle");
    add_name("_broken_bottle");
    set_pshort("dirty broken bottles");
    set_short("dirty broken bottle");
    set_adj(({"broken","dirty"}));
    set_long("This is a dirty, broken bottle. The top is " +
        "shattered with jagged edges and a large crack running " +
        "down the side.\n");

    add_prop(OBJ_I_WEIGHT,25);
    add_prop(OBJ_I_VOLUME,25);
    add_prop(OBJ_I_VALUE, 20+random(17));
}
