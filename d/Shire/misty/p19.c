/* highpass */

#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("in crack");
    set_long("You are in the big crack of the rock. There is some cave " + 
      "here too so if the weather is really bad you can stay there " +
      "for a while. If the weather is fine then you should go back to " +
      "the path.\n");

    add_item("crack", "It is really big. Nearly like a small canyon. A " +
      "soft breeze blows from the crack, bringing the smell of " +
      "damp earth and something else you can't quite identify.\n");
    add_item("cave", "It is dim and looks dangerous. Better stay out of it.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p7", "north",    0,    5);
    add_exit(MISTY_DIR+"c2", "in",    0,    4);

}
