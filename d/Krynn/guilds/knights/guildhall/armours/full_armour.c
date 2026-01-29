/* created by Aridor, 09/15/94
 * Modified by Teth, June 19, 98, to fit updated man armour.
 */
/*
 * Added support for the commerce module in July 2002, by Boron
 * 
 * Navarre june 10th 2006
 * Removed Magical armour prop, since the armour isn't magical.
 */

/* Navarre July 2008, adding metal adj for ogres */

inherit "/std/armour";
inherit "/lib/keep";
inherit "/d/Genesis/lib/commodity";

#include <wa_types.h>
#include <formulas.h>
#include "../../local.h"

public void
create_armour()
{
    set_name("platemail");
    set_pname("platemails");
    add_name(({"plate","mail","armour"}));
    add_pname(({"plates","mails","armours"}));
    set_adj("solamnic");
    add_adj("solamnian");
    add_adj("full");
    add_adj("body");
    add_adj("metal");
    set_short("solamnic platemail");
    set_pshort("solamnic platemails");
    set_long("This is the full body armour of a Solamnic Knight. The steel " +
      "is polished perfectly to shine brightly. Upon the breastplate " +
      "the symbols of the knighthood are placed: Crown, Sword, Rose " +
      "and Kingfisher.@@tradition@@\n");
    add_item(({"crown","sword","rose","kingfisher","symbols"}),
      "These are the symbols of the Solamnian knighthood, the crown, " +
      "sword and rose representing the three orders, and the " +
      "kingfisher symbolizing the knighthood as a unity.\n");
    set_ac(40);
    set_at(A_TORSO | A_ARMS | A_LEGS);

    set_commodity_name ("full_armour"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_ARMOUR(40), 0);

    add_prop(OBJ_I_VOLUME, 6239);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40));
    add_prop(VK_NOBUY, 1);
}

string
tradition()
{
    if (this_player()->query_guild_member("Solamnian Knights"))
    return " Traditionally, this armour is bequeathed along a family " +
    "of Knights of Solamnia. It is the proud heritage and the testament " +
    "of nobility among knights.";
    return "";
}
