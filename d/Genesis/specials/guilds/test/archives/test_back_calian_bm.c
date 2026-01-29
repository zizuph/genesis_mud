/*
 * Calian/Blademaster testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_back_calian";

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
    set_name("back_calian_bm");    
    set_short("test back calian blademaster npc");
    set_long("This is a test back calian blademaster npc.\n");
}

public int
special_attack(object target)
{
    string name;
    object * others = query_team_others();
    if (sizeof(others))
    {   
        name = OB_NAME(others[0]);
        command("mbsw " + name);
    }
    command("battack");
        
    refresh_npc();
    return 0;
}


