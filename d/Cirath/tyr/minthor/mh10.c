/* mh10.c: Minthor house room 10 */
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("slave", TZ_MINTHOR+"npc/q_slave.c", 1);
    bring_room_mob("master", TZ_MINTHOR+"npc/smaster.c", 1, 1);
}

void
create_room()
 {
  set_short("Path");
  set_long("The dusty path ends here. There is a medium sized warehouse "
	+"standing here with its door to your south. There is a large "
	+"wagon sitting here and there are slaves loading it up with "
	+"large crates and sacks. You can see the western edge of a "
	+"large mansion to your northeast, but it is unaccessible from "
	+"here.\n"); 
  add_item(({"smell"}),"It smells like moisture, maybe even free "
        +"standing water!\n");
  add_item("path","It is a wide, dusty, dirt path.\n");
  add_item("building","It is a fairly large building, and is probably "
	+"the personal warehouse of the Minthors.\n");
  add_item("wall","The wall is about 9 feet tall, and is made of "
        +"a dark grey granite. It would seem to protect decently well "
        +"against thugs and the like, as well as keep slaves in.\n");
  add_item("ruts","The ruts look to have been driven into the ground "
	+"by a large wheeled vehicle of some type.\n");
  add_item("grass","The grass is dried and coarse from its constant "
	+"exposure to the sun.\n");
  add_item(({"house","mansion"}),"The building is somewhere "
	+"around four  stories tall(about 50 feet), and is covered in statues and "
        +"other decorative items.\n");
  add_item("people","They look like people from a distance.\n");
  add_item(({"statues","items"}),"They are nicely crafted and must "
        +"be very expensive, probably worth their weight in water.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  add_exit(TZ_MINTHOR + "mh9","southeast", 0);
  reset_room();
}
