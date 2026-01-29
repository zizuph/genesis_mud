/*
 * /d/Krynn/sancrist/nevermind/guild/obj/coffee.c
 * 
 * Creator: Shadowlynx
 * Date   : Jan 26/99
 * Updated: 
 * By Whom:
 *
 * To be generated from the Coffeemaker module on the gizmo
 *
 * Modified in part from /d/Krynn/gnome/obj/food/coffee.c
 */

inherit "/std/drink";
#include "/sys/stdproperties.h"

void
create_drink()
{
    set_soft_amount(100);
    set_alco_amount(0);
    set_name("cappiccino");
    add_name("cup");
    add_name("cup of cappaccino");
    add_name("cappiccino");
    add_name("coffee");
    set_adj("gnomish");
    set_short("cup of cappaccino");
    set_pshort("cups of cappaccino");
    set_long("A cup filled with a hot, " 
      + ({"dark brown", "black", "nearly transparent"
	, "light brown", "tasty"})[random(5)] 
      + " liquid.\n");
    set_drink_msg("This cappuccino tastes really yummy.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
