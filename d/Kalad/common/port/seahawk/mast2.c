#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("You are clinging to the mast of the ship");
    set_long("You are clinging to the main mast of the ship. From this "+
      "vantage point the surrounding docks and bay are clearly visible. "+
      "Just above you is the crow's nest.\n");
    add_item(({"main mast","mast"}),"The great central pole at the "+
      "center of the Seahawk, upon which the sails are attached.\n");
    add_item(({"sails","sail"}),"Great white billowing sails that lie "+
      "just below you.\n");
    add_item(({"docks","dock"}),"Looking below, the large system of "+
      "piers looks significantly smaller, though still quite impressive.\n");
    add_item(({"bay"}),"The glittering waters of the bay sparkle with "+
      "a crystal blue clarity.\n");
    add_item(({"crow's nest","nest"}),"Gazing up, you can make out a "+
      "small hole at the bottom of the platform, allowing passage up "+
      "onto the nest.\n");

    add_prop(ROOM_NO_TIME_DESC, 1);

    add_exit(PORT + "seahawk/nest",  "up", 0,2);
    add_exit(PORT + "seahawk/mast1",  "down", 0,1);
}

