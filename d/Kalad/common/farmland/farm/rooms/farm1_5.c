/* 
 *  /d/Kalad/common/farmland/farm/rooms/farm1_5
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
    set_short("Inside the master bedroom");
    set_long("Inside the master bedroom in a large farm estate."
      + " A huge bed dominates the room, it is filled with"
      + " extravagant pillows and luxurious blankets. Windows provide"
      + " the room with a view over the farmlands outside, candles burn"
      + " softly in candle holders along the walls providing the room"
      + " with light. Colorful rugs and mats covers the wooden floor."
      + " The sound of laughter and chattering nobles tells you that the"
      + " dining hall lies to the east.\n");       

    /* Items for this room */
    add_item( ({ "bed", "huge bed", "wooden bed","huge wooden bed"}),
        "A huge very luxurious bed, that is filled with very comfortable"
      + " extravagant pillows and luxurious blankets, you have no doubt"
      + " that one would sleep like a king in this bed.\n");     
    add_item( ({ "pillow", "pillows", "extravagant pillows"}),
        "Several extravagant pillows lie in the huge bed, making it"
      + " look very comfortable.\n"); 
    add_item( ({ "blanket", "blankets", "luxurious blankets"}),
        "Several luxurious blankets lie in the huge bed, making it"
      + " look very comfortable.\n"); 
    add_item( ({ "dining hall", "hall"}),
        "The dining hall lies in the middle of the farm estate.\n");                   

    add_exit("farm1_4", "east");
   
} /* create_std_farm*/
