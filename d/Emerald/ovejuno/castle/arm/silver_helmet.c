
/* Ckrik 1998
 * Modified by Marisol (08/31/98) to be used in Ovejuno, Emerald.
*/

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 30

void
create_armour()
{
    set_name("helmet");
    set_pname("helmets");

    set_adj("silver");
    set_adj("alloyed");

    set_short("silver-alloyed helmet");
    set_pshort("silver-alloyed helmets");

    set_long("A silver-alloyed helmet. A handsome design that combine "+
        "beauty and protection. This helmet is light but strong "+
        "enough to protect the wearer head against harm.\n");  

    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_am( ({-2,0,1}) );

    add_prop(OBJ_I_WEIGHT, 2500 + random(200));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(100));

}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}                                                                      