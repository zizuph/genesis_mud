/* 
 * Warfare masterwork body armour standard file for the various factions.
 * Provides resistance to warfare npc special attacks.
 * Arman Kharas, October 2018
 */

inherit "/d/Krynn/common/warfare/rewards/masterwork_warfare_std_helm";

#include <wa_types.h>

#define MASTERWORK_CHAINMAIL     1

public void
create_warfare_armour()
{
    set_commodity_name("mw chain hood");
    set_armour_level(MASTERWORK_CHAINMAIL, A_HEAD, "free");
}
