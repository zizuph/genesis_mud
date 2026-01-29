/* Banner of Vingaard Keep  */
/* by Teth 01 97 for new VK */

inherit "/std/object";

#include "../../local.h"

create_object()
{
    set_name("standard");
    add_name(({"vingaard keep standard","standard of Vingaard Keep"}));
    set_short("standard of Vingaard Keep");
    set_long("This standard bears a symbol of a rock weathering the " +
        "forces of Nature's elements, suggesting the sturdiness and " +
        "resilience of those who reside within these walls.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_GET, "It is affixed to the battlement.\n");
    add_prop(OBJ_M_NO_STEAL);
}
