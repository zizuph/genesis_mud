
#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("An animal trail");
    set_long("You reach the edge of a wooded glen. The path continues through the trees " +
       "to the north. The trail leading down is to the south.\n");

      
    add_item(({"wooded glen", "glen"}),
       "The edge of a glen, or valley, spreads out before you to the north. " +
       "Mostly small saplings, mixed with rock outcroppings.\n");
    
    add_item(({"saplings", "tree", "trees", "ping tree"}),
       "Young cedar, mixed with the occasional pine tree make up most of the glen.\n");
    
    add_item(({"rocks", "rock", "granite rocks", "granite", "boulders"}),
       "Rocky outcroppings can be seen peppering the glen.\n"); 
      
    add_item(({"vales", "anduin", "vales of the anduin"}),
       "The Vales of Anduin, also known as Vale of the Great River, " +
       "are the fertile valleys of the Anduin river. They lay between " +
       "the Misty Mountains and Mirkwood, and extend for hundreds of miles.\n");
       
    add_item(({"anduin", "anduin river", "river"}),
       "You can just make out the blue water of the Anduin as it snakes through the " +
       "Vales.\n");
      
    add_item(({"trail", "animal trail", "path"}), 
       "The path is little more than trampled brush, grass and weeds. It continues " +
       "up the foothills to the northwest or through the brush to the south.\n");
    
    add_item(({"bushes", "brush"}),
       "You're in the middle of dense brush and bushes. Mostly green and brown. " +
       "Some have thorns, while the brush lining the path seem safe to pass.\n");
    
    add_item(({"foothills", "hills"}),
       "Rocky, brush filled foothills can be seen rising to the north from here.\n");

    add_prop(ROOM_I_INSIDE, 0);

       
    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR + "hunter_trail05", "south", 0, 0, 1);
    add_exit(MISTY_DIR + "hunter_trail07", "north", 0, 0, 1);

}
