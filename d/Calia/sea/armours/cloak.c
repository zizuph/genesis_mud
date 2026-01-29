 /*        Black cloak for the water krougs

    coder(s):   Glykron

    history:    25. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron
                24. 5.95    changed for water krougs          Digit

*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("cloak");
    set_adj("black");
    set_short("black cloak");
    set_long("This is a black cloak of a human make.\n");
    set_ac(15);
    set_at(A_ROBE);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 5000);
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
