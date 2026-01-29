/*
 *  /d/Kalad/common/farmland/farm/rooms/farm1_6
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
    set_short("Inside the kitchen");
    set_long("Inside the kitchen in a large farm estate."
      + " A large iron stove dominates the room, it is filled with"
      + " all sorts of cooking pots, making different foods. Several"
      + " shelves are mounted on the walls, used to store various food"
      + " ingredients. Candles are mounted on candle holders along the walls"
      + " providing the room with light, colorful rugs and mats covers the"
      + " wooden floor. The sound of laughter and chattering nobles tells"
      + " you that the dining hall lies to the west.\n");       

    /* Items for this room */
    add_item( ({ "pots", "cooking pots", "pot", "cooking pot"}),
        "Several cooking pots filled with different food are cooking"
      + " on the large iron stove.\n");  
    add_item( ({ "stove", "iron stove", "large iron stove"}),
        "A large iron stove dominates the kitchen, it is filled with"
      + " various cooking pots.\n");  
    add_item( ({ "food"}),
        "All sorts of food are being cooked on the large iron stove.\n");
    add_item( ({ "dining hall", "hall"}),
        "The dining hall lies in the middle of the farm estate.\n");                   

    add_exit("farm1_4", "west");
   
 
} /* create_std_farm*/
