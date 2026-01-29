/* /d/Raumdor/common/vallaki/indoor/house01.c
*
*
* Nerull 2021
*
*/

#include "../defs.h"

inherit VALLAKI_HOUSE_STD_ROOM;


void
create_vallaki_indoor()
{
    seteuid(getuid());
    
    set_short("Inside a house in Drakmere");
    
    set_long("You are now within a modest wooden dwelling. "+
    "There are a couple of beds that line the west wall, a "+
    "small fireplace on the north wall, a few chests and "+
    "drawers on the east wall, while a large, warm and cozy "+
    "looking rug covers the floor. There is a table with "+
    "a couple chairs surrounding it standing here.\n");
    
    add_item(({"iron pot","pot"}),"You smell something good cooking.\n");
    
    
    add_exit(VALLAKI_OUTDOOR_DIR + "road01","west");
    
    reset_room();
}


void
reset_room()
{
}
