
#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("An animal trail");
    set_long("You continue along a steep animal trail through the Misty mountain " +
      "foothills. The edge of a wooded glen can be seen to the north. " +
      "You can still see the blue waters of the River Bruinen, and the Great " +
      "Road below you to the southwest.\n");
      
    add_item(({"wooded glen", "glen"}),
       "The edge of a glen, or valley, spreads out before you to the north. " +
       "Mostly small saplings, mixed with rock outcroppings.\n");
    
    add_item(({"saplings", "tree", "trees", "ping tree"}),
       "Young cedar, mixed with the occasional pine tree make up most of the glen.\n");
    
    add_item(({"rocks", "rock", "granite rocks", "granite", "boulders"}),
       "Rocky outcroppings can be seen peppering the glen.\n"); 
      
    add_item(({"river", "bruinen"}),
       "Also called the Loudwater, the river rises from the Misty Mountains " +
       "east of Rivendell, and joins the Mitheithel (Hoarwell) to form the " +
       "River Gwathló or Greyflood..\n");
    
    add_item(({"great road", "road"}),
       "You can see the great road below from High Pass, stretching throughout " +
       "Grey Havens.\n");
      
    add_item(({"trail", "animal trail", "path"}), 
       "The path is little more than trampled brush, grass and weeds. It continues " +
       "up the foothills to the northwest or through the brush to the southeast.\n");
    
    add_item(({"bushes", "brush"}),
       "You're in the middle of dense brush and bushes. Mostly green and brown. " +
       "Some have thorns, while the brush lining the path seem safe to pass.\n");
    
    add_item(({"foothills", "hills"}),
       "Rocky, brush filled foothills can be seen rising to the north from here.\n");
       
    add_item(({"high pass", "pass", "Cirith Forn en Andrath"}),
       "The High Pass, also named Cirith Forn en Andrath, is an important " +
       "mountain pass over the Misty Mountains.\n");
    

    add_prop(ROOM_I_INSIDE, 0);


    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR + "hunter_trail04", "southwest", 0, 3, 1);
    add_exit(MISTY_DIR + "hunter_trail06", "north", 0, 3, 1);

}
