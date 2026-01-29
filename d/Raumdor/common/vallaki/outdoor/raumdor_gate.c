/* /d/Raumdor/common/vallaki/outdoor/road02.c
*
*
* Edeqium 2022
*
*/
#include "../defs.h"

inherit VALLAKI_ROAD_STD_ROOM;

void
create_vallaki_outdoor()
{
    seteuid(getuid());

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    
    set_short("Inside the northwest gate");
    
    set_long("You are currently standing inside the northwest gates of "
        +"Vallaki. The stone wall surrounding the city is here "
        +"tall, sturdy and well repaired. Set into the wall is a huge "
        +"wooden gate leading northwest towards the road to Drakmere. "
        +"There is a dirt road along the wall stretching from the southwest "
        +"and extending northeast, and a cobbled road going "
        +"southeast towards the town centre. "
        +"While the gate and walls seem to be in good repair, the same"
        +"cannot be said for the nearby houses.\n\n");

    add_item(({"house, houses"}),
        "The closest houses are the two to your southeast, in between "
        +"which the cobbled road goes."
        +"Paint flaking from the walls and a cracked window tells"
        +"a tale of neglect. Every now and then you see a guard entering "
        +"or exiting the buildings.\n");
        
    add_item(({"wall", "stone wall","gate","gates"}),
        "The wall seem very well repaired and maintained here, and the massive"
        +"wooden gate probably does a good job keeping enemies out of "
        +"Vallaki. The gate and wall here makes the dilapidated buildings "
        +"nearby seem even more run-down. It seems the defences are "
        +"something this town takes very seriously.\n");
        
    add_item(({"road"}),
        "There's a dirt road going along the wall here, and a cobbled road"
        +"leading into town. Neither road has anything of note that catches "
        +"your eye.\n");
      
    add_item(({"dirt road"}),
        "The dirt road along the wall is just stomped earth. You mostly "
        +"see guards walking on them, but the occational villager pass "
        +"you by as well.\n"); 
    
    add_item(({"cobbled road","stone"}),
        "The cobbled road leading into the city seem sturdy enough to "
        +"drive wagons with cargo on. Aside from the occational loose "
        +"stone it seems reasonably well maintained. "       
        +"This is probably the main trade road leading into the city.\n"); 
 
    add_item(({"guard", "guards"}),
        "You glimpse the occational guard going in and out of the "
        +"buildings to the southeast.\n");
        
    add_item(({"paint", "flaking paint"}),
        "Upon closer inspection, the flaking paint on the buildings seem "
        +"to be only a surface problem. The walls are still intact and strong, "
        +"but for how long?.\n");
    
    add_item(({"window", "cracked window"}),
        "Aside from being dirty there is nothing wrong with most of the windows you see."
        +"Upon inspection, the cracked one seem to have been boarded shut on the inside to "
        +"keep the rain and cold out.\n");
 
    reset_room();

    add_exit(VALLAKI_OUTDOOR_DIR + "wall_road01","southwest");
    add_exit(VALLAKI_OUTDOOR_DIR + "wall_road57","northeast");
    add_exit(VALLAKI_OUTDOOR_DIR + "city_road01","southeast");
    add_exit(VALLAKI_OUTDOOR_DIR + "portcullis_room","northwest");

    
}


void reset_room()
{
}
