/*
 *  /d/Kalad/common/farmland/farm/rooms/farm3_1
 *
 *  One of the rooms in the farm estates in the Kalad farmlands
 *
 *  Created February 2017, by Andreas Bergstrom (Zignur)
 */
#pragma strict_types
#include "../../defs.h"
inherit ROOMS_DIR + "std_farm";


/* Prototypes */
public void         create_std_farm();


/*
 * Function name:        create_room
 * Description  :        constructor for the room
 */
public void
create_std_farm()
{
    set_short("Inside the hall of House Alexander farm estate");
    set_long("Inside the hall of House Alexander farm estate, even though"
      + " this house is not nearly as extravagant as the Noble Houses"
      + " in the City, it still is much more than a mere farm estate."
      + " Several paintings and banners hang on the polished wooden"
      + " walls, candles burn softly in candle holders. Several colorful"
      + " rugs and mats covers the wooden floor. A storeroom lies east,"
      + " west is what appears to be the servants quarters. A large"
      + " dining hall opens up to the south, the exit to the farmlands"
      + " is to the north.\n");       

    /* Items for this room */
    add_item( ({ "dining hall", "hall"}),
        "The dining hall lies in the middle of the farm estate.\n"); 
    add_item( ({ "servants quarters"}),
        "The servants quarters is where the servants rest when they"
     +  " are not working.\n");      
    add_item( ({ "storeroom"}),
        "You see a storeroom to the east, most likely used to store"
     +  " various things.\n");      
    add_item( ({ "farmland", "farmlands"}),
        "You see the wast farmland stretch out outside of the farm estate.\n");      
   
    add_npc(NPC_DIR + "house_guard_al",2,&->arm_me());
     
    add_exit(FARM_DIR+ "f_road15", "north");
    add_exit("farm3_2", "west");
    add_exit("farm3_3", "east");
    add_exit("farm3_4", "south");
   
} /* create_std_farm*/
