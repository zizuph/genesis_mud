/*
 * poor_targe.c
 *
 * This targe is just a really poor shield for small npc's. 
 *
 * Khail - March 29/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"

#define AC 5

inherit "/std/armour";
          
/*
 * Function name: create_armour
 * Description  : Turns this object into armour.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_armour()
{
    set_name("targe");
    add_name("shield");
    set_adj("battered");
    add_adj("wooden");
    set_short("battered wooden targe");
    set_long("This targe, or shield, is made fairly cheaply of " +
        "badly battered and slashed lathes of wood. A single " +
        "brass dome, or boss, decorates the front of the targe, " +
        "and once held a spike, but that's long gone.\n");

    set_at(A_SHIELD);
    set_af(TO);
    set_ac(AC);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_SHIELD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);     
}
