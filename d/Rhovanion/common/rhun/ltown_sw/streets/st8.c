#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("You walk the streets of this large town in Rhun, near the"
	+" northwest edge of the great Sea of Rhun."
	+"  The road leads back to the southwest here, toward the center of"
	+" town, while a large boat house is just to the east.  You"
	+" may also step out onto a wooden pier by heading northeast.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st7","southwest",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/dock","northeast",0);
  add_exit(RHUN_DIR+"ltown_sw/bldgs/boat_house","east",0);

  add_item(({"pier","dock"}), "The ferry from across the bay"
	+" docks on the wooden pier just to the northeast.\n");
  add_item(({"house","boat house","boathouse"}), "The boat"
	+" house is apparently where the local shipwright"
	+" does his work.  You may enter it to the east.\n");
}
