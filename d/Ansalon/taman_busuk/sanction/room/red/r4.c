#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("on a path running up the side of a volcano in Sanction");
    set_long("@@long_descr");

    add_item(({"wide path","path"}),
      "You stand on a wide path, created and maintained by numerous " +
      "slaves taken by the dragonarmies. The path leads up to the " +
      "large temple on the edge of the volcano.\n");
    add_item(({"volcano","active volcano","lords of doom"}),
      "Rising up before you is one of the Lords of Doom, " +
      "an active volcano that borders the city of Sanction.\n");
    add_item(({"encampment","large encampment","orderly encampment",
	"dragonarmy"}),
      "Down the path to your southwest, stationed at the base of the " +
      "volcano is an encampment of the Red Dragonarmy.\n");
    add_item(({"large temple","dragon head","dragons head","temple"}),
      "Rising up at the base of the volcano is a large temple, " +
      "created in the ghastly image of a dragons head.\n");

    add_exit(SRED + "r1","southwest",0);
    add_exit(SRED + "r5","northeast",0);
}


string
long_descr()
{
    return tod_short_descr()+ "You stand on a wide path that runs " +
    "up the side of an active volcano, one of the Lords of Doom "+
    "that borders on the city of Sanction. " +
    "To your southwest you notice a large orderly encampment of " +
    "the dragonarmy, while up the path to your northeast " +
    "rises a large temple, created in the image of a " +
    "ghastly dragons head.\n";
}
