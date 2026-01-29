#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;

object merc;

void
reset_sanction_room()
{
    if(!objectp(merc))
    {
	merc = clone_object(SNPC + "mercenary");
	merc->set_color("red");
	merc->quiet_arm_me();
	merc->move(TO);
    }
}

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
      "runs alongside a river of lava.\n");

    add_exit(SCITY + "street8","west",0);
    add_exit(SCITY + "street10","east",0);

    slum_descriptions();
    reset_sanction_room();
}
