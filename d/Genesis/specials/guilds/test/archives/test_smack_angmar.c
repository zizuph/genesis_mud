/*
 * Smacking Angmar testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_angmar";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    ::create_test_npc();
    
    // Set up a few basics
    set_name("smack_angmar");
    set_short("test smack angmar npc");
    set_long("This is a test smacking angmar npc.\n");
}

public int
special_attack(object target)
{
    command("smack");
    
    refresh_npc();
           
    return 0;
}
