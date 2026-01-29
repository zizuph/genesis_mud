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
	merc->set_color("blue");
	merc->quiet_arm_me();
	merc->move(TO);
    }
}

void
create_sanction_room()
{
    set_short("A street in the southern parts of central Sanction");
    set_extra_long("Here you walk along a street on the southern " +
      "edge of a teeming slum consisting of filthy, closely-packed " +
      "buildings that create a maze of winding alleys.");

    add_item("street","You stand on a cobbled street in " +
      "the city of Sanction. To your north you believe you can " +
      "enter the slum district of this wretched city.\n");

    add_exit(SCITY + "street1","west",0);
    add_exit(SCITY + "street3","east",0);
    add_invis_exit(SCITY + "slum2","north",0);

    slum_descriptions();
    reset_sanction_room();
}

