/*
 *  /d/Kalad/common/farmland/f_road5
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
    set_short("A gravel road among the fields southwest of Kalad");
    set_long("A gravel road that runs through wast fields southwest"
      + " of Kalad. You can see the city gates to the northeast,"
      + " wast farmlands surrounds the road. You notice a large"
      + " farm estate directly to the south. The road leads south" 
      + " towards the farm estate or north back to the main road."
      + " It is possible to travel north and to the south.\n\n");       

    /* Items for this room */
    add_item( ({ "gates", "gate" }),
        "This is the large city gate that protects Kalad from intruders.\n"); 
    add_item( ({ "farm", "estate", "farm estate", "large farm estate"}),
        "A large farm estate, it looks very well tended so your guess"
      + " is that it belongs to some rich noble family.\n"); 
 
    add_exit("f_road2", "north");
    add_exit("f_road6", "south");
   
} /* create_std_road */
