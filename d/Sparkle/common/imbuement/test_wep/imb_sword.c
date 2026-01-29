/*
 * This weapon is a standard sword, with a random imbuement.
 *
 *
 * Nerull 14/3-09.
 */

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../../defs.h";

inherit "std/weapon";
inherit S_DOMAIN_COMMON_DIR + "imbuement/im_master";


// The creation of the weapon.
create_weapon()
{
    set_name("shortsword");
    add_name("sword");
    set_adj("steel");
    add_adj("rust-colored");
    set_short("rust-colored steel shortsword");
    set_long("This is a "+short()+". It can be " +
    "wielded in any hand. The hilt is made of black wood " +
    "trimmed with stripes of red leather, and the blade is " +
    "straight and doubleedged. The blade is painted with a " +
    "brown-red colour, similar to the color of rust.\n");
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hit(30);
    set_pen(30);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE, 1200);
    
    seteuid(getuid());
    
    random_imbuement_wep();
}

// This weapon will never last over armageddon.
public string
query_recover()
{
    return 0;
}
