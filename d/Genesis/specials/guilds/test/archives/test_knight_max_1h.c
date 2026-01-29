/*
 * Knight with max 1H Sword testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_knight";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    ::create_test_npc();
    
    // Set up a few basics
    set_name("knight_max_1h");    
    set_short("test knight max 1h npc");
    set_long("This is a test knight with max 1h sword npc.\n");
}

public string *
query_equipment_list()
{
    return ({ 
            "/d/Genesis/specials/guilds/test/armours/standard_armour_40",
            "/d/Genesis/specials/guilds/test/weapons/test_1h_50_sword",
            "/d/Genesis/specials/guilds/test/armours/standard_shield_40",
            "/d/Krynn/guilds/knights/obj/medal" 
            });
}


