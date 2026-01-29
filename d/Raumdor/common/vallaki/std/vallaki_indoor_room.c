/* /d/Raumdor/common/vallaki/outdoor/road01.c
*
*
* Nerull 2021
*
*/

#include "../defs.h"

inherit STD_ROOM;

void
create_vallaki_indoor()
{
}


void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    
    ::create_room();
    
    create_vallaki_indoor();
}

