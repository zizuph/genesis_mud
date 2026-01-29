/*
 *  /d/Kalad/common/farmland/farm/rooms/farm3_2
 *
 *  One of the roads in the farmlands west of kalad
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
    set_short("Inside the servants quarters");
    set_long("Inside of the servants quarters of the farm estate."
      + " This is clearly where the servants sleep, even so it is"
      + " kept in perfect order. Beds neatly made with with clean"
      + " sheets line the walls, oaken chests stand beside the beds."   
      + " Several paintings and banners hang on the polished wooden"
      + " walls, candles burn softly in candle holders. Several colorful"
      + " rugs and mats covers the wooden floor. The main hall is"
      + " located to the east.\n");       

    /* Special items for this room */
    add_item( ({ "bed", "beds"}),
        "Several beds, neatly made with clean sheets stand along the walls."
      + " Providing a place for the servants of the farm estate to sleep.\n");  
    add_item( ({ "chests", "chest", "oaken chests","oaken chest"}),
        "An oaken chest is standing by each bed, holding the little"
      + " possessions owned by the servants working in the farm estate.\n");
    add_item( ({ "sheets", "sheet"}),
        "The beds are made with fresh sheets, providing a comfortable"
      + " place to sleep.\n");  
    add_item( ({ "main hall", "hall"}),
        "The main hall is the entrance to the large farm estate.\n");  
   
    add_exit("farm3_1", "east");
   
} /* create_std_farm*/
