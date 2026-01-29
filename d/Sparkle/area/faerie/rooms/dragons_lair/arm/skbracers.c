/*
 *
 * blackened tungsten bracers.
 * Nerull, 21/2/09.
 */
 
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../defs.h";

inherit "/std/armour";

void
create_armour()
{
    set_name("bracers");
    set_adj("tungsten");
    set_adj("blackened");
    set_short("pair of blackened tungsten bracers");
    set_pshort("pairs of blackened tungsten bracers");
    set_long("These pair of blackened tungsten bracers gives good " +
    "protection of the underarms, and they are adjustable to fit " +
    "anyone of normal size.\n");
    set_ac(40);
    set_at(A_ARMS);
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, 1500);
}



