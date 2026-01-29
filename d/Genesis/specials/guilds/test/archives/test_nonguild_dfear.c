/*
 * Base testing NPC with no guild affiliations
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/test_npc";

public string *
query_equipment_list()
{
    return ({ 
            "/d/Genesis/specials/guilds/test/armours/standard_armour_40",
            "/d/Genesis/specials/guilds/test/weapons/test_sword",
            "/d/Genesis/specials/guilds/test/armours/standard_shield_40",
            });
}

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    // Set up a few basics
    set_name("noguild_dfear");
    set_short("test no guild dfear npc");
    set_long("This is a test noguild dfear npc.\n");
    config_test_npc(170, "human");
    
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 75); // lower defence and parry by 25
    set_skill(SS_PARRY, 75);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_BLIND_COMBAT, 20);
}

public int
special_attack(object target)
{
    refresh_npc();
           
    return 0;
}
