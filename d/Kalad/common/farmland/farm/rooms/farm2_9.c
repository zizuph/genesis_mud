/*
 *  /d/Kalad/common/farmland/farm/rooms/farm2_9
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
    set_short("Inside the west guards quarters");
    set_long("Inside of the western part of the guards quarters."
      + " The owners of this state is clearly very worried about"
      + " the security of their property. The guards quarters are"
      + " huge and must take up the better part of the house. Several"    
      + " beds with fresh sheets line the walls, oaken chests stand"
      + " beside the beds. Several paintings and banners hang on the"
      + " polished wooden walls, candles burn softly in candle holders."
      + " Several colorful rugs and mats covers the wooden floor. The"
      + " main entrance to the guard quarters lies to the east.\n");       

    /* Special items for this room */
    add_item( ({ "bed", "beds"}),
        "Several beds, neatly made with clean sheets stand along the walls."
      + " Providing a place for the guards of the farm estate to sleep.\n");  
    add_item( ({ "chests", "chest", "oaken chests","oaken chest","chest"}),
        "An oaken chest is standing by each bed, holding the little"
      + " possessions owned by the guards employed in the farm estate.\n");
    add_item( ({ "sheets", "sheet"}),
        "The beds are made with fresh sheets, providing a comfortable"
      + " place to sleep.\n");  
    
    add_npc(NPC_DIR + "house_guard_a",4,&->arm_me());   

    add_exit("farm2_7", "east");
   
} /* create_std_farm*/

