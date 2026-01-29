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
    set_name("knight_bm_dfear");    
    set_short("test knight blademaster dfear npc");
    set_long("This is a test knight blademaster npc.\n");
    
    set_skill(SS_DEFENCE, 57);
    set_skill(SS_PARRY, 80);
}

public int
special_attack(object target)
{
    command("kattack");
    command("mount warhorse");
    command("battack");
    command("kheroism");
    
    refresh_npc();
    return 0;
}


