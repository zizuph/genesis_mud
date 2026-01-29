#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;
object          officer;
object          merc;
object          merc2;
object          merc3;

void
reset_balifor_room()
{
    if (!objectp(officer)) {
	officer = clone_object(BNPC + "serion");
	officer->move(TO);
    }
    if (!objectp(merc)) {
	merc = clone_object(KNPC + "mercenary");
	merc->move(TO);
    }
    if (!objectp(merc2)) {
	merc2 = clone_object(KNPC + "mercenary");
	merc2->move(TO);
    }
    if (!objectp(merc3)) {
	merc3 = clone_object(KNPC + "mercenary");
	merc3->move(TO);
    }
}

create_balifor_room()
{
    set_short("Northeast part of Town");
    set_long("@@long_descr");
    add_item(({"breakwater", "Breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"barracks","entrance"}),
      "The entrance to the barracks is to the north, " +
      "but it is closed off for the moment, and there doesn't " +
      "seem to be any way to get in.\n");
    add_item("town","@@long_descr");
    add_item(({"roads","road"}),
      "The road here leads southeast and southwest.\n");
    add_exit(BROOM + "city08", "southwest", 0);
    add_exit(BROOM + "city20", "southeast", 0);
    add_exit(BROOM + "barrack01","north","@@no_go");
    reset_balifor_room();
}

int
no_go()
{
    write("The doors to the barracks are closed for the time " +
      "being.\n");
    return 1;
}

string
long_descr()
{
    return tod_descr1() + " You stand in the northern part of town, in " +
    "front of the barracks of the dragonarmy. Roads lead southeast and " +
    "southwest from here into town. This part of the city is much less " +
    "crowded than the rest, the citizens tend to avoid this part of " +
    "town it seems. The entrance to the barracks lies to the north, " +
    "but why would you want to go in there? " + season_descr() + "\n";
}
