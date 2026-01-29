/*
 * The Solamnian Knights
 */
#include "../warfare.h";

inherit ARMY_BASE;

#pragma no_clone
#pragma strict_types

#define WAR_NPC  (WAR_PATH + "npcs/knight/")


public void
configure_army()
{
    set_army_name(KNIGHT_ARMY);

    add_unit("Rose Knight", WAR_NPC + "rose", 4032);
    add_unit("Sword Knight", WAR_NPC + "sword", 3168);
    add_unit("Crown Knight", WAR_NPC + "crown", 2304);
    add_unit("Knight Squire", WAR_NPC + "squire", 1584);
    add_unit("Sentry", WAR_NPC + "sentry", 2160);
}

public int
query_member(object player)
{
    if (player->query_guild_member(SOLAMNIAN_KNIGHTS))
	return 1;
    return 0;
}
