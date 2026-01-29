/* highpass */

#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("top of mountains");
    set_long("Finally you have reached the top of a highpass through Misty " +
      "Mountains. You are in the saddle between two high peaks. " + 
      "Strong cold winds are drawing heat from you.\n");

    add_item(({"peak","peaks"}), "The peaks are high and dark. What a " +
      "relief that you don't have to climb up anymore.\n");
    add_item("saddle", "It is a natural saddle between two high peaks.\n");
    add_item("wind", "You are getting cold from it. Better go down again.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p7", "west",    0,    10);
    add_exit(MISTY_DIR+"p9", "northeast",    0,    10);

}
