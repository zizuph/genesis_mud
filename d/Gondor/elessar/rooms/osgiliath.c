inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_room()
{
  set_short("In the Hall of Stars in Osgiliath");
  set_long("You are in a large hall with a domed ceiling. The ceiling is\n"+
    "covered with the image of the night sky, with all of the known stars.\n"+
    "By one wall is a stone throne, and by one side of the\n"+
    "throne is a large crystal globe - the Palantir!\n");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/elessar/rooms/weathertop","north",0);
  add_exit("/d/Gondor/rohan/isengard/orthanc/8/palantirroom","west",0);
  add_exit("/d/Gondor/minas/citadel/tower/palantirroom","up",0);
  add_exit("/d/Gondor/mordor/baraddur/throneroom","east",0);
}

