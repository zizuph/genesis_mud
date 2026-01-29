
#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("a wooded glen");
    set_long("You're standing in the glen. The path becomes obvious now, as someone " +
       "has outlined it with whitewashed rocks. Trees of various sizes extend " +
       "from the craggy sheer cliffs to the east and west. To the north " +
       "you can just make out a small clearing and some sort of wooden structure. " +
       "\n");
       
    add_item(({"structure", "wooden structure"}),
       "You just make out a large structure in the middle of a clearing just past the " +
       "trees. It looks like a lodge of sorts.\n");
    
    add_item(({"whitewashed", "white rocks"}),
       "Small rocks painted white outlining the path.\n");
       
    add_item(({"sheer cliffs", "cliffs"}),
       "The precipitous cliffs of the Misty Mountains line the glen on either side. " +
       "They appear too sheer to climb.\n");
      
    add_item(({"wooded glen", "glen"}),
       "The edge of a glen, or valley, spreads out before you to the north. " +
       "Mostly small saplings, mixed with rock outcroppings.\n");
    
    add_item(({"saplings", "tree", "trees", "ping tree"}),
       "Young cedar, mixed with the occasional pine tree make up most of the glen.\n");
    
    add_item(({"rocks", "rock", "granite rocks", "granite", "boulders"}),
       "Rocky outcroppings can be seen peppering the glen.\n"); 
          
    add_item(({"trail", "animal trail", "path"}), 
       "The path is little more than trampled brush, grass and weeds. It continues " +
       "up the foothills to the northwest or through the brush to the southeast.\n");
    
    add_item(({"bushes", "brush"}),
       "You're in the middle of dense brush and bushes. Mostly green and brown. " +
       "Some have thorns, while the brush lining the path seem safe to pass.\n");
    
    add_prop(ROOM_I_INSIDE, 0);
         
    /* The other room,           direction, VBFC, fatigue */
    add_exit("/d/Shire/clubs/huntclub/huntclub_porch", "north", 0, 1);
    add_exit(MISTY_DIR    + "hunter_trail06", "south", 0, 0);

}
