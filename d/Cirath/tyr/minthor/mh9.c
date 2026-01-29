inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("Path");
  set_long("The dusty path continues westward, and here takes a turn "
	+"to the northwest, and also heads back east. To the northwest "
	+"there is a building of some sort, and there are some people "
	+"present also. To the south stands the wall that gives the "
	+"courtyard some privacy from people on the street. To the "
	+"north lies the large mansion which houses the people which "
	+"own this large area.\n");
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
  add_item(({"building","house","mansion"}),"The building is somewhere "
	+"around four  stories tall(about 50 feet), and is covered in statues and "
        +"other decorative items.\n");
  add_item("people","They look like people from a distance.\n");
  add_item(({"statues","items"}),"They are nicely crafted and must "
        +"be very expensive, probably worth their weight in water.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  add_exit(TZ_MINTHOR + "mh8","east", 0);
  add_exit(TZ_MINTHOR + "mh10","northwest", 0);
}

