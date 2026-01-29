/*
 * The Neidar Clan
 */
#include "../warfare.h";

inherit ARMY_BASE;
inherit AUTO_RECRUIT;

#pragma no_clone
#pragma strict_types

#define WAR_NPC  ("/d/Krynn/common/warfare/npcs/new/neidar/")

public void
configure_army()
{
    set_army_name(NEIDAR_ARMY);

    // Standard Neidar Spawns
    add_unit("Neidar Wayfinder", WAR_NPC + "neidar_warfare_wayfinder", 500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Neidar Trailblazer", WAR_NPC + "neidar_warfare_trailblazer", 500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Neidar Adventurer", WAR_NPC + "neidar_warfare_adventurer", 750,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Neidar Clansman", WAR_NPC + "neidar_warfare_clansman", 750,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Neidar Axeman", WAR_NPC + "neidar_warfare_axeman", 1500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    add_unit("Neidar Sniper", WAR_NPC + "neidar_warfare_sniper", 1500,
        &valid_area(, ({ WAR_AREA_NEWPORT, WAR_AREA_SOLACE, WAR_AREA_TRELGORN,
        WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_GUARDLUND, WAR_AREA_THROTYL })));

    // Elite Neidar Spawns
    add_unit("Neidar Chieftain", WAR_NPC + "neidar_warfare_chieftain", 3000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Neidar Battlerager", WAR_NPC + "neidar_warfare_battlerager", 2500,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Neidar Slayer", WAR_NPC + "neidar_warfare_slayer", 2000,
        &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Neidar Longbeard", WAR_NPC + "neidar_warfare_longbeard", 
        1500, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Neidar Hammerer", WAR_NPC + "neidar_warfare_hammerer", 
        1500, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));

    add_unit("Neidar Sharpshooter", WAR_NPC + "neidar_warfare_sharpshooter", 
        1500, &valid_area(, ({ WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE, WAR_AREA_ICEWALL,
        WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND })));
    
}

public int
query_tax(string area)
{
    if (area == WAR_AREA_ESTWILDE)
        return ::query_tax(area);
    return 80;
}

public int
query_member(object player)
{
    if (player->query_guild_member(NEIDAR_GUILD))
	return 1;

    if (WAR_CLUB_ADMIN->query_warfare_army(player) == NEIDAR_ARMY)
	return 1;

    return 0;
}

public void
army_effect()
{
    auto_recruit();
}

