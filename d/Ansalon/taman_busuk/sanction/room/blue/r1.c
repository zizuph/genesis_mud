#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("on a road passing through an encampment of the Blue Dragonarmy");
    set_long("@@long_descr");

    add_item(({"bridge","stone bridge"}),
      "To your west a bridge crosses over a lava stream into the city of " +
      "Sanction.\n");
    add_item(({"lava","lava stream"}),
      "A lava stream flows slowly under the bridge. The heat " +
      "from it hits you like a physical blow.\n");
    add_item(({"encampment","tents"}),
      "Surrounding you is an encampment of the Blue Dragonarmy.\n");
    add_item("road","A road passes through the encampment, eventually " +
      "entering the Khalkhist Mountains to your east.\n");
    add_item(({"mountains","khalkhist mountains"}),
      "Surrounding the city of Sanction is the most desolate " +
      "area of the Khalkist Mountains, the Doom Range.\n");

    add_exit(SBLUE + "tent1","north",0);
    add_exit(SBLUE + "tent2","southeast",0);
    add_exit(SBLUE + "bridge","west",0);
    add_exit(SBLUE + "r2","east",0);
}


string
long_descr()
{
    return tod_short_descr()+ "You stand on a " +
    "road passing through an encampment of the Blue " +
    "Dragonarmy. " +
    "To your west a bridge passes over a lava stream and " +
    "into the city of Sanction. To your north and southeast " +
    "are the entrances to tents while to your east the road " +
    "continues. " +season()+ "\n";
}
