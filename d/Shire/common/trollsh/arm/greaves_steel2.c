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
    add_adj("steel");
    set_short("dull steel greaves");
    set_long("These are a pair of "+short()+". They come from the " +
        "Trollshaws and used to protect the legs.\n");
    set_ac(25);
    set_at(A_LEGS);
    add_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VALUE, 750+random(500));
}
