/*
 * herb salad for the pub in Ten Alders
 * coded by Amelia   5/24/97
 *
 * - The very high effect was commented out. /Cotillion, AoB
 * Effect/Price made comparable to veges in Calia, Ckrik 9/2005
 * Removed bias against undead. (Gorboth, August 2009)
 */

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>

public void
create_food()
{
    set_name("salad");
    set_adj(({"fresh", "herb"}));
    set_short("fresh herb salad");
    set_long("A salad of green herbs. Among " +
        "the leaves you see bits of lettuce, basil, spinach " +
        "and chopped garlic and onion. There " +
        "are some small red berries mixed among the green " +
        "leaves. It appears very nutricious and " +
        "is tossed with a delicate fragrant vinaigrette for " +
        "extra flavour.\n");
    set_amount(85);
    add_prop(OBJ_I_WEIGHT, 85);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 300);
}



public void
special_effect(int num_salads)
{

    object tp = this_player();

    tp->heal_hp(10 * num_salads);
    tp->add_mana(20 * num_salads);
    write("You feel the nutricious effects of " +
        "the herb salad going to work in your body.\n");

    return;
}
