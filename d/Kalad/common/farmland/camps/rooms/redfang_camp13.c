/*
 *  /d/Kalad/common/farmland/camps/rooms/redfang_camp13
 *
 *  One of the rooms in the redfang camp in Kalad
 *
 *  Created October 2014, by Andreas Bergstrom (Zignur)
 */
#pragma strict_types
#include "../defs.h"

inherit ROOMS_DIR + "std_redfang_camp";


/* Prototypes */
public void         create_redfang_camp_room();


/*
 * Function name:        create_redfang_camp_room
 * Description  :        constructor for the room
 */
public void
create_redfang_camp_room()
{
    set_short("eastern part of the camp");
    set_long("In the eastern corner of a Red Fang training camp."
      + " @@get_camp_state_desc@@ The camp stretch out to the"
      + " north, south and to the west.\n\n");      

    add_redfang_camp_items();
    add_redfang_camp_subscriber();
    
    int totalMobs = 0;
    int mobs = 0;
    mobs = random(6)+2;
    totalMobs = totalMobs + mobs;
    
    add_npc(NPC_DIR + "goblin_warrior", mobs, &->arm_me());
 
    if (random(3)) /* 33% chance to spawn trainers */
    {   
        mobs = random(3)+2;
        add_npc(NPC_DIR + "goblin_trainer", mobs, &->arm_me());
        totalMobs = totalMobs + mobs;
    }  
    if (random(10)) /* 10% chance to spawn wolves */
    {
        mobs = random(2)+2;
        add_npc(NPC_DIR + "goblin_wolf", mobs, &->arm_me());
        totalMobs = totalMobs + mobs;
    }
    /* Add the mobs to the counter */
    RF_WAR_ROOM->add_goblin_warriors(totalMobs);
    
    add_exit("redfang_camp17", "north");
    add_exit("redfang_camp8", "south");
    add_exit("redfang_camp12", "west");    
    
} /* create_redfang_camp_room */
