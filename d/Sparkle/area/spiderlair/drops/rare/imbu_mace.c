/*
 * This weapon is a standard mace, with a random imbuement.
 *
 *
 * Nerull 14/3-09.
 */

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../../defs.h";

inherit "std/weapon";
inherit SPIDER_DIR + "imbuements/imb_master";


// The creation of the weapon.
create_weapon()
{
    set_name("mace");
    set_adj("rust-colored");
    set_adj("spiked");
    set_short("rust-colored spiked mace");
    set_long("This is a rust-colored spiked mace. It can be " +
    "wielded in any hand. Six pointy spikes errupts from " +
    "the round base of the mace, which seems to could " +
    "do some additional piercing damage. The mace is wrapped " +
    "with black leather, and is coated with a rust-colored " +
    "paint.\n");
    
    set_default_weapon(30,30, W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE, 1200);
 
    seteuid(getuid());
    
    random_imbue_me();
}


// This weapon will never last over armageddon.
public string
query_recover()
{
    return 0;
}
