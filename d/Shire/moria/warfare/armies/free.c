/*
 * The Free People
 */
#include "../warfare.h";

inherit ARMY_BASE;
inherit AUTO_RECRUIT; 

#pragma no_clone
#pragma strict_types

#define WAR_NPC  (WAR_PATH + "npcs/free/")


public void
configure_army()
{
    /* The Free People don't need much money */
    set_tax(50);
    set_army_name(FREE_ARMY);

    /* There are special units in North Abanasinia */    
    add_unit("Que Shu Shepherd", "/d/Krynn/que/shu/living/shepherd", 150,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA,
                             WAR_AREA_CENTRAL_ABANASINIA })));
    add_unit("Que Kiri Shepherd", "/d/Krynn/que/kiri/living/shepherd", 150,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA,
                             WAR_AREA_CENTRAL_ABANASINIA })));
    
    add_unit("Que Teh Shepherd", "/d/Krynn/que/teh/living/shepherd", 150,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA,
                             WAR_AREA_CENTRAL_ABANASINIA })));
    
    add_unit("Que Shu Warrior", "/d/Krynn/que/shu/living/warrior", 350,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA,
                             WAR_AREA_CENTRAL_ABANASINIA })));

    add_unit("Que Kiri Warrior", "/d/Krynn/que/kiri/living/warrior", 350,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA,
                             WAR_AREA_CENTRAL_ABANASINIA })));
    
    add_unit("Que Teh Warrior", "/d/Krynn/que/teh/living/warrior", 350,
        &valid_area(, ({ WAR_AREA_NORTH_ABANASINIA,
                             WAR_AREA_CENTRAL_ABANASINIA })));

    /* There are special units in Nightlund */ 
    add_unit("Zombie", "/d/Krynn/common/warfare/npcs/free/zombie", 200,
        &valid_area(, ({ WAR_AREA_NIGHLUND })));

    add_unit("Skeleton Warrior", "/d/Krynn/common/warfare/npcs/free/skeleton", 350,
        &valid_area(, ({ WAR_AREA_NIGHLUND })));


    /* There are special units in Throtyl Plains */ 
    add_unit("Tribal Goblin", "/d/Krynn/common/warfare/npcs/free/goblin", 150,
        &valid_area(, ({ WAR_AREA_THROTYL })));

    add_unit("Tribal Ogre", "/d/Krynn/common/warfare/npcs/free/ogre", 300,
        &valid_area(, ({ WAR_AREA_THROTYL })));

    add_unit("Hill Giant", "/d/Krynn/common/warfare/npcs/free/hillgiant", 2350,
        &valid_area(, ({ WAR_AREA_THROTYL })));


    /* There are special units in Icewall Glacier */ 
    add_unit("Icewall Warrior", "/d/Krynn/common/warfare/npcs/free/ice_warrior", 200,
        &valid_area(, ({ WAR_AREA_ICEWALL })));

    
    /* These units are the default */
    add_unit("Farmer", "/d/Krynn/solamn/road/npc/farmer", 150,
        &invalid_area(, ({ WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND, WAR_AREA_ICEWALL,
                           WAR_AREA_THROTYL, WAR_AREA_CENTRAL_ABANASINIA })));
    add_unit("Cowboy",  "/d/Krynn/solamn/road/npc/cowboy", 200,
        &invalid_area(, ({ WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND, WAR_AREA_ICEWALL,
                           WAR_AREA_THROTYL, WAR_AREA_CENTRAL_ABANASINIA })));
    add_unit("Warrior", "/d/Krynn/solamn/road/npc/warrior", 300,
        &invalid_area(, ({ WAR_AREA_NORTH_ABANASINIA, WAR_AREA_NIGHLUND, WAR_AREA_ICEWALL,
                           WAR_AREA_THROTYL, WAR_AREA_CENTRAL_ABANASINIA })));
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
