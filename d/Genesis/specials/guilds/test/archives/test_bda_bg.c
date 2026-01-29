/*
 * BDA/Bloodguard testing NPC
 *
 * Created by Petros, March 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_bda";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    ::create_test_npc();
    
    // Set up a few basics
    set_name("bda_bg");
    set_short("test bda bloodguard npc");
    set_long("This is a test bda bloodguard npc.\n");
    
    load_guild("bloodguard");
}

public int
special_attack(object target)
{
    command("slash");
    command("dfear");
    command("dbreath");
    command("bgsavage head");
    
    refresh_npc();
           
    return 0;
}
