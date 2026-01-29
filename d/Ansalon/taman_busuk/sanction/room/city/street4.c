#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("A street in the southern parts of central Sanction");
    set_extra_long("Here you walk along a street on the southern " +
      "edge of a teeming slum consisting of filthy, closely-packed " +
      "buildings that create a maze of winding alleys.");

    add_item("street","You are walking along a cobbled street " +
      "in the city of Sanction. To your north you think you can " +
      "enter the slum district of this wretched city.\n");

    add_exit(SCITY + "street3","west",0);
    add_exit(SCITY + "street5","east",0);
    add_invis_exit(SCITY + "slum4","north",0);

    slum_descriptions();
}

