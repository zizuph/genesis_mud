/* created by Aridor, 09/15/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("armour");
    set_adj("solamnic");
    add_adj("full");
    add_adj("body");
    set_short("Solamnic full body armour");
    set_long("This is the full body armour of a Solamnic Knight. The steel " +
	     "is polished perfectly to shine brightly. Upon the breastplate " +
	     "the symbols of the knighthood are placed: Crown, Sword, Rose " +
	     "and Kingfisher.@@tradition@@\n");
    add_item(({"crown","sword","rose","kingfisher","symbols"}),
	     "These are the symbols of the Solamnian knighthood, the crown, " +
	     "sword and rose representing the three orders, and the " +
	     "kingfisher symbolizing the knighthood as a unity.\n");
    set_ac(39);
    set_at(A_TORSO | A_ARMS | A_LEGS);
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
