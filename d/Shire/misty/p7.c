/* highpass */

#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("at slope");
    set_long("You are climbing the slope of Misty Mountains. Above you " + 
             "can see the top of it. There is also a big crack in the " + 
             "mountain to the south.\n");

    add_item("crack", "It is really big. Nearly like a small canyon. A " +
               "soft breeze blows from the crack, bringing the smell of " +
               "damp earth and something else you can't quite identify.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p6", "northwest",    0,    10);
    add_exit(MISTY_DIR+"p8", "east",    0,    10);
    add_exit(MISTY_DIR+"p19", "crack",    0,    5);

}
