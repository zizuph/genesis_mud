/* highpass */

#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("outside of caves");
    set_long("You are at a grassy path which goes generaly in a east-west "+
      "direction. To the west it goes back to those horrible "+
      "goblin caves. So you must keep to the east and hope that "+
      "there is some way out of these dangerous places.\n");

    add_item("path", "It comes from the goblin caves and winds eastward.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(CAVE_DIR + "t59", "west", 0 , 4);
    add_exit(MISTY_DIR+"p21", "southeast",    0,    4);

}

void
end_of_prisoner_quest()
{
    return;
}
