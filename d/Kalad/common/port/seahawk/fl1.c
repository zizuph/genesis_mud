#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Lower level");
    set_long("This is the lower level of the ship, just beneath the "+
      "upperdeck of the Seahawk. Located here would be the cabins and "+
      "offices of the crew. From the number of cobwebs covering every "+
      "corner, it doesn't appear as if anyone has used this area for "+
      "quite some time. The floor beneath is scuffed and worn.\n"+
      "A set of stairs leads up.\n");
    add_item(({"set of stairs","stairs"}),"A flight of wooden steps that "+
      "leads to the ship's upper deck.\n");
    add_item(({"cobwebs","cobweb"}),"Thin grey strands spun by a large "+
      "number of spiders. Their industrious work has resulted in most of "+
      "this room being blanketed by their filmy strands.\n");
    add_item(({"corner"}),"It is cluttered with many cobwebs.\n");
    add_item(({"floor"}),"A roughly cut round hole leads down into "+
      "the shadows.\n");
    add_item(({"roughly cut round hole","roughly cut hole","round hole","hole"}),
      "It appears to have been made via the sharp point of a cutlass.\n");
    add_item(({"shadows","shadow"}),"You can see nothing of what lies "+
      "below, you'll have to go down to find out anything more.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/boat6", "up", 0,2);
    add_exit(PORT + "seahawk/fl2", "west",0,1);
    add_exit(PORT + "seahawk/ba1", "down",0,2);
}

