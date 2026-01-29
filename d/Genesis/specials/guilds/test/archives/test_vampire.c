/*
 * Base Vampire testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/test_npc";

public void
setup_vampire_effects()
{
    // Set up Celerity
    object oldtp = this_player();
    set_this_player(this_object()); 
    "/d/Terel/guilds/vamp/spells/celerity"->do_ability("");
    set_this_player(oldtp);
}

public string *
query_equipment_list()
{
    return ({ 
            "/d/Genesis/specials/guilds/test/armours/standard_armour_40",
            "/d/Genesis/specials/guilds/test/weapons/test_sword",
            "/d/Genesis/specials/guilds/test/armours/standard_shield_40",
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
    set_name("vampire_npc");
    set_short("test vampire npc");
    set_long("This is a test vampire npc.\n");
    config_test_npc(170, "human");
    
    load_guild("vamp");

    set_alarm(0.0, 0.0, &setup_vampire_effects());
}

public int
special_attack(object target)
{
    command("vflurry head");

    this_object()->add_blood(300);
    setup_vampire_effects();
    refresh_npc();
            
    return 0;
}
