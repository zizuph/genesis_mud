/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    seteuid(getuid());
    set_name("leaf");
    set_pname("golden leaves");
    set_adj("golden");
    set_long("This is beautiful golden leaf. It is has three " +
        "large lobes on top with two smaller ones at the base " +
        "and a long stem. The leaf is crisscrossed with silver veins.\n");

    add_item(({"lobes"}),
        "The three lobes at the end of the leaf are large while " +
        "the bottom two are small.\n");
    add_item(({"veins", "silver veins"}),
        "They run randomly across each leaf and are silver colored.\n");
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_WEIGHT, 50);
}
