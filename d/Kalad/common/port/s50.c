#include "default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    set_short("Narrow Street");
    set_long("You are on a narrow street sandwiched between two "+
      "extremely large buildings that lie to the north and south. The "+
      "cobblestones underfoot are moist and covered with grime. The "+
      "roadway continues west and east. There seems to be some sort of major "+
      "intersection in the latter direction.\n");
    add_item(({"narrow street","street","roadway"}),"A small road that "+
      "winds its way through the Port District.\n");
    add_item(({"two extremely large buildings","two buildings","two large buildings","large buildings","buildings","building"}),
      "Enormous structures made out of hardwood planks. From the size of the "+
      "buildings you assume they must be warehouses of some sort.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is weathered "+
      "and as a result is cracked in many places. A thin film of moisture "+
      "blankets the surface, allowing small plants to grow upon it.\n");
    add_item(({"grime","small plants","plants","small plant","plant"}),
      "Moss, lichen and other rootless plants have taken to growing on the "+
      "cobblestones of the street.\n");
    add_item(({"major intersection","intersection"}),"A large central "+
      "area in the east, where there seems to be an abundant amount of "+
      "activity.\n");
    add_exit(PORT + "s49", "west");
    add_exit(PORT + "s51", "east");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/kid");
	ob1 -> move_living("xxx", TO);
    }

}

