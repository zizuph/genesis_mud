/* Flag of Solamnia for Vingaard Keep  */
/* by Teth 01 97 for new VK */

inherit "/std/object";

#include "../local.h"

create_object()
{
    set_name("flag");
    add_name(({"solamnian flag", "flag of Solamnia"}));
    set_short("flag of Solamnia");
    set_long("This flag bears the symbol of Solamnia, a gauntletted " +
        "fist, implying that the land deals out justice fairly for all.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_GET, "It is affixed to the battlement.\n");
    add_prop(OBJ_M_NO_STEAL);
}
