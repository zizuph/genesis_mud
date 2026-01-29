/* A platemail for the Grey barrow wight's
 * Modified from Rogon's Trollplate, (sorry Rog) stole from you again..
 * Cloned by ~Shire/common/monster/g_wight.c 
 * Dondon 141093
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

create_armour()
{
    set_name( ({"fullplate", "armour"}) );
    set_short("steel fullplate armour");
    set_adj("steel");
    set_long("A fullplate armour made of ancient steel.\n");
    set_ac( 23 );
    set_at( A_TORSO );
    set_am( ({ -1, -2, 3}) );

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(23,A_TORSO) + random(501) + 6000 ); 
    add_prop(OBJ_I_VOLUME,  3450);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(23)+random(101));

}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
