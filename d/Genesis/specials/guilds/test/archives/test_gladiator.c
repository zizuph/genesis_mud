/*
 * Base Gladiator testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/test_npc";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    // Set up a few basics
    set_name("gladiator_npc");
    set_short("test gladiator npc");
    set_long("This is a test gladiator npc.\n");
    config_test_npc(170, "human");
    
    load_guild("gladiator");

    setuid();
    seteuid(getuid());    
    // Load Equipment
    clone_object("/d/Genesis/specials/guilds/test/armours/standard_armour_40")->move(this_object());
    clone_object("/d/Genesis/specials/guilds/test/weapons/test_axe")->move(this_object());
    clone_object("/d/Genesis/specials/guilds/test/armours/standard_shield_40")->move(this_object());
    command("wield all");
    command("wear all");
}

public int
special_attack(object target)
{
    command("berserk");
    command("charge");
    
    refresh_npc();
           
    return 0;
}
