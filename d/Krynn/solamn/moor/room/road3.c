/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

void
create_moor_room()
{

    set_short("On the Highlands");
    set_long(BS("The road continues east and west. The fields are now "
         +   "only east of you and to the west the beginning of a "
         +   "canyon opens below you. There are scattered trees and "
         +   "waterholes visible to the north, a small path seems to "
         +   "lead in their direction.",SL));

    add_exit(ROOM + "road2","east",0,1);
    add_exit(ROOM + "moor1","north",0,2);
    add_exit(ROOM + "road4","west",0,3);

}



