/* highpass */

#include "local.h";

inherit SHIRE_ROOM;

void
create_shire_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("at foot of mountains");
    set_long("You are at the foot of Misty Mountains. To the west you " + 
      "see the valley with paths going towards the lowlands " + 
      "of Rhudaur and to northeast it climbs up a steep slope.\n");


    add_item("valley", "You see a fair green valley.\n");
    add_item("mountains", "The mountains look somehow dark. Maybe there is " +
      "danger brooding there.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p1", "west",    0,    3);
    add_exit(MISTY_DIR+"p3", "northeast",    0,    4);

}
