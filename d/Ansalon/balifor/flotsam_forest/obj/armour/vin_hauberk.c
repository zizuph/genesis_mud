/* Base code by Aridor, 09/15/94
 * Adjusted by Mortis to be the suit of armour cloned after
 * the plate armour of Solamnus reaches its maximum of five.
 * It still fulfills the quest just as the plate armour.
 *
 * Its AC will range from 40-45, and it is not magical.
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
    add_name("hauberk");
    set_adj("plate");
    set_short("plate hauberk of Solamnus");
    set_long("Of all the armours you have come across, this set is " +
      "by far the most awe inspiring. Consisting of a breastplate, " +
      "shoulder guards and arm fittings, all made of the " +
      "finest of steel and all beautifully tooled with the " +
      "markings of the three Solamnic Orders, this armour is considered " +
      "by all warriors and smiths as the finest the land has ever seen. " +
      "@@tradition@@" +
      "Not surprisingly, these suits of armour are greatly prized even "
	  + "though they do not protect the lower body or its rear end.\n");
    add_item(({"crown","sword","rose","kingfisher","markings"}),
      "All over this plate armour elaborate symbols have been " +
      "carved. You notice the markings of the Solamnian knighthood, the crown, " +
      "sword and rose representing the three orders, and the " +
      "kingfisher symbolizing the knighthood as a unity.\n");
    set_ac(40 + random(6));
    set_at(A_TORSO | A_ARMS);
    set_af(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 8040);
    add_prop(OBJ_I_WEIGHT, 13000 + random(500));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(55) + 1500);

}

string
tradition()
{
    if (this_player()->query_guild_member("Solamnian Knights"))
	return " No less inspiring are the legends of those who wore this armour.  "
	+ "Niebutai Marblund, founder of the Knights of Solamnia's lesser known "
	+ "branch, the Leather Rebels, was the first to have such a suit created, "
	+ "and the most famous and beloved of knights Huma Dragonslayer was "
	+ "rumoured to have commented on the suit before his final battle "
	+ "against the Queen of Darkness.  His comments were not recorded. ";
    return "";
}

mixed
wear(object what)
{
    if (TP->query_alignment() > 1100)
    {
	TP->catch_msg("A greater peace flows through you as you wear " +
	  "the plate hauberk of Solamnus.\n");
	return 0;
    }
    return 0;
}

mixed
remove(object what)
{
    TP->catch_msg("The plate hauberk of Solamnus ceases to imbue you with "
	+ "its knightly power of Niebutai.\n");
	say(QCTNAME(TP) + " shudders pleasurably while sighing:  Mmmmmmm, "
	+ "Niebutai.\n");
	return 0;
}

