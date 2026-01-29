/*
 * Calian/Blademaster testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_front_calian";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    load_guild("blademasters");

    ::create_test_npc();
    
    // Set up a few basics
    set_name("front_calian_bm");    
    set_short("test front calian blademaster npc");
    set_long("This is a test front calian blademaster npc.\n");
}

public int
special_attack(object target)
{
    command("battack");
        
    refresh_npc();
    return 0;
}


