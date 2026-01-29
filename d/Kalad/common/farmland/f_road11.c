/*
 *  /d/Kalad/common/farmland/f_road11
 *
 *  One of the roads in the farmlands west of kalad
 *
 *  Created February 2017, by Andreas Bergstrom (Zignur)
 */
#pragma strict_types
#include "defs.h"
inherit FARM_DIR + "std_road";


/* Prototypes */
public void         create_std_road();


/*
 * Function name:        create_room
 * Description  :        constructor for the room
 */
public void
create_std_road()
{
    set_short("A gravel road just outside a farm estate");
    set_long("A gravel road just outside a farm estate. You can see"
      + " the city gates to the northeast, wast farmlands surrounds"
      + " the road. You stand just in front of a large farm estate"
      + " the entrance lies directly to the south. The road leads"
      + " into the estate or north back to the main road. It is"
      + " possible to travel north and to the south.\n\n");       

    /* Items for this room */       
    add_item( ({ "farm", "estate", "farm estate", "large farm estate"}),
        "A large farm estate, it looks very well tended so your guess"
      + " is that it belongs to some rich noble family.\n"); 
    add_item( ({ "entrance", "door", "doors", "wooden doors"}),
        "The entrance to the large farm estate consist of two wooden"
      + " doors. A red banner hangs over each door showing that"
      + " this estate belongs to the house of Aemilius.\n"); 
   add_item( ({ "banner", "banners", "red banner", "red banners"}),
        "A red banner hangs over each door, proudly displaying the"
      + " emblem of the House of Aemilius.\n"); 
   add_item( ({ "emblem", "emblems"}),
        "The emblem of the House of Aemilius are very skillfully"
      + " inscribed on the red banners.\n");      
 
    add_exit("f_road10", "north");
    add_exit(ROOMS_DIR +"farm2_1", "south");
   
} /* create_std_road */
