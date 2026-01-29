/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom";

void
create_change_room()
{
    set_short("On the plains");
    set_long(BS("You are standing in the middle of nowhere on the plains of "
         +   "Solamnia, brownish, knee high grass stretching out in all "
         +   "directions. To the north and to the east a road seems to "
         +   "lead through the plains.",SL));

    set_noshow_obvious(1);
    add_exit(ROOM + "plain16","south",0,3);
    add_exit(ROOM + "road1a","north",0,3);
    add_exit(ROOM + "plain9","west",0,3);
    add_exit(ROOM + "road2","east",0,3);

    set_auto_reset(TABLE);
    reset_room();
}



