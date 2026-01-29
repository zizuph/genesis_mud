
 /*    Thalassian Mail

    coder(s):    Digit

    history:    21.7.95    Header added          Digit

 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void
create_armour()
{
    set_name(({"mail","thalassian mail","armor","armour"}));
    set_adj("dark");
    set_short("thalassian mail");
    set_long("It is a suit of armour to wear over your shoulders.  "+
        "It is made out of the skin of a sea-serpent, which is dark "+
        "green in colour, and has plates of orichalcum on it to "+
        "cover the chest, back and shoulder areas.  There "+
        "is a design carved into the plates of three circles, "+
        "a small one in the centre, a larger one surrounding that, "+
        "and a larger one surrounding the other two.\n");
    set_ac(40);
    set_at(A_BODY);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45) + 200);
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
