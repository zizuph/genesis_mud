/*
 *  /d/Kalad/common/farmland/f_road7
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
    set_short("A gravel road in the farmlands west of Kalad");
    set_long("A gravel road in the farmlands west of Kalad. You can"
      + " see the city gates to the far east, while wast"
      + " farmlands stretch out to the southwest. You notice a"
      + " sparse forest with what seems to be a camp to the northwest,"
      + " however there is no way to get there from this location."
      + " The gravel road continues to the west deeper into the"
      + " farmlands and to the east towards Kalad. You see wast" 
      + " fields to the south. It is possible to travel to the"
      + " east and to the west.\n\n");       

    /* Items for this room */
    add_item( ({ "gates", "gate" }),
        "This is the large city gate that protects Kalad from intruders.\n");        
    add_item( ({ "forest", "sparse forest", "tree", "trees" }),
        "Short dried trees are struggling to survive in the dry hot"
      + " climate. You see a cluster of them that could be called a"
      + " very sparse forest.\n");
    add_item( ({ "camp", "orc camp", "red fang camp", "Red Fang camp"}),
        "You see what appears to be a primitive orc camp. Judging by"
      + " the looks of it you think its a Red Fang camp.\n");
       
    add_exit("f_road8", "west");
    add_exit("f_road2", "east");   
   
} /* create_std_road */
