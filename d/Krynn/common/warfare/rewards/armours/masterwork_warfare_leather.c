/* 
 * Warfare masterwork body armour standard file for the various factions.
 * Provides resistance to warfare npc special attacks.
 *
 * Created by Theros Ironfeld in Solace.
 * Ingredients are:   60 steel coins (warfare reward item)
 *                    a silver bar (mine silver nuggets, sell nuggets,
 *                                  wait for another smith to finish and then
 *                                  buy a silver bar, bring it to Theros)
 *                    Five leather scraps 
 *                    a carbon bar
 *
 *
 * Arman Kharas, October 2018
 */

inherit "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour";

#include <wa_types.h>

#define MASTERWORK_LEATHER     2

public void
create_warfare_armour()
{
    set_commodity_name("mw lbreastplate");
    set_armour_level(MASTERWORK_LEATHER, A_TORSO, "free");
}
