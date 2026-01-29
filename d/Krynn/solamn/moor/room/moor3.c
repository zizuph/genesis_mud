/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

void
create_moor_room()
{

    set_short("Moor");
    set_long(BS("You are still in the moor. Tufts of grass grow all "
         +   "around you and some bushes appear very lonely out here.",SL));

    add_exit(ROOM + "moor2","south",0,3);
    add_exit(ROOM + "moor4","southeast",0,3);

    add_item(({"bush","tuft","grass"}),
	     "It looks ordinary.\n");
    add_item(({"bushes","tufts"}),
	     "They look ordinary.\n");
}



