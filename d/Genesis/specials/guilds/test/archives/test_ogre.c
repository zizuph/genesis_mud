/*
 * Base Gladiator testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/test_npc";

public void
setup_ogre_eq(object player)
{
    object club;
    
    club = clone_object("/d/Emerald/common/guild/aod/wep/forgeclub9");
    club->set_pen(60);
    club->set_hit(60);
    club->move(player);
    club = clone_object("/d/Emerald/common/guild/aod/wep/forgeclub9");
    club->set_pen(60);
    club->set_hit(60);
    club->move(player);
    clone_object("/d/Emerald/common/guild/aod/arm/forgearm8")->move(player);
    clone_object("/d/Emerald/common/guild/aod/arm/forgearm9")->move(player);

    player->command("wear all");
    player->command("wield all");    
}

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    // Set up a few basics
    set_name("ogre_npc");
    set_short("test ogre npc");
    set_long("This is a test ogre npc.\n");
    config_test_npc(187, "human");
    
    load_guild("ogre");
    
    set_alarm(0.0, 0.0, &setup_ogre_eq(this_object()));
}

public string *
query_equipment_list()
{
    return ({ 

            });
}

public int
special_attack(object target)
{
    command("crush");
    
    refresh_npc();
           
    return 0;
}
