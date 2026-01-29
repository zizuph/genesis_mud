
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
inherit "/std/armour";


create_armour()
{
    set_name("pants");
    set_short("pair of brown leather pants");
    set_pshort("pairs of brown leather pants");
    set_adj(({"brown","leather"}));
    set_long("A small pair of brown leather pants.\n");
    set_ac(4);
    set_at(A_LEGS);
    set_am(({0,-1,0}));
    add_prop(OBJ_I_WEIGHT,350);
    add_prop(OBJ_I_VOLUME,250);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(4));
}
