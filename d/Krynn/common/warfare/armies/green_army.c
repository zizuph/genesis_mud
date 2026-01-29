/*
 * The Green Dragonarmy
 */
#include "../warfare.h";

inherit ARMY_BASE;
inherit AUTO_RECRUIT; 

#pragma no_clone
#pragma strict_types

#define WAR_NPC  (WAR_PATH + "npcs/new/green/")


public void
configure_army()
{
    set_army_name(GREEN_ARMY);
    
    // Standard Dragonarmy Spawns
    add_unit("Green Baaz Draconian", WAR_NPC + "gda_warfare_baaz", 500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Green Dragonarmy Scout", WAR_NPC + "gda_warfare_scout", 500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Green Kapak Draconian", WAR_NPC + "gda_warfare_kapak", 750,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Green Dragonarmy Mercenary", WAR_NPC + "gda_warfare_mercenary", 750,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Green Bozak Draconian", WAR_NPC + "gda_warfare_bozak", 1500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Green Dragonarmy Soldier", WAR_NPC + "gda_warfare_soldier", 1000,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    // Elite Dragonarmy Spawns
    add_unit("Green Dragon", WAR_NPC + "gda_warfare_dragon", 10000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Green Aurak Draconian", WAR_NPC + "gda_warfare_aurak", 3000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Green Sivak Draconian", WAR_NPC + "gda_warfare_sivak", 2000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Green Dragonarmy High Officer", WAR_NPC + "gda_warfare_high_officer", 
        3000, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Green Dragonarmy Officer", WAR_NPC + "gda_warfare_officer", 
        2000, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Green Dragonarmy Elite Soldier", WAR_NPC + "gda_warfare_elite_soldier", 
        1500, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));
}

public int
query_member(object player)
{
    if (player->query_guild_member("Dragonarmy") &&
	player->query_dragonarmy_division() == "green")
    {
	return 1;
    }

    if (WAR_CLUB_ADMIN->query_warfare_army(player) == GREEN_ARMY)
	return 1;

    return 0;
}

public void
army_effect()
{
    auto_recruit();
}
