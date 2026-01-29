/* MCLUB - ceremonial mantle
** - worn for ceremonial purposes
** - found in rooms/shconsac.c in the cabinet (2 available)
** - no monetary or armour value
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"
 
void
create_armour()
{
    set_name(({"gray mantle","mantle"}));
    add_name(MCLUB_MANTLE);
    set_adj("grey");
    set_short("grey mantle");
    set_long("It is a long sleevless garment worn over a robe.\n");
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}
