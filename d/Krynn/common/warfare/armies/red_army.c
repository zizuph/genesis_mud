/*
 * The Red Dragonarmy
 */
#include "../warfare.h";

inherit ARMY_BASE;
inherit AUTO_RECRUIT; 

#pragma no_clone
#pragma strict_types

#define WAR_NPC  (WAR_PATH + "npcs/new/red/")


public void
configure_army()
{
    set_army_name(RED_ARMY);
    
    // Standard Dragonarmy Spawns
    add_unit("Red Baaz Draconian", WAR_NPC + "rda_warfare_baaz", 500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Red Dragonarmy Scout", WAR_NPC + "rda_warfare_scout", 500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Red Kapak Draconian", WAR_NPC + "rda_warfare_kapak", 750,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Red Dragonarmy Mercenary", WAR_NPC + "rda_warfare_mercenary", 750,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Red Bozak Draconian", WAR_NPC + "rda_warfare_bozak", 1500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Red Dragonarmy Soldier", WAR_NPC + "rda_warfare_soldier", 1000,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    // Elite Dragonarmy Spawns
    add_unit("Red Dragon", WAR_NPC + "rda_warfare_dragon", 10000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Red Aurak Draconian", WAR_NPC + "rda_warfare_aurak", 3000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Red Sivak Draconian", WAR_NPC + "rda_warfare_sivak", 2000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Red Dragonarmy High Officer", WAR_NPC + "rda_warfare_high_officer", 
        3000, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Red Dragonarmy Officer", WAR_NPC + "rda_warfare_officer", 
        2000, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Red Dragonarmy Elite Soldier", WAR_NPC + "rda_warfare_elite_soldier", 
        1500, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));
}

public int
query_member(object player)
{
    if (player->query_guild_member("Dragonarmy") &&
	player->query_dragonarmy_division() == "red")
	return 1;

    if (WAR_CLUB_ADMIN->query_warfare_army(player) == RED_ARMY)
	return 1;
    
    return 0;
}

public void
army_effect()
{
    auto_recruit();
}
