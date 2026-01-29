/* 
 * Warfare hoopak standard file for the various factions.
 *
 * Created by Theros Ironfeld in Solace.
 * Ingredients are:   100 steel coins (warfare reward item)
 *                    a silver bar (mine silver nuggets, sell nuggets,
 *                                  wait for another smith to finish and then
 *                                  buy a silver bar, bring it to Theros)
 *                    Eight iron bars
 *                    Five leather scraps 
 *
 *
 * Arman Kharas, November 2018
 */

inherit "/d/Krynn/common/warfare/rewards/masterwork_warfare_weapon";

#include <wa_types.h>

#define HOOPAK            2

public void
create_warfare_weapon()
{
    set_commodity_name("mw hoopak");
    set_weapon_level(HOOPAK, W_POLEARM, W_BOTH, "free");
}
