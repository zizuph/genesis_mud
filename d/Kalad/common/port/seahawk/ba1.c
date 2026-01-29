#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Entrance to bottom level");
    set_long("This is the dark, dismal bottom level of the Seahawk. "+
      "A shadowy corridor heads west from here. Above you, in the ceiling, "+
      "a small hole has been roughly cut, providing an exit to the lower "+
      "level of the ship.\n");
    add_item(({"shadowy corridor","corridor"}),"A narrow shadow-filled "+
      "passageway that heads towards the ship's stern.\n");
    add_item(({"ceiling"}),"It looks as if it is ready to give way at "+
      "any moment. A roughly cut hole lies directly above you.\n");
    add_item(({"small hole","roughly cut hole","hole"}),"A dark gap "+
      "in the ceiling above.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/fl1", "up",0);
    add_exit(PORT + "seahawk/ba2", "west",0);
}

