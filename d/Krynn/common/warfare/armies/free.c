/*
 * The Free People
 *
 * New NPCs for the Free People added 30 Sept 2018 - Arman
 */
#include "../warfare.h";

inherit ARMY_BASE;
inherit AUTO_RECRUIT; 

#pragma no_clone
#pragma strict_types

#define WAR_NPC  (WAR_PATH + "npcs/free/")
#define NEW_NPC  (WAR_PATH + "npcs/new/free/")


public void
configure_army()
{
    /* The Free People don't need much money */
    set_tax(50);
    set_army_name(FREE_ARMY);

    /* There are special units in North Abanasinia */
    add_unit("QueKiri Warrior", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_warrior", 1000,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA })));
    add_unit("QueKiri Berserker", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_berserker", 2000,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA })));
    add_unit("QueKiri Warlord", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_warlord", 4000,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA })));
    add_unit("QueKiri Marauder", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_marauder", 3000,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA })));
    add_unit("QueKiri Heavy Archer", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_heavy_archer", 3000,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA })));
    add_unit("QueKiri Shaman", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_shaman", 3000,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA })));

    /* There are special units in Central Abanasinia */
    add_unit("QueShu Scout", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_scout", 500,
        &valid_area(, ({ WAR_AREA_CENTRAL_ABANASINIA })));
    add_unit("QueShu Tribesman", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_tribesman", 500,
        &valid_area(, ({ WAR_AREA_CENTRAL_ABANASINIA })));
    add_unit("QueShu Barbarian", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_barbarian", 1000,
        &valid_area(, ({ WAR_AREA_CENTRAL_ABANASINIA })));
    add_unit("QueShu Outrider", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_outrider", 1500,
        &valid_area(, ({ WAR_AREA_CENTRAL_ABANASINIA })));
    add_unit("QueShu Archer", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_archer", 1500,
        &valid_area(, ({ WAR_AREA_CENTRAL_ABANASINIA })));

    /* There are special units in Southern Abanasinia - Newports */
    add_unit("QueTeh Scout", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_scout_np", 500,
        &valid_area(, ({ WAR_AREA_NEWPORT })));
    add_unit("QueTeh Tribesman", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_tribesman_np", 500,
        &valid_area(, ({ WAR_AREA_NEWPORT })));
    add_unit("QueTeh Barbarian", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_barbarian_np", 1000,
        &valid_area(, ({ WAR_AREA_NEWPORT })));
    add_unit("QueTeh Outrider", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_outrider_np", 1500,
        &valid_area(, ({ WAR_AREA_NEWPORT })));
    add_unit("QueTeh Archer", 
        "/d/Krynn/common/warfare/npcs/new/free/plains_warfare_archer_np", 1500,
        &valid_area(, ({ WAR_AREA_NEWPORT })));

    /* There are special units in Solace WAR_AREA_SOLACE */ 
    add_unit("Seeker Believer", 
        "/d/Krynn/common/warfare/npcs/new/free/seeker_warfare_believer", 500,
        &valid_area(, ({ WAR_AREA_SOLACE })));
    add_unit("Seeker Guard", 
        "/d/Krynn/common/warfare/npcs/new/free/seeker_warfare_guard", 500,
        &valid_area(, ({ WAR_AREA_SOLACE })));
    add_unit("Seeker Enforcer", 
        "/d/Krynn/common/warfare/npcs/new/free/seeker_warfare_enforcer", 1000,
        &valid_area(, ({ WAR_AREA_SOLACE })));
    add_unit("Seeker Templar", 
        "/d/Krynn/common/warfare/npcs/new/free/seeker_warfare_templar", 1500,
        &valid_area(, ({ WAR_AREA_SOLACE })));
    add_unit("Seeker Charlatan", 
        "/d/Krynn/common/warfare/npcs/new/free/seeker_warfare_charlatan", 3000,
        &valid_area(, ({ WAR_AREA_SOLACE })));

    /* There are special units in Nighlund, Estwilde, and WSP */ 
    add_unit("Rebel Vigilante", 
        "/d/Krynn/common/warfare/npcs/new/free/rebel_warfare_vigilante", 1000,
        &valid_area(, ({ WAR_AREA_NIGHLUND, WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE })));
    add_unit("Rebel Swordsman", 
        "/d/Krynn/common/warfare/npcs/new/free/rebel_warfare_swordsman", 2000,
        &valid_area(, ({ WAR_AREA_NIGHLUND, WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE })));
    add_unit("Rebel Noble", 
        "/d/Krynn/common/warfare/npcs/new/free/rebel_warfare_noble", 4000,
        &valid_area(, ({ WAR_AREA_NIGHLUND, WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE })));
    add_unit("Rebel Longbowman", 
        "/d/Krynn/common/warfare/npcs/new/free/rebel_warfare_longbowman", 2000,
        &valid_area(, ({ WAR_AREA_NIGHLUND, WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE })));
    add_unit("Hedge Wizard", 
        "/d/Krynn/common/warfare/npcs/new/free/rebel_warfare_wizard", 3000,
        &valid_area(, ({ WAR_AREA_NIGHLUND, WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE })));

    /* There are special units in Guardlund */ 
    add_unit("Rebel", 
        "/d/Krynn/common/warfare/npcs/new/free/rebel_warfare_rebel", 500,
        &valid_area(, ({ WAR_AREA_GUARDLUND })));
    add_unit("Rebel Pikeman", 
        "/d/Krynn/common/warfare/npcs/new/free/rebel_warfare_pikeman", 500,
        &valid_area(, ({ WAR_AREA_GUARDLUND })));
    add_unit("Rebel Militiaman", 
        "/d/Krynn/common/warfare/npcs/new/free/rebel_warfare_militiaman", 1000,
        &valid_area(, ({ WAR_AREA_GUARDLUND })));


    /* There are special units in Throtyl Plains */ 
    add_unit("Goblin Archer", 
        "/d/Krynn/common/warfare/npcs/new/free/throtyl_warfare_goblin", 500,
        &valid_area(, ({ WAR_AREA_THROTYL, WAR_AREA_TRELGORN })));
    add_unit("Hobgoblin Looter", 
        "/d/Krynn/common/warfare/npcs/new/free/throtyl_warfare_hobgoblin", 500,
        &valid_area(, ({ WAR_AREA_THROTYL, WAR_AREA_TRELGORN })));
    add_unit("Bugbear", 
        "/d/Krynn/common/warfare/npcs/new/free/throtyl_warfare_bugbear", 1000,
        &valid_area(, ({ WAR_AREA_THROTYL, WAR_AREA_TRELGORN })));
    add_unit("Ogre Marauder", 
        "/d/Krynn/common/warfare/npcs/new/free/throtyl_warfare_ogre", 3000,
        &valid_area(, ({ WAR_AREA_THROTYL, WAR_AREA_TRELGORN })));
    add_unit("Ogre Magi", 
        "/d/Krynn/common/warfare/npcs/new/free/throtyl_warfare_magi", 5000,
        &valid_area(, ({ WAR_AREA_THROTYL, WAR_AREA_TRELGORN })));


    /* There are special units in Icewall Glacier */ 
    add_unit("Icewall Barbarian", 
        "/d/Krynn/common/warfare/npcs/new/free/icewall_warfare_barbarian", 1000,
        &valid_area(, ({ WAR_AREA_ICEWALL })));
    add_unit("Icewall Reaver", 
        "/d/Krynn/common/warfare/npcs/new/free/icewall_warfare_reaver", 2000,
        &valid_area(, ({ WAR_AREA_ICEWALL })));
    add_unit("Icewall Chieftain", 
        "/d/Krynn/common/warfare/npcs/new/free/icewall_warfare_chieftain", 4000,
        &valid_area(, ({ WAR_AREA_ICEWALL })));
    add_unit("Icewall Winternorn", 
        "/d/Krynn/common/warfare/npcs/new/free/icewall_warfare_winternorn", 3000,
        &valid_area(, ({ WAR_AREA_ICEWALL })));

    /* Special elven units for Qualinesti forest */

    /* Uncomment when Qualinesti forest added to warfare areas

    add_unit("Elven Scout", 
        "/d/Krynn/common/warfare/npcs/new/free/qualinesti_warfare_scout", 1000,
        &valid_area(, ({ WAR_AREA_QUALINESTI })));
    add_unit("Elven Ranger", 
        "/d/Krynn/common/warfare/npcs/new/free/qualinesti_warfare_ranger", 1000,
        &valid_area(, ({ WAR_AREA_QUALINESTI })));
    add_unit("Elven Skirmisher", 
        "/d/Krynn/common/warfare/npcs/new/free/qualinesti_warfare_skirmisher", 1000,
        &valid_area(, ({ WAR_AREA_QUALINESTI })));
    add_unit("Elven Archer", 
        "/d/Krynn/common/warfare/npcs/new/free/qualinesti_warfare_archer", 1000,
        &valid_area(, ({ WAR_AREA_QUALINESTI })));
    add_unit("Elven Magus", 
        "/d/Krynn/common/warfare/npcs/new/free/qualinesti_warfare_magus", 1000,
        &valid_area(, ({ WAR_AREA_QUALINESTI })));

    */


    
    /* These units are the default.. should never clone. If they do then an area
       hasn't been set up properly */
    add_unit("Farmer", "/d/Krynn/solamn/road/npc/farmer", 150,
        &invalid_area(, ({ WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND, WAR_AREA_ICEWALL,
                           WAR_AREA_THROTYL, WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_SOLACE,
                           WAR_AREA_NEWPORT, WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE,
                           WAR_AREA_GUARDLUND, WAR_AREA_TRELGORN })));
    add_unit("Cowboy",  "/d/Krynn/solamn/road/npc/cowboy", 200,
        &invalid_area(, ({ WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND, WAR_AREA_ICEWALL,
                           WAR_AREA_THROTYL, WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_SOLACE,
                           WAR_AREA_NEWPORT, WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE,
                           WAR_AREA_GUARDLUND, WAR_AREA_TRELGORN })));
    add_unit("Warrior", "/d/Krynn/solamn/road/npc/warrior", 300,
        &invalid_area(, ({ WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND, WAR_AREA_ICEWALL,
                           WAR_AREA_THROTYL, WAR_AREA_CENTRAL_ABANASINIA, WAR_AREA_SOLACE,
                           WAR_AREA_NEWPORT, WAR_AREA_WESTSOL, WAR_AREA_ESTWILDE,
                           WAR_AREA_GUARDLUND, WAR_AREA_TRELGORN })));
}

public void
army_effect()
{
    auto_recruit();
}

public int
query_member(object player)
{
    if (WAR_CLUB_ADMIN->query_warfare_army(player) == FREE_ARMY)
	return 1;

    return 0;
}
