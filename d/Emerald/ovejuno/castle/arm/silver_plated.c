
/* Ckrik 1998
 * Modified by Marisol (08/31/98) to be used in Ovejuno, Emerald.
*/

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 37

void
create_armour()
{
    set_name("armour");
    set_pname("armours");

    set_adj("silver-alloyed");
    set_adj("plated");

    set_short("silver-alloyed plated armour");
    set_pshort("silver-alloyed plated armours");

    set_long("A elvish silver-alloyed plated armour. Of excellent "+
        "quality and craftmanship, this armour shine with the "+
        "beauty of silver but has the resistence of the best steel "+
        "alloyed. It will fit any wearer like a glove.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);                                        
    set_am( ({-3,0,1}) );

    add_prop(OBJ_I_WEIGHT, 12000 + random(1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(150));
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
