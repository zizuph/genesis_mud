 /*     Triton helmet for Thalassia

    coder(s):   Glykron, Jaacar

    history:    25. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron
                23. 7.03    changed for Thalassian Tritons  Jaacar

*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("helmet");
    set_adj("silver");
    set_short("silver helmet");
    set_long("This is a pointy helmet made of a silver material.\n");
    set_ac(20);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2500);
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
