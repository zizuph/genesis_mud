/* A platemail for the Black (toughest) Barrow wight
 * Modified from Rogon's Trollplate, (sorry Rog) stole from yu again..
 * Cloned by ~Shire/common/monster/wight.c in ~common/downs/stone2
 * Dondon 121093
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

create_armour()
{
    set_name( ({"armour"}) );
    set_short("tempered steel fullplate armour");
    set_adj("fullplate");
    set_adj("steel");
    set_adj("tempered");
    set_long("This is a heavy fullplate armour made of steel. It is ancient " +
        "looking and covers the chest. The metal looks tempered and strong.\n");
    set_ac( 40 );
    set_at( A_TORSO );
    set_am( ({ 1, 1, -2}) );

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(42,A_TORSO) - random(203)); 
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(42) + random(303));
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
