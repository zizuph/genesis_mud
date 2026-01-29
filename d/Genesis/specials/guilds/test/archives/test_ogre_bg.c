/*
 * Ogre/Bloodguard testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_ogre";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    ::create_test_npc();
    
    // Set up a few basics
    set_name("ogre_bg");
    set_short("test ogre bloodguard npc");
    set_long("This is a test ogre bloodguard npc.\n");
    
    load_guild("bloodguard");
    set_skill(SS_DEFENCE, 85); // drain about 10 defence
}

public int
special_attack(object target)
{
    command("crush");
    command("bgsavage head");
    
    refresh_npc();
           
    return 0;
}
