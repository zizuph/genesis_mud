/* highpass */

#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("at slope");
    set_long("You are climbing the slope of Misty Mountains. You are " +
      "really tired and wonder how long you will have to climb " +
      "up til you reach the top. Or are you going down??? It " +
      "seems that you are so tired that you forget which way you " +
      "want to go.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit("p9", "northwest",    0,    10);
    add_exit("p11", "southeast",    0,    10);

}
