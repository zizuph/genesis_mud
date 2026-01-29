/*
 *  /d/Kalad/common/farmland/f_road3
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
    set_short("A gravel road inside a sparse forest northwest of Kalad");
    set_long("A gravel road inside a spearse forest northwest of Kalad."
      + " You can see the city gates far to the southeast, farmlands are"
      + " barely visible far to the southwest. You see some sort of camp"
      + " futher into the sparse forest to the northwest. The gravel road"
      + " continues towards the camp or back into the farmlands to the"
      + " southeast. It is possible to travel to the northwest and to the"
      + " southeast.\n\n");       

     /* Items for this room */ 
    add_item( ({ "forest", "sparse forest", "tree", "trees" }),
        "Short dried trees are struggling to survive in the dry hot"
      + " climate. You see a cluster of them that could be called a"
      + " very sparse forest.\n");   
    add_item( ({ "camp", "orc camp", "red fang camp", "Red Fang camp"}),
        "You see what appears to be a primitive orc camp. Judging by"
      + " the looks of it you think its a Red Fang camp.\n");
   
    add_exit("f_road4", "northwest");
    add_exit("f_road2", "southeast");
   
} /* create_std_road */
