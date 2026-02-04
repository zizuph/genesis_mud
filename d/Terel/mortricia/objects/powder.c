/*
    A pile of black powder. Mortricia 920901.
 */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("powder");
    set_short("pile of powder");
    set_pshort("piles of powder");
    set_long(break_string("It's a pile of black iron powder.\n", 70));
    set_adj(({"iron", "black"}));
    add_prop(OBJ_I_VALUE, 20 + random(11));
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
}
