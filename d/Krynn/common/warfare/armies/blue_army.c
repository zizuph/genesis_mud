/*
 * The Blue Dragonarmy
 */
#include "../warfare.h";

inherit ARMY_BASE;
inherit AUTO_RECRUIT; 

#pragma no_clone
#pragma strict_types

#define WAR_NPC  (WAR_PATH + "npcs/new/blue/")


public void
configure_army()
{
    set_army_name(BLUE_ARMY);
    
    // Standard Dragonarmy Spawns
    add_unit("Blue Baaz Draconian", WAR_NPC + "bda_warfare_baaz", 500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Blue Dragonarmy Scout", WAR_NPC + "bda_warfare_scout", 500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Blue Kapak Draconian", WAR_NPC + "bda_warfare_kapak", 750,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Blue Dragonarmy Mercenary", WAR_NPC + "bda_warfare_mercenary", 750,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Blue Bozak Draconian", WAR_NPC + "bda_warfare_bozak", 1500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Blue Dragonarmy Soldier", WAR_NPC + "bda_warfare_soldier", 1000,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    // Elite Dragonarmy Spawns
    add_unit("Blue Dragon", WAR_NPC + "bda_warfare_dragon", 10000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Blue Aurak Draconian", WAR_NPC + "bda_warfare_aurak", 3000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Blue Sivak Draconian", WAR_NPC + "bda_warfare_sivak", 2000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Blue Dragonarmy High Officer", WAR_NPC + "bda_warfare_high_officer", 
        3000, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Blue Dragonarmy Officer", WAR_NPC + "bda_warfare_officer", 
        2000, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Blue Dragonarmy Elite Soldier", WAR_NPC + "bda_warfare_elite_soldier", 
        1500, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));
}

public int
query_member(object player)
{
    if (player->query_guild_member("Dragonarmy") &&
	player->query_dragonarmy_division() == "blue")
    {
	return 1;
    }

    if (WAR_CLUB_ADMIN->query_warfare_army(player) == BLUE_ARMY)
	return 1;

    return 0;
}

public void
army_effect()
{
    auto_recruit();
}
