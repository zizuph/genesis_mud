/*
 * - The very high effect was commented out. /Cotillion, AoB
 */
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink()
{
    set_name("milk");
    set_adj(({"thick", "frothy", "white", "goat"}));
    set_short("goat milk");
    set_long("Thick frothy white goat milk. The perfect " +
        "food and beverage.\n");
    set_soft_amount(100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}


public void
special_effect(int num_milks)
{
/*
  object tp = this_player();
  
  tp->add_mana(10 * num_milks);
  tp->eat_food(100 * num_milks);
*/
    write("Ahh ... delicious refreshing goat milk.\n");
}

