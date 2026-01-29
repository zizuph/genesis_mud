#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("A street in the southern parts of central Sanction");
    set_extra_long("Here you walk along a street on the southern " +
      "edge of a teeming slum consisting of filthy, closely-packed " +
      "buildings that create a maze of winding alleys. To the southeast "+
      "there is some opening in the ground.");

    add_item("street","Here two cobbled streets meet " +
      "forming a crossroad.\n");

    add_exit(SCITY + "street2","west",0);
    add_exit(SCITY + "street6","north",0);
    add_exit(SCITY + "street4","east",0);
    add_exit(SCITY + "smith","southeast",0);
    add_exit("","south","@@no_go");

    slum_descriptions();
}

int
no_go()
{
    write("Due to a rather large lava surge from one " +
      "of the volcanoes, this street has been closed off and evacuated.\n");
    return 1;
}
