/* 	golden boots for the gold knight in the crystalline palace

    coder(s):   Glykron

    history:    17/7/95     typo removed                    Maniac
                25. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("boots");
    set_adj( ({ "gold", "golden" }) );
    set_short("pair of gold boots");
    set_pshort("pairs of gold boots");
    set_long("These boots appear to be made of solid gold.\n");
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