/*
 * Greaves used by trolls in Trollshaws
 * -- Finwe October 2001
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("greaves");
    set_adj("dull");
    add_adj("iron");
    set_short("dull iron greaves");
    set_long("These are a pair of "+short()+". They are battered " +
        "from many battles and are scratched from constant use.\n");
    set_ac(23);
    set_at(A_LEGS);
    add_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VALUE, 750+random(500));
}
