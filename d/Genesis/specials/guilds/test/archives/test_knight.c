/*
 * Base Knight testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/test_npc";

public void
setup_knight_effects()
{
    object medal;
    object oldtp = this_player();
    set_this_player(this_object());
    if (objectp(medal = present("pal_med", this_player())))
    {
        medal->set_knight_level(3);
        medal->set_knight_sublevel(11);
    }
    clone_object("/d/Krynn/guilds/knights/guildhall/npcs/steed")->move(environment(this_object()));
    command("mount warhorse");
    set_this_player(oldtp);
}

public string *
query_equipment_list()
{
    return ({ 
            "/d/Genesis/specials/guilds/test/armours/standard_armour_40",
            "/d/Genesis/specials/guilds/test/weapons/test_sword",
            "/d/Genesis/specials/guilds/test/armours/standard_shield_40",
            "/d/Krynn/guilds/knights/obj/medal" 
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
    set_name("knight_npc");    
    set_short("test knight npc");
    set_long("This is a test knight npc.\n");
    config_test_npc(170, "human");

    load_guild("knight");
    
    set_alarm(1.0, 0.0, &setup_knight_effects());
}

public int
special_attack(object target)
{
    command("kattack");
    command("mount warhorse");
    
    refresh_npc();
    return 0;
}


