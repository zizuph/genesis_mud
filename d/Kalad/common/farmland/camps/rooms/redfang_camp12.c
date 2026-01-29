/*
 *  /d/Kalad/common/farmland/camps/rooms/redfang_camp12
 *
 *  One of the rooms in the redfang camp in Kalad
 *
 *  Created October 2015, by Andreas Bergstrom (Zignur)
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
    set_short("middle part of the camp");
    set_long("In the middle part of a Red Fang training camp."
      + " @@get_camp_state_desc@@ You notice a large training"
      + " pit just to west of here. The camp stretch out to"
      + " the north and to the west.\n\n");       

    add_redfang_camp_items();
     /* special item for this room */
    add_item( ({ "pit", "large pit","large training pit","training pit"}),
                 "You see a large pit, most likely used as a sparring" +
                 " area for new recruits.\n");
    
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
        mobs = random(2)+1;
        add_npc(NPC_DIR + "goblin_wolf", mobs, &->arm_me());
        totalMobs = totalMobs + mobs;
    }
    /* Add the mobs to the counter */
    RF_WAR_ROOM->add_goblin_warriors(totalMobs);

    add_exit("redfang_camp16", "north");
    add_exit("redfang_camp7", "south");
    add_exit("redfang_camp13", "east");
    add_exit("redfang_camp11", "west");
    
    
} /* create_redfang_camp_room */
