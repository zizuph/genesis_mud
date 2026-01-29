#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("on a road passing through an encampment of the Blue Dragonarmy");
    set_long("@@long_descr");

    add_item(({"encampment","tents"}),
      "Surrounding you is an encampment of the Blue Dragonarmy.\n");
    add_item("road","A road passes through the encampment, eventually " +
      "entering the Khalkhist Mountains to your east.\n");
    add_item(({"mountains","khalkhist mountains"}),
      "Surrounding the city of Sanction is the most desolate " +
      "area of the Khalkist Mountains, the Doom Range.\n");

    add_exit(SBLUE + "r3","east",0);
    add_exit(SBLUE + "r1","west",0);
    add_exit(SBLUE + "r4","north",0);
    add_exit(SBLUE + "r5","southeast",0);

}


string
long_descr()
{
    return tod_short_descr()+ "You stand on a " +
    "road passing through an encampment of the Blue " +
    "Dragonarmy. " +
    "To your north and southeast you can enter further " +
    "into the encampment, while to your west you can " +
    "head towards the city of Sanction. To your east " +
    "the road continues towards the mountains. " +
    season()+ "\n";
}
