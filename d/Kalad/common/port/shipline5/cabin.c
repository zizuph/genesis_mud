#include "../default.h"
inherit "/std/room";

void
create_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Cabin");
    set_long("You stand within the upper deck's cabin.\n"+
      "This warm, dry and even cozy room surprises you because directly "+
      "across from you is a blazing fire! The roaring flame illuminates "+
      "the interior of the cabin quite well, showing the comfortable seats "+
      "arrayed around the room. A single desk and couch lie in one corner "+
      "of the room, opposite the fire.\n");
    add_item(({"cabin","room"}),"Its what you are in. Also, you notice "+
      "that the flame is carefully controlled, having been placed inside "+
      "a brick fireplace of sorts, with some exit through the ceiling.\n");
    add_item(({"brick fireplace","fireplace","ceiling"}),"The fire is "+
      "contained in a brick structure which leads out through the top of this "+
      "cabin.\n");
    add_item(({"comfortable seats","seats","seat"}),"Well-rounded plush "+
      "chairs that you could easily fall asleep in.\n");
    add_item(({"desk"}),"A richly finished oak desk, its fanciful designs "+
      "are quite attractive.\n");
    add_item(({"designs","design"}),"Intricately carved images of "+
      "mermen and mermaids sprawl across the desk.\n");
    add_item(({"couch"}),"A nice couch approximately seven feet across "+
      "that is covered with wonderfully plush cushions.\n");
    add_item(({"wonderfully plush cushions","plush cushions","cushions","cushion"}),
      "Square-shaped and covered with silk, they are extremely soft to "+
      "the touch.\n");
    add_exit(PORT + "shipline5/upperdeck", "out");
    clone_object(PORT + "shipline5/fire")->move(TO);
}

