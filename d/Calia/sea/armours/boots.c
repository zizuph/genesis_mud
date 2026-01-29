 /*      Black boots for the water krougs

    coder(s):   Glykron, Digit

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
    set_name("boots");
    set_adj("black");
    set_long("These boots appear to be made of a black material.\n");
    set_ac(25);
    set_at(A_FEET);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6000);
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
