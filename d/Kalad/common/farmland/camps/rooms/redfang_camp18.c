/*
 *  /d/Kalad/common/farmland/camps/rooms/redfang_camp18
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
    set_short("meeting area in the northeastern part of the camp");
    set_long("In the northeastern corner of a Red Fang training"
      + " camp. @@get_camp_state_desc@@ A huge campfire burns"
      + " in the middle of the area, this must be where the red fang"
      + " commanders meet. The only way out is to the west back into"
      + " the camp.\n\n");      

    add_redfang_camp_items();
    /* special item for this room */
    add_item( ({ "campfire", "huge campfire","fire","huge fire"}),
                 "A huge campfire burns in the middle of the area," +
                 " spreading light and warmth.\n");
    
    add_redfang_camp_subscriber();
    int totalMobs = 0;
    int mobs = 0;
    totalMobs = totalMobs + mobs;
    
    add_npc(NPC_DIR + "goblin_commander", 1, &->arm_me());
 
    if (random(3)) /* 33% chance to spawn trainers */
    {   
        mobs = random(3)+2;
        add_npc(NPC_DIR + "goblin_trainer", mobs, &->arm_me());
        totalMobs = totalMobs + mobs;
    }  
    if (random(2)) /* 50% chance to spawn wolves */
    {
        mobs = random(2)+4;
        add_npc(NPC_DIR + "goblin_wolf", mobs, &->arm_me());
        totalMobs = totalMobs + mobs;
    }
    /* Add the mobs to the counter */
    RF_WAR_ROOM->add_goblin_warriors(totalMobs);
    add_exit("redfang_camp17", "west");
  
    
} /* create_redfang_camp_room */
