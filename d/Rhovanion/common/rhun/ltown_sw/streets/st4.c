#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("You walk the streets of this large town in Rhun, near the"
	+" northwest edge of the great Sea of Rhun."
	+"  The road leads back to the south here, toward the center of"
	+" town, while the mayor's house is just to the west.  You"
	+" may also approach the town wall by heading northeast.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st3","south",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/bywall4","northeast",0);
  add_exit(RHUN_DIR+"ltown_sw/bldgs/mayor_house","west",0);

  add_item(({"wall","town wall"}), "The town wall, standing just northeast"
	+" of here, is low and made of solidly-packed stones.  It"
	+" would not serve very useful for purposes of defense.\n");
  add_item(({"house","mayor house","mayor's house"}),
	"The mayoral estate stands just west of here.  It is far nicer than"
	+" the other homes in town; you guess that the mayor has much more"
	+" money in reserve than do its poverty-stricken citizens.\n");
}
