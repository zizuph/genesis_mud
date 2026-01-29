inherit "/d/Gondor/common/room";
inherit "/d/Gondor/ithilien/forest/room_tells";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
    set_short("On the east bank of the river Anduin");
    set_long("You are standing on the east riverbank of the Anduin river. "+
        "Out in the river to the northwest are the ruins of central Osgiliath, "+
        "large stone buildings that are mostly crumbled into the river. To the "+
        "east is the edge of the southern Ithilien forest. You can walk along "+
        "the riverbank both north and south.\n");
    add_item("buildings",
        "One of the ruined buildings looks almost like a palace,\n"+
        "or a fortress of some sort.\n");

    add_exit(ITH_DIR+"forest/edge2","east",0);
    add_exit(ITH_DIR+"osgiliath/boatplace","south",0);
    add_exit(ITH_DIR+"osgiliath/bank1","north",0);

    add_orc_camp_tells();

}

blocked()
{
  if (!TP->query_wiz_level()) {
  write("That place is not yet finished.\nLord Elessar.\n");
  return 1;
  }
  return 0;
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
