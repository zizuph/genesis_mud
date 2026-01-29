/* Teth Jan 18 1997 */

inherit "/std/armour";
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    set_name("hat");
    set_ac(3);
    add_name("armour");
    set_short("green hat");
    set_pshort("green hats");
    set_at(A_HEAD);
    set_adj("green");
    set_long("This is a funny-looking green hat. Obviously someone " +
        "left it by accident while wandering the forest, or perhaps " +
        "they dropped it while taking a rest and forgot about it. " +
        "Whatever the case, it appears that it would fit your head " +
        "perfectly.\n");
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
}
