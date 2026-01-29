/*
 * Base Vampire testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_vampire";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    ::create_test_npc();

    set_name("hastedrain_vampire");
    add_prop(LIVE_I_QUICKNESS, 45);
    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_DEFENCE, 75);
}
