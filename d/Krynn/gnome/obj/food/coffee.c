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
    set_name("cappuccino");
    add_name("cup");
    add_name("steaming cup of cappuccino");
    add_name("cappucino");
    add_name("coffee");
    set_adj("gnomish");
    set_short("steaming cup of cappuccino");
    set_pshort("steaming cups of cappuccino");
    set_long("A cup overflowing with a steaming, " 
      + ({"wickedly sinful", "lusciously rich", "creamy smooth"
	, "devilishly delightful", "mouth watering"})[random(5)] 
      + " essence.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

void
special_effect(int amnt)
{
    write("Mmmm! This cappuccino tastes heavenly!\n" +
      "By far, the best you have EVER had!\n");
}

