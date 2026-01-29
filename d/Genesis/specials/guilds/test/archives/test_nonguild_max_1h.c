/*
 * Base testing NPC with no guild affiliations
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_nonguild";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    ::create_test_npc();
    
    // Set up a few basics
    set_name("noguild_1h_max");
    set_short("test no guild 1h max npc");
    set_long("This is a test noguild 1h max npc.\n");
}

public string *
query_equipment_list()
{
    return ({ 
            "/d/Genesis/specials/guilds/test/armours/standard_armour_40",
            "/d/Genesis/specials/guilds/test/weapons/test_1h_50_sword",
            "/d/Genesis/specials/guilds/test/armours/standard_shield_40",
            });
}
