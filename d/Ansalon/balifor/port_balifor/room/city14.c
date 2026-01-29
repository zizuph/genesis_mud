#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit BALIFOR_OUT;
object merc;

void
reset_balifor_room()
{
    if(!objectp(merc))
    {
	merc = clone_object(KNPC + "mercenary");
	merc->move(TO);
    }
}

create_balifor_room()
{
    set_short("Street in Southern City");
    set_long("@@long_descr");
    add_item(({"breakwater","Breakwater"}),"@@break_water");
    add_item(({"steppes","Steppes"}),"@@steppes");
    add_item(({"northwest","road","main road"}),
      "Looking northwest you see the main road that leads into " +
      "the center of Port Balifor join onto the road you are " +
      "standing on.\n");
    add_item("coast","To the west is the coastline of the " +
      "Bay of Balifor.\n");
    add_item("roads","Roads run east and northeast towards " +
      "the center of Balifor.\n");
    add_item("sign","@@read");
    add_cmd_item("sign","read","@@read");
    add_exit(BROOM + "city16","east",0);
    add_exit(BROOM + "city13","northeast",0);
    add_exit(BROOM + "city04","northwest",0);
    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + " You stand on the south side of town. Looking "+
    "northwest you see the road lead to the main road in Balifor, that "+
    "run along the coast. To the east and northeast, roads travel "+
    "deeper into the city, towards the business section. "+
    season_descr()+"\n";
}
