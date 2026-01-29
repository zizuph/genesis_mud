/* Created by Aridor, 09/15/94 
 *
 * Modified by Mortis.  It used to be ILLEGAL ac 65.  I dropped
 * that to range from 50-58.  Also, it is now called by clone_unique
 * with a maximum of 5.
 */

inherit "/std/armour";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

string
query_recover()
{
    return 0;
}

void
create_armour()
{
    set_name(({"armour","_ansalon_quest_s_armour_"}));
    add_name("platemail");
    set_adj("plate");
    set_short("plate armour of Solamnus");
    set_long("Of all the armours you have come across, this set is " +
      "by far the most awe inspiring. Consisting of a breastplate, " +
      "shoulder guards and arm fittings, all made of the " +
      "finest of steel and all beautifully tooled with the " +
      "markings of the three Solamnic Orders, this armour is considered " +
      "by all warriors and smiths as the finest the land has ever seen. " +
      "@@tradition@@" +
      "Not surprisingly, these suits of armour are greatly prized.\n");
    add_item(({"crown","sword","rose","kingfisher","markings"}),
      "All over this plate armour elaborate symbols have been " +
      "carved. You notice the markings of the Solamnian knighthood, the crown, " +
      "sword and rose representing the three orders, and the " +
      "kingfisher symbolizing the knighthood as a unity.\n");
    set_ac(50 + random(9));
    set_at(A_TORSO | A_ARMS | A_LEGS);
    set_af(TO);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This armour was forged when the Knights of Solamnia were " +
	"newly formed. Made with the finest steels by the greatest " +
	"of armourers, and enchanted by the magic of the White Robed " +
	"Wizards of High Sorcery, as well as blessed by the High " +
	"Priests of Paladine, it offers unequaled protection.\n",20}));
    add_prop(MAGIC_AM_MAGIC,({100,"enchantment"}));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 8040);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(45, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(55) + 1500);

}

string
tradition()
{
    if (this_player()->query_guild_member("Solamnian Knights"))
	return " No less inspiring are the legends of those who wore this armour. Vinas Solamnus, " +
	"founder of the Knights of Solamnia, was the first to have " +
	"such a suit created, and the most famous and beloved of knights " +
	"Huma Dragonslayer was rumoured to have worn a suit in his " +
	"final battle against the Queen of Darkness.";
    return "";
}

mixed
wear(object what)
{
    if (TP->query_alignment() > 1100)
    {
	TP->catch_msg("A greater peace flows through you as you wear " +
	  "the plate armour of Solamnus.\n");
	return 0;
    }
    return 0;
}

mixed
remove(object what)
{
    if (TO->query_prop(OBJ_I_LIGHT) == 1)
    {
	add_prop(OBJ_I_LIGHT,0);
	TP->catch_msg("The plate armour of Solamnus ceases to glow.\n");
	say(QCTNAME(TP) + "'s plate armour of Solamnus ceases to " +
	  "glow.\n");
	return 0;
    }
    add_prop(OBJ_I_LIGHT,0);
    return 0;
}

