/* highpass */

#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("at slope");
    set_long("You are at the slope of Misty Mountains. To the west you " + 
      "can see only huge peaks. The path goes through the saddle " +
      "high up.\n");

    add_item("peak", "The peaks are high and dark.\n");
    add_item("peaks", "The peaks are high and dark.\n");
    add_item("saddle", "It is a natural saddle between two high peaks.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p11", "southwest",    0,    10);
    add_exit(MISTY_DIR+"p13", "northeast",    0,    8);

}
