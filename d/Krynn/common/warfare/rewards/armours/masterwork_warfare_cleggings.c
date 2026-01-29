/* 
 * Warfare masterwork chain leggings standard file for the various factions.
 * Provides resistance to warfare npc special attacks.
 * Arman Kharas, October 2018
 */

inherit "/d/Krynn/common/warfare/rewards/masterwork_warfare_leggings";

#include <wa_types.h>

#define MASTERWORK_CHAIN     1

public void
create_warfare_armour()
{
    set_commodity_name("mw cleggings");
    set_armour_level(MASTERWORK_CHAIN, A_LEGS, "free");
}
