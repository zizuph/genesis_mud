/*
 * Base Neidar testing NPC
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
        "/d/Genesis/specials/guilds/test/weapons/test_axe",
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
    set_name("neidar_npc");
    set_short("test neidar npc");
    set_long("This is a test neidar npc.\n");
    config_test_npc(170, "dwarf");
    
    load_guild("neidar");
}

public int
special_attack(object target)
{
    command("chop");
    command("dmaster");

    refresh_npc();
           
    return 0;
}
