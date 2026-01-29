/* /d/Raumdor/common/vallaki/indoor/house01.c
*
*
* Nerull 2021
*
*/

#include "../defs.h"

inherit STD_ROOM;

void
create_vallaki_outdoor()
{
}


void
create_room()
{
    ::create_room();
    
    create_vallaki_outdoor();
}

