/* 
 * Leather apron used by a blacksmith
 *
 * Finwe, February 2018
 */
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

create_armour() 
{
    set_name("apron");
    set_pname("aprons");
    remove_name("armour");
    set_short("heavy leather apron");
    set_pshort("leather aprons");
    set_adj("leather");
    set_adj("heavy");
    set_long("This heavy leather apron looks like the typical blacksmith apron.\n");
    set_default_armour(6,A_BODY,({ -1, 2, -1}),0);
    add_prop(OBJ_I_WEIGHT, 3200);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(6)+random(20)-10);
    add_prop(OBJ_M_NO_DROP,1);
}




