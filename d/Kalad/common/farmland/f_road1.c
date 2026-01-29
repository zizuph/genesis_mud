/*
 *  /d/Kalad/common/farmland/f_road1
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
    set_short("A gravel road just outside of Kalad");
    set_long("A gravel road just outside the gates of Kalad. You can see"
      + " the city gates directly to the east, while wast farmlands"
      + " stretch out to the southwest. You notice a sparse forest far"
      + " away to the northwest. The gravel road continues to the west," 
      + " deeper into the farmlands. It is possible to travel to the east"
      + " and to the west.\n\n");       
      
    /* Items for this room */
    add_item( ({ "forest", "sparse forest", "tree", "trees" }),
        "Short dried trees are struggling to survive in the dry hot"
      + " climate. You see a cluster of them that could be called a"
      + " very sparse forest.\n");
    add_item( ({ "gates", "gate" }),
        "This is the large city gate that protects Kalad from intruders.\n");
    
    add_exit("f_road2", "west");
    add_exit("farm_gate", "east");
   
   
} /* create_std_road */
