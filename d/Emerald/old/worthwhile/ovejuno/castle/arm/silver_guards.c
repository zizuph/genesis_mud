
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
    set_name("guards");
    set_pname("guards");

    set_adj("silver-alloyed");
    set_adj("shin");

    set_short("pair of silver-alloyed shin guards");
    set_pshort("pairs of silver-alloyed shin guards");

    set_long("A pair of silver-alloyed shin guards. Beautiful "+
        "elvish craftmanship. It combines beauty and protection "+   
        "for the legs.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);
    set_am( ({-2,0,1}) );

    add_prop(OBJ_I_WEIGHT, 3500 + random(500));
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