#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;

object gob;

void
reset_sanction_room()
{
    if(!objectp(gob))
    {
	gob = clone_object(SNPC + "goblin");
	gob->set_color("red");
	gob->quiet_arm_me();
	gob->move(TO);
    }
}

void
create_sanction_room()
{
    set_short("A street passing through the center of Sanction");
    set_extra_long("Here you walk along a street that cuts through the " +
      "center of a teeming slum consisting of filthy, closely-packed " +
      "buildings that create a maze of winding alleys.");

    add_item("street","You stand on a cobbled street that " +
      "runs through the middle of the slums of Sanction. You " +
      "see entrances to this district on either side of you.\n");

    add_exit(SCITY + "street3","south",0);
    add_exit(SCITY + "street7","north",0);
    add_invis_exit(SCITY+ "slum2","west",0);
    add_invis_exit(SCITY + "slum4","east",0);

    slum_descriptions();
    reset_sanction_room();
}

