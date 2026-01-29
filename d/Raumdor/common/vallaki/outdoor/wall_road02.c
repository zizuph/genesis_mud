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
    
    set_short("A road by the northwest wall");
    
    set_long("The stomped earth road running between the "
        +"very meticulously maintained stone wall and the "
        +"rather dilapidated houses seems well used. "
        +"You see a building to your southeast with flaking "
        +"paint and an overgrown yard, but you do not see an "
        +"entrance from this side.\n\n");
    
    add_item(({"wall", "stone wall"}),
        "The wall seem to be in excellent shape. Obviously "
        +"the town spares no expense in maintaining their only "
        +"means of keeping the undead on the outside.\n");
        
    add_item(({"road", "ground", "earth"}),
        "The road running through seems almost to have been made "
        +"simply by the constant wear and tear of people walking here."
        +"There are no gutters, and no surfacing allowing carts to "
        +"roll on it if the weather gets wet. You suspect a heavy rain "
        +"would turn this road into a mud trench.\n");
        
    add_item(({"house","houses"}),
        "You see a single house to your southeast, which is the only"
        +"one nearby. It seems a bit dilapidated, and the yard is overgrown"
        +"with knee high grass that no-one seems to have cut in quite a "
        +"while. Regardless of it looking quite abandoned, you can hear "
        +"voices and sometimes laughter from the house. You see no entrance"
        +"from this direction.\n");
    
    add_item(({"paint", "flaking paint"}),
        "Upon closer inspection, the flaking paint on the building seem "
        +"to be only a surface problem. The walls are still intact and strong, "
        +"but for how long?.\n"); 

    add_item(({"yard", "grass"}),
        "The long grass on the yard looks like it hasn't been cut for years. "
        +"Gardening is obviously not an interest for whoever lives there.\n ");

    reset_room();
    add_exit(VALLAKI_OUTDOOR_DIR + "wall_road01","northeast");
    
    
}


void reset_room()
{
}
