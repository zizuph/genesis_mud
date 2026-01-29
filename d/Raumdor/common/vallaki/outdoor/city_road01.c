/* /d/Raumdor/common/vallaki/outdoor/road02.c
*
*
* Nerull 2021
*
*/

#include "../defs.h"

inherit VALLAKI_ROAD_STD_ROOM;


void
create_vallaki_outdoor()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_LIGHT, 2);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    
    set_short("By the large fire-pit");
    
    set_long("Here in the center courtyard of the temple, a "
        +"very large rectangular fire-pit has been placed. The "
        +"pit is recessed into the floor with iron fences running "
        +"along the long sides. On the short sides there are "
        +"steps leading down to the massive bed of infernally "
        +"hot coals burning there. Above the fire-pit "
        +"the roof is open, allowing the hot air to escape. "
        +"Despite this constant exchange of air, you still note "
        +"a faint smell of burnt flesh and hair here.\n");
    
    add_item(({"courtyard"}),
        "The courtyard is paved with the same dark granite as "
        +"the rest of the temple, but it is open to the sky. "
        +"Dominating this courtyard is a large fire-pit. Aside "
        +"from that you see nothing particular here.\n");
        
    add_item(({"floor", "ground"}),
        "The floor is made up of very dark granite. In contrast "
        +"to the white walls, the floor almost looks black. Recessed "
        +"into the floor is a large rectangular fire-pit.\n");
        
    add_item(({"pit", "fire pit", "firepit", "fire-pit"}),
        "The pit is covered in burning coals, and you can feel "
        +"the heat radiating from it. Sometimes flames burst upward "
        +"from the bed of coal only to quickly dissipate again.\n");
        
    add_item(({"smell", "air"}),
        "The hot air surrounding the firepit is smelling slightly "
        +"of burnt flesh and hair.\n");
    
    add_exit(VALLAKI_OUTDOOR_DIR + "road01","south");
    
    reset_room();
}


void reset_room()
{
}
