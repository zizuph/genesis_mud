/*
 *  /d/Kalad/common/farmland/farm/rooms/farm1_3
 *
 *   One of the rooms in the farm estates in the Kalad farmlands
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
    set_short("Inside a large storeroom");
    set_long("Inside a large storeroom in the farm estate."
      + " The walls are lined with wooden shelves that hold"
      + " several sacks of flour and various grains. Several candles"
      + " burn softly from candle holders mounted on the walls."   
      + " Several colorful rugs and mats covers the wooden floor."
      + " The main hall is located to the west.\n");       

    /* Special items for this room */
    add_item( ({ "sack", "sacks", "flour", "grain","grains"}),
        "Several sacks or flour and various grains are neatly stored on."
      + " the wooden shelves along the walls.\n");  
    add_item( ({ "shelves", "shelf", "wooden shelf","wooden shelves"}),
        "Wooden shelves are standing along the walls, providing great"
      + " room for storage.\n");  
    add_item( ({ "main hall", "hall"}),
        "The main hall is the entrance to the large farm estate.\n");     
 
    add_exit("farm1_1", "west");
   
} /* create_std_farm*/
