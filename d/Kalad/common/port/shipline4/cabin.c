#include "../default.h"
inherit "/std/room";

void
create_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Captain's Cabin");
    set_long("You stand within the captain's chambers.\n"+
      "The interior of the cabin is meticulously clean, not a spot of "+
      "dirt can be spyed anywhere. A small wooden desk lies on one end of "+
      "room while a comfortable bed lies on the other end. A steel lantern "+
      "hangs on one of the walls. Two portholes allow a view of the "+
      "environment outside.\n");
    add_item(({"small wooden desk","small desk","wooden desk","desk"}),
      "A fancifully designed oak desk. Beautiful images of mermaids and dolphins "+
      "are carved all over it.\n");
    add_item(({"images","image"}),"Their silent beauty astounds you.\n");
    add_item(({"comfortable bed","bed"}),"A incredibly soft and alluring "+
      "sleeping place. It looks as if you could sleep through the worst of "+
      "hurricanes in its comforting softness.\n");
    add_item(({"steel lantern","lantern"}),"It provides a dim "+
      "illumination for the room.\n");
    add_item(({"walls","wall"}),"The sides of the cabins are plain and "+
      "unaddorned.\n");
    add_item(({"portholes","porthole"}),"Looking out you can see the "+
      "slightly turbulent waters of the ocean.\n");
    add_exit(PORT + "shipline4/upperdeck", "out");
    clone_object(PORT + "shipline4/mirror")->move(TO);
}

