/*
 * bezainted_greaves.c
 * Bezainted greaves, worn by Ergothian guards
 * Gulfport, Northern Ergoth
 * Tibbit, 22 May 1998
 *
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("greaves");
    add_adj("bezainted");
    set_short("pair of bezainted greaves");
    set_pshort("pairs of bezainted greaves");
    set_long("These protective greaves consist of steel "+
        "closely set on a layer of cuir-boili, leather boiled in oil "+
        "and hardened.\n");
    set_at(A_LEGS);
    set_ac(17);
    add_prop(OBJ_I_VOLUME, 300);
}
