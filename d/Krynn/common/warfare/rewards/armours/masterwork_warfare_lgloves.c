/* 
 * Warfare masterwork leather gloves standard file for the various factions.
 * Provides resistance to warfare npc special attacks.
 * Arman Kharas, October 2018
 */

inherit "/d/Krynn/common/warfare/rewards/masterwork_warfare_gauntlets";

#include <wa_types.h>

#define MASTERWORK_LEATHER     2

public void
create_warfare_armour()
{
    set_commodity_name("mw lgloves");
    set_armour_level(MASTERWORK_LEATHER, A_ARMS, "free");
}
