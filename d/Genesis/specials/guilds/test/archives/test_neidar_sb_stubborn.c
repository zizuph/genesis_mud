/*
 * Neidar/Shieldbearer testing NPC
 *
 * Created by Petros, May 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_neidar";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    ::create_test_npc();
    
    // Set up a few basics
    set_name("neidar_sb_stubborn");
    set_short("test neidar shieldbearer npc");
    set_long("This is a test neidar shieldbearers npc.\n");
    
    load_guild("shieldbearers");
}

public int
special_attack(object target)
{
    command("chop");
    command("dmaster");
    command("slam");
    command("battlerage stubbornly");
        
    refresh_npc();
           
    return 0;
}
