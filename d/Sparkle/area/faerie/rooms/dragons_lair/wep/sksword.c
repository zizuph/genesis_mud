/*
 *
 * blackened tungsten bracers.
 * Nerull, 21/2/09.
 */

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h";


inherit "/std/weapon";

create_weapon()
{
    set_name("shortsword");
    add_name("sword");
    set_adj("blackened");
    set_adj("tungsten");
    set_short("blackened tungsten shortsword");
    set_long("This is a blackened tungsten shortsword. It can be " +
    "wielded in any hand. The hilt is made of black wood " +
    "trimmed with stripes of blue leather, and the blade is " +
    "straight and doubleedged. It seems to be recently " +
    "polished and it carries a black coating of something resembling " +
    "the dust of coal.\n");
    set_default_weapon(40,40, W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE, 1200);
}
