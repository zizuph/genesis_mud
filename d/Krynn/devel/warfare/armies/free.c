/*
 * The Free People
 */
#include "../warfare.h";

inherit ARMY_BASE;
inherit AUTO_RECRUIT; 

#pragma no_clone
#pragma strict_types

#define WAR_NPC  (WAR_PATH + "npcs/free/")
#define WAR_TABLE (WAR_PATH + "tables/")

public void
configure_army()
{
    set_army_name(FREE_ARMY);
    
    add_unit("Tribe Warrior", WAR_NPC + "tribe_warrior", 560,
	&valid_area(, ({ WAR_AREA_SOLACE, WAR_AREA_NEWPORT,
			     WAR_AREA_CENTRAL_ABANASINIA,
			     WAR_AREA_NORTH_ABANASINIA })));
    
    add_unit("Tribe Farmer", WAR_NPC + "tribe_farmer", 100);
    add_unit("Tribe Shepherd", WAR_NPC + "tribe_sheperd", 100);

    add_unit("Farmer", "/d/Krynn/solamn/road/npc/farmer", 100);
    add_unit("Cowboy",  "/d/Krynn/solamn/road/npc/cowboy", 200);
    add_unit("Warrior", "/d/Krynn/solamn/road/npc/warrior", 300);
}

public void
army_effect()
{
    auto_recruit();
}

public int
query_member(object player)
{
    return 0;
}
