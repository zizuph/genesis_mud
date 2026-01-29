/* highpass */

#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("at slope");
    set_long("You are climbing the slope of the Misty Mountains. Above you " + 
      "can see the top of it.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p8", "southwest",    0,    10);
    add_exit(MISTY_DIR+"p10", "southeast",    0,    10);

}
