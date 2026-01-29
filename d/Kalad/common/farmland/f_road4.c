/*
 *  /d/Kalad/common/farmland/f_road4
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
    set_short("A gravel road just outside a Red Fang camp");
    set_long("A gravel rood just outside a Red Fang camp. The gravel road"
      + " ends here and leads into a Red Fang camp directly to the northwest"
      + " You hear the sounds of orcs doing their daily chores inside the"
      + " nearby camp. The gravel road leads back into the farmlands to the"
      + " southeast. It is possible to travel to the northwest into the camp"
      + " and southeast back to the farmlands.\n\n");       

    /* Items for this room */        
    add_item( ({ "forest", "sparse forest", "tree", "trees" }),
        "Short dried trees are struggling to survive in the dry hot"
      + " climate. You see a cluster of them that could be called a"
      + " very sparse forest.\n");
   
    add_item( ({ "camp", "orc camp", "red fang camp", "Red Fang camp"}),
        "You see what appears to be a primitive orc camp. Judging by"
      + " the looks of it you think its a Red Fang camp.\n");
    
    add_exit(CAMP_DIR+ "redfang_camp1", "northwest");
    add_exit("f_road3", "southeast");

} /* create_std_road */
