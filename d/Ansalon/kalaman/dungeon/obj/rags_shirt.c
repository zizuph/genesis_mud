/*
 * Prisoner Shirt
 */
inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

create_armour()
{
    set_name("shirt");
    add_name("_prison_rags_");
    set_adj("thorn");
    add_adj("cloth");

    set_short("thorn cloth shirt");
    set_pshort("thorn cloth shirts");
    set_long("This is a " +short()+ " is a rather sad excuse for " +
      "a shirt.\n");
    set_ac(0);
    set_am(({0,0,0}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 2);
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_WEIGHT, 2);
}
