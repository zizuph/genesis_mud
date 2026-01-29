/*
 *  /d/Kalad/common/farmland/camps/rooms/redfang_camp3
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
    set_short("at the entrance to the camp");
    set_long("Before you lies the entrance to a Red Fang training"
      + " camp. @@get_camp_state_desc@@ The path leads north deeper"
      + " into the camp and southeast towards the farmlands.\n\n");       

    add_redfang_camp_items();

    /* special items for this room */
    add_item( ({ "path" }),
        "The path leads in and out of the camp.\n");
    add_item( ({ "forest", "sparse forest"}),
        "You see a sparse forest surrounding the camp.\n");
    add_item( ({ "farmland", "farmlands"}),
        "The farmlands of Kalad lies to the southeast.\n");	

    add_redfang_camp_subscriber();
    int totalMobs = 0;
    int mobs = 0;
    mobs = random(6)+2;
    totalMobs = totalMobs + mobs;
    
    add_npc(NPC_DIR + "goblin_warrior", mobs, &->arm_me());
 
    if (random(2)) /* 50% chance to spawn trainers */
    {   
        mobs = random(3)+1;
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
    
    add_exit("redfang_camp2", "southeast");
    add_exit("redfang_camp4", "north");
   
} /* create_redfang_camp_room */
