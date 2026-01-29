#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
   set_short("southwestern tower");
   set_long("This southwestern tower is strange. There seems to have been "+
         "a cave in here.  The stairs that used to lead up are now just a "+
         "a pile of rubble. The rubble appears to be unpassable. The only "+
         "apparent exit is northwest.\n");
   
   add_item("rubble","The pile of rubble compleatly blocks the stairs leading "+
            "up.\n");
   
   add_exit(CASTLE_DIR + "3k10","northwest",);
}
