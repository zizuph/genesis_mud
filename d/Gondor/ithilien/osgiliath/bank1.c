inherit "/d/Gondor/common/room";
inherit "/d/Gondor/ithilien/forest/room_tells";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
  set_short("On the east bank of the river Anduin");
  set_long("You are standing on the east riverbank of the Anduin river. "+
    "Out in the river to the northwest are the ruins of central Osgiliath, "+
    "large stone buildings that are mostly crumbled into the river. "+
    "The east part of Osgiliath was built on the east riverbank, and some "+
    "ruins are still left of it just north of here. To the "+
    "east is the edge of the southern Ithilien forest. You can walk along "+
    "the riverbank both north and south.\n");
  add_item(({"buildings", "ruins", }), 
      "One of the ruined buildings looks almost like a palace, or a "
    + "fortress of some sort.\n");
  add_item(({"river", "anduin", }), 
      "The river Anduin is flowing southward to its mouth in the Bay of "
    + "Belfalas. To the northwest you can see the ruins of Osgiliath on "
    + "an island in the middle of the stream and on both banks.\n");
  add_item(({"riverbank", "bank", }), 
      "You are on the eastern bank of the Anduin, just south of the ruins "
    + "of Osgiliath.\n");

  add_exit(ITH_DIR+"osgiliath/bank","north",0);
  add_exit(ITH_DIR+"osgiliath/bank2","south",0);

  add_orc_camp_tells();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
