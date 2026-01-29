#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Gates of Flotsam");
    set_long("@@long_descr");

    add_item(({"iron gates","gates","gate"}),"Double iron " +
      "gates rise before you, now standing open, allowing passage " +
      "out of Flotsam.\n");
    add_item("guardrooms","Two stone guardrooms stand to your " +
      "north and south, where soldiers of the Dragonarmies ordered " +
      "to guard the main gates rest. \n");

    add_exit(FROOM + "guard01","north","@@guard",0);
    add_exit("/d/Ansalon/balifor/flotsam_forest/coastline/road1",
      "east","@@no_exit");
    add_exit(FROOM + "guard02","south","@@guard",0);
    add_exit(FROOM + "street20","west",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "You stand at the grim " +
    "iron gates of Flotsam. To your north and south are guardrooms, " +
    "while to your west lies the centre of the town. To your east are " +
    "the gates, which are at the moment open. " + season_descr() +
    "\n";
}

int
guard()
{
    write("You enter the guardroom... \n");
    return 0;
}

int
no_exit()
{
    write("You pass out the open gates of Flotsam.\n");
    return 0;
}
