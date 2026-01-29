#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("On a street alongside a river of lava");
    set_extra_long("Here you stand on the northern edge of a " +
      "teeming slum that has stopped expanding only because of the " +
      "extremely hot lava stream that runs past you to your north.");

    add_item(({"hot lava stream","lava stream","river",
	"river of molten rock","lava"}),
      "From the east a lava river runs past you to the west and " +
      "into the harbour. The heat from this river is staggering, " +
      "and you feel faint standing at this distance from it.\n");
    add_item("street","You stand upon a cobbled street that " +
      "runs alongside a river of lava. To your south is " +
      "the slums of the city. You believe you can enter " +
      "them from here.\n");

    add_exit(SCITY + "street9","west",0);
    add_exit(SCITY + "street14","east",0);
    add_invis_exit(SCITY + "slum6","south",0);

    slum_descriptions();
}
