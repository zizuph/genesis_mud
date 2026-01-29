/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom";

void
create_change_room()
{
    set_short("On the plains");
    set_long(BS("You are standing in the middle of nowhere on the plains of "
         +   "Solamnia, brownish, knee high grass stretching out in all "
         +   "directions. To the south a road seems to make its way through "
         +   "the grass.",SL));

    set_noshow_obvious(1);
    add_exit(ROOM + "road4","south",0,3);
    add_exit(ROOM + "plain7","north",0,3);
    add_exit(ROOM + "plain12","west",0,3);
    add_exit(ROOM + "plain14","east",0,3);

    set_auto_reset(TABLE);
    reset_room();
}



