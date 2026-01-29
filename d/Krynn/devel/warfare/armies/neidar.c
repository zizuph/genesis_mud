/*
 * The Neidar Clan
 */
#include "../warfare.h";

inherit ARMY_BASE;

#pragma no_clone
#pragma strict_types

#define WAR_NPC  ("/d/Ansalon/estwilde/living/")

public void
configure_army()
{
    set_army_name("Neidar Clan");

    add_unit("Huge War Boar", WAR_NPC + "warboar", 3100,
	&valid_area(, WAR_AREA_ESTWILDE));
    add_unit("War Boar", WAR_NPC + "warboar02", 1600);
    add_unit("Axeman", WAR_NPC + "dwarf_guard02", 2500);
}

public int
query_member(object player)
{
    if (player->query_guild_member(NEIDAR_GUILD))
	return 1;
    return 0;
}
