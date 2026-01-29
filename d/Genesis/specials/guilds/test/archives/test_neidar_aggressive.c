/*
 * Base Neidar testing NPC
 *
 * Created by Petros, February 2009
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
    // Set up a few basics
    set_name("neidar_aggressive_npc");
    set_short("test neidar aggressive npc");
    set_long("This is a test neidar aggressive npc.\n");
    config_test_npc(170, "dwarf");
    
    load_guild("neidar");
}

public int
special_attack(object target)
{
    command("chop");
    command("dmaster");
    command("battlerage aggressively");

    refresh_npc();
           
    return 0;
}
