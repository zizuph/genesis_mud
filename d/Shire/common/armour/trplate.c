/*
 * 2021-01-02 Cotillion
 * - Fixed broken resistance implementation
 *   The high additive resistance is easily offset by the low ac
 *   and high weight.
 */
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include "rdefs.h"

inherit ShireArmour;

void
CreateArmour()
{
    set_name( ({"armour", "platemail","fullplate", "plate"}) );
    set_short("iron fullplate armour");
    set_adj("iron");
    set_long("This seems like a large iron fullplate armour made "+
      "for big creatures.\n");
    set_ac( 33 );
    set_at( A_TORSO );
    set_am( ({ -4, -3, 7}) );
    set_af( this_object() );

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(33,A_TORSO) + 20000);  
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
	({  "This seems like a large platemail covering the torso.\n", 1,
	    "This platemail yields protection against fire.\n",20
	}) );

}

mapping resistances = ([
    MAGIC_I_RES_FIRE: 25, 
    MAGIC_I_RES_LIGHT: 15
]); 

mixed
query_magic_protection(string prop, object who)
{
    if (who != query_worn() || !resistances[prop])
        return 0;

    return ({ resistances[prop], 1 });
}

mixed
wear(object ob)
{
    this_player()->add_magic_effect(this_object());
}

mixed
remove(object to)
{
    this_player()->remove_magic_effect(this_object());
}
