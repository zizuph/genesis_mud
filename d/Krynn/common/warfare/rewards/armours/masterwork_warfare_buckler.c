/* 
 * Warfare masterwork buckler standard file for the various factions.
 * Provides resistance to warfare npc special attacks.
 * Arman Kharas, November 2018
 */

inherit "/d/Krynn/common/warfare/rewards/masterwork_warfare_shield";

#include <wa_types.h>

#define MASTERWORK_BUCKLER     1

public void
create_warfare_armour()
{
    set_commodity_name("mw buckler");
    set_armour_level(MASTERWORK_BUCKLER, A_SHIELD, "free");
}
