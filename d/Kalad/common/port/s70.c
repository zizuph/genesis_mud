#include "default.h"
inherit PORT_ROOM;

#define PG PORT + "npc/pgmember"
object ob1;
object ob2;

void
create_port_room()
{
    set_short("Street by the Bay");
    set_long("This street runs aside the bay, travelling in an east-west "+
      "direction. The breaking of the surf just to the south sends up a "+
      "light shower of moisture that makes anything above a run rather "+
      "dangerous here, because of the increased chance of slipping and "+
      "falling. The cobblestones beneath you are covered with grime. A "+
      "long pier lies to the southeast, jutting into the bay while a large "+
      "building is to the north.\n");
    add_item(({"street"}),"A narrow road that hugs the coastline.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is kept "+
      "continually slick from the breaking of the surf. A layer of grime "+
      "blankets its surface.\n");
    add_item(({"layer","grime"}),"A number of rootless plants such as "+
      "moss and lichen have taken to growing on the cobblestones.\n");
    add_item(({"long pier","pier"}),"A large pier where a great many ships "+
      "might land.\n");
    add_item(({"bay"}),"Colored a deep azure, its beauty is marred only "+
      "by the pier in the southeast.\n");
    add_item(({"large building","building"}),"A large structure built "+
      "from hardwood planks. It looks like a warehouse.\n");
    add_exit(PORT + "s69", "west");
    add_exit(PORT + "s71", "east");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PG);
	ob1 -> move_living("xxx",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(PG);
	ob2 -> move_living("xxx",TO);
	ob1 -> team_join(ob2);
    }

}

