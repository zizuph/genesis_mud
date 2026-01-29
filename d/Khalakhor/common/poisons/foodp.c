/* File         : /d/Khalakhor/common/poisons/foodp.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : February 27, 1999
 * Purpose      : This is a small poison given when someone eats raw fish.
 * Related Files: /d/Khalakhor/se_speir/port/obj/ various.c
 *                /d/Khalakhor/se_speir/port/obj/fish_base.c
 * Comments     :
 * Modifications:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/poison_effect";

#include <poison_types.h>
#include <stdproperties.h>

public void
create_poison_effect()
{
    set_name("_khalakhor_food_poison");
    set_interval(45);
    set_time(600);
    set_damage(({ POISON_HP, 5 }));
    set_strength(5);
    set_poison_type("food");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);    
}

