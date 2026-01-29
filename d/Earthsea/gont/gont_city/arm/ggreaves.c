/*  Imported from Roke, originally coded by Vladimir
 *  for Alexander (marshal.c)...typos corrected, added
 *  pname
 *  Amelia 3/24/98
 */

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_armour()
{
    set_name("greaves");
    set_adj("steel");
    add_adj("green");
    set_short("pair of green steel greaves");
    set_pshort("pairs of green steel greaves");
    set_pname("pairs of green steel greaves");
    set_long("They are made of green steel "+
        "with three small spikes at the "+
        "knees. On each greave is a symbol of two crossed axes "+
        "over a map of the world.\n");
    set_keep(1);
    set_ac(38);
    set_am(({ 0, 0, 0}));
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE, 800);
}
