#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <stdproperties.h>



public void  create_gondor();

public void
create_gondor()
{
  set_short("a small trail");
  set_long("Here the trail curves a bit, sliding deeper into the " +
	   "forest.  " +
           "The rustle of leaves creates a dry background of noise, " +
           "while the curious lack of any birdsong is slightly " +
           "unnerving.  " +
           "A clearing seems to grow to the east, while the trail " +
           "leads to both the north and south.  " +
	   "\n");

  add_item("ground","It is hard and covered with grass.\n");
  add_item("grass","The grass here is green and lush.\n");
  add_item("sky","The sky rises into infinity above you.\n");
  add_item("trail","The trail is simply an area of trampled grass, " +
	   "leading into the forest.\n");
  add_item(({"bird","birds"}),"There are no birds in this area.\n");
  add_item("clearing","The clearing is open to the east.\n");
  add_item("forest","The forest is thick with trees, surrounding " +
	   "you.\n");
  add_item(({"tree","trees"}),"The trees in the area are tall " +
	   "and strong.\n");

  add_exit(CAMP_ROOM_DIR + "trail1","north");
  add_exit(CAMP_ROOM_DIR + "trail3","east");
  add_exit(CAMP_ROOM_DIR + "trail4","south");


}

