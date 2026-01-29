/*
 * Knight/Blademaster testing NPC
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
    load_guild("blademasters");

    ::create_test_npc();
    
    // Set up a few basics
    set_name("knight_khero_bm");    
    set_short("test knight khero blademaster npc");
    set_long("This is a test knight khero blademaster npc.\n");
    
    clone_object("/d/Genesis/specials/guilds/test/objects/khero_object")->move(this_object());
}

public int
special_attack(object target)
{
    command("kattack");
    command("mount warhorse");
    command("battack");
        
    refresh_npc();
    return 0;
}


