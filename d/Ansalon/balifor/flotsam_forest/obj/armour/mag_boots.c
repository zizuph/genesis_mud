/* created by Arman, 21/7/98 
* These magical boots increases the dex
* of those who can wear it by 10 points.
*
* Navarre May 9th 2009, Resourceful players figured out
* ways to purposedly lower their dex to get the full benefit
* of the boots.
* I fixed the check so it works as intended.
*/

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

object wearer;

void
create_armour()
{
    set_name("boots");
    add_name("armour");
    set_adj("grey");
    add_adj("leather");
    set_short("pair of grey leather boots");
    set_pshort("pairs of grey boots");
    set_long("This is a pair of very small grey " +
      "leather boots "+
      "that seem to be in fine condition. You notice " +
      "it has been finely cobbled, with thin strands " +
      "of silver replacing any leather thread normally " +
      "used.\n");
    set_at(A_FEET);
    set_ac(20);
    set_af(TO);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This small pair of boots are a pair of Faery boots, " +
	"tailored by the magical creatures of the forest. Often " +
	"some of its magic rubs off onto these boots, sometimes giving the wearer " +
	"an increase in agility\n",30,
	"Those whose feet are small enough to wear the boots but " +
	"who are extremely agile are rejected by the " +
	"boots due to their fickle, jealous nature.\n",70}));
    add_prop(MAGIC_AM_MAGIC,({10,"enchantment"}));
}

void
wear_message()
{
    if(E(TO) != wearer)
	return;

    wearer->catch_msg("Woh! A burst of energy " +
      "runs up your legs, making you feel more nimble!\n");

    tell_room(E(wearer),QCTNAME(wearer)+
      " straightens quite suddenly, as if a snake had " +
      "just run up the leg of " +HIS(wearer)+ " trousers.\n", wearer);
}

mixed
wear(object what)
{
    if(TP->query_race() == "human" || TP->query_race() == "elf")
	return "There is no way your big feet are going to fit " +
	"into these small boots.\n";
    if(TP->query_race_name() == "hobbit")
	return "At the thought of putting your hairy feet into " +
	"boots you inwardly shudder. Hobbits just weren't meant " +
	"to wear boots!\n";
    if(TP->query_stat(SS_DEX) > 135 || TP->query_base_stat(SS_DEX) > 135)
	return "The magical boots reject your feet, jealous " +
	"of their nimble nature.\n";
    TP->set_stat_extra(SS_DEX, (TP->query_stat_extra(SS_DEX) + 10));

    wearer = TP;
    set_alarm(0.5, 0.0, "wear_message");
    return 0;
}

mixed
remove(object what)
{
    if (wearer)
        wearer->set_stat_extra(SS_DEX, (TP->query_stat_extra(SS_DEX) - 10));

    wearer = 0;
    return 0;
}

void
leave_env(object ob, object from)
{
    if (wearer)
        remove(this_object());

    ::leave_env(ob, from);
}

