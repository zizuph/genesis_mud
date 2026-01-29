#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/kalaman/seavillage/local.h"

inherit VILLAGE_ROAD;

void
reset_seavillage_room()
{
    return;
}

create_seavillage_room()
{
    set_short("Some ways off from the village of Braeme");
    set_long("@@long_descr");

    add_item("ocean","The ocean, even from here, looks rough.\n");
    add_item(({"village","braeme","Braeme"})," This is a small sea "+
      "side village that supplies far off Kalaman with fish.\n");
    add_item(({"building","buildings","double story building",
	"double story buildings"})," The buildings of Braeme are too far "+
      "away to make out any detail. One or two of the buildings "+
      "are taller than the others.\n");
    add_item(({"kalaman","city","Kalaman"}),"Kalaman lies "+
      "many leagues south of here.\n");

    add_exit(VILLAGEROOM + "road3","north",0);
    add_exit(VILLAGEROOM + "road1","south",0);

    reset_seavillage_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "To the north, you can make " +
    "out the buildings that constitute the village of Braeme. "+
    "Mostly single story structures, you can see a couple of double " +
    "story buildings rising above the rest. Beyond the village lies "+
    "the vast ocean that pounds against the coast of Nordmaar. "+
    "Far to the south lies the city of Kalaman. "+
    season_descr() + "\n";
}

