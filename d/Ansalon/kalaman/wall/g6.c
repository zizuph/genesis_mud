#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object g1,g2,g3;

void
reset_kalaman_room()
{
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "sentry");
	g1->arm_me();
	g1->move(TO);
    }

    if(!objectp(g2))
    {
	g2 = clone_object(KNPC + "sentry");
	g2->arm_me();
	g2->move(TO);
    }

    if(!objectp(g3))
    {
	g3 = clone_object(KNPC + "militiaman");
	g3->arm_me();
	g3->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Up on the battlements above the western gate of Kalaman");
    add_item_wall();
    add_item(({"nightlund","river","vingaard river",
	"plains","plains of solamnia","west"}),
      "@@west_wall");
    add_item(({"western gate","gate"}),
      "You stand on the battlements above the western gate of Kalaman.\n");
    add_item(({"stairway","stone stairway"}),
      "A stone stairway leads down the the gate below.\n");
    add_item("road",
      "A road follows the Vingaard River away to the west into the eastern " +
      "lands of Solamnia.\n");

    add_exit(WALL + "n8","north",0);
    add_exit(WALL + "g5","southwest",0);
    add_exit(CITY + "guard3","down",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up on the battlements on the wall " +
    "above the western gate of Kalaman. " + season_battlements() + 
    "A stone stairway leads down to the gate below. " +
    west_desc();
}
