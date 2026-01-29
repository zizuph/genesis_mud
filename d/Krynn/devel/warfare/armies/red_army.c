/*
 * The Red Dragonarmy
 */
#include "../warfare.h";

inherit ARMY_BASE;

#pragma no_clone
#pragma strict_types

#define WAR_NPC  (WAR_PATH + "npcs/red/")


public void
configure_army()
{
    set_army_name(RED_ARMY);
    
    add_unit("Officer", WAR_NPC + "officer", 3888);
    add_unit("Soldier", WAR_NPC + "soldier", 2880);
    add_unit("Mercenary", WAR_NPC + "mercenary", 2160);
    add_unit("Recruit", WAR_NPC + "recruit", 1440);
    add_unit("Aurak", WAR_NPC + "aurak", 2880);
    add_unit("Sivak", WAR_NPC + "sivak", 2592);
    add_unit("Bozak", WAR_NPC + "bozak", 1872);
    add_unit("Kapak", WAR_NPC + "kapak", 1440);
    add_unit("Baaz", WAR_NPC + "baaz", 1152);
}

public int
query_member(object player)
{
    if (player->query_guild_member("Dragonarmy") &&
	player->query_dragonarmy_division() == "Red")
	return 1;
    
    return 0;
}
