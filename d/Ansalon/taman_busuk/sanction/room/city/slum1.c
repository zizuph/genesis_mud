#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;
object rough;

reset_sanction_room()
{
    if(!objectp(rough))
    {
	rough = clone_object(SNPC + "rough");
	rough->arm_me();
	rough->move(TO);
    }
}


void
create_sanction_room()
{
    set_short("Within one of the filthy slums of Sanction.\n"+
      "There are a few obvious exits");
    set_extra_long("Here you stand within one of the " +
      "slum areas of Sanction, consisting of densely packed, ramshackle " +
      "buildings that connect onto a maze of winding alleys " +
      "and walkways.");

    add_invis_exit(SCITY + "slum2","east",0);
    add_invis_exit(SCITY + "slum3","north",0);
    add_invis_exit(SCITY + "street1","south",0);

    add_item(({"walkways","exit","exits"}),"@@walkway_directions");
    slum_descriptions();
    reset_sanction_room();
}

string
walkway_directions()
{
    return "Walkways you can follow head off to your " +
    "north, east, and south.\n";
}

