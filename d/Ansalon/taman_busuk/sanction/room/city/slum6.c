#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;

object sm, s1, s2;

reset_sanction_room()
{
    if(!objectp(sm))
    {
	sm = clone_object(SNPC + "slavemaster");
	sm->arm_me();
	sm->move(TO);

	s1 = clone_object(SNPC + "slave");
	s1->set_short(s1->query_adj() + " slave");
	s1->move(TO);
	s1->set_owner(sm);

	s2 = clone_object(SNPC + "slave");
	s2->set_short(s2->query_adj()+ " slave");
	s2->move(TO);
	s2->set_owner(sm);
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

    add_invis_exit(SCITY + "street10","north",0);
    add_invis_exit(SCITY + "slum5","west",0);

    add_item(({"walkways","exits"}),"@@walkway_directions");
    slum_descriptions();

    reset_sanction_room();
}

string
walkway_directions()
{
    return "Walkways you can follow head off to your " +
    "north and west.\n";
}

