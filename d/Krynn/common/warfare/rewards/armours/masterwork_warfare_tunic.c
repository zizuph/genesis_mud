/* 
 * Warfare masterwork body armour standard file for the various factions.
 * Provides resistance to warfare npc special attacks.
 *
 * Created by Theros Ironfeld in Solace.
 * Ingredients are:   40 steel coins (warfare reward item)
 *                    a silver bar (mine silver nuggets, sell nuggets,
 *                                  wait for another smith to finish and then
 *                                  buy a silver bar, bring it to Theros)
 *                    a gold bar
 *                    Five leather scraps 
 *                    a carbon bar
 *
 *
 * Arman Kharas, October 2018
 */

inherit "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour";

#include <wa_types.h>

#define MASTERWORK_TUNIC     3

public void
create_warfare_armour()
{
    set_commodity_name("mw tunic");
    set_armour_level(MASTERWORK_TUNIC, A_TORSO, "free");
}
