/*
 * Base Blue Dragonarmy testing NPC
 *
 * Created by Petros, March 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/test_npc";

public void
setup_rda_effects()
{
    object oldtp = this_player();
    set_this_player(this_object());
    
    command("dfear");

    set_this_player(oldtp);
}

public string *
query_equipment_list()
{
    return ({ 
            "/d/Genesis/specials/guilds/test/armours/standard_armour_40",
            "/d/Genesis/specials/guilds/test/weapons/test_2h_60_polearm",
            });
}

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    // Set up a few basics
    set_name("rda_npc");    
    set_short("test rda npc");
    set_long("This is a test rda npc.\n");
    config_test_npc(170, "human");

    load_guild("rda");
    
    set_alarm(1.0, 0.0, &setup_rda_effects());
}

public int
special_attack(object target)
{
    command("impale");
    command("dfear");
    command("dbreath");
    
    refresh_npc();
    return 0;
}


