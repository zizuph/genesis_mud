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
    set_short("Before a rowdy tavern within one of the " +
      "filthy slums of Sanction.\nThere are a number of " +
      "obvious exits");
    set_extra_long("Here you stand within one of the " +
      "slum areas of Sanction, consisting of densely packed, ramshackle " +
      "buildings that connect onto a maze of winding alleys " +
      "and walkways. To your east stands a tavern, filthy " +
      "with ash and soot, yet as busy as any you have seen " +
      "in the lands. Here the rowdy soldiers of the dragonarmy " +
      "come here to get drunk and pick fights, so be careful " +
      "if you decide to make your way in there.");

    add_item(({"rowdy tavern","tavern","filthy tavern"}),
      "To your east stands a busy tavern, quite a common " +
      "sight in the slums of Sanction. Its walls and roof " +
      "are covered with soot and ash respectively due to " +
      "the common eruptions of the Lords of Doom.\n");
    add_item(({"soldiers","rowdy soldiers"}),
      "Drunken soldiers of the dragonarmies fill the slums and " +
      "taverns, spending their time drinking and picking " +
      "fights with locals or each other.\n");

    add_invis_exit(SCITY + "tavern","east","@@enter_tavern");
    add_invis_exit(SCITY + "street4","south",0);
    add_invis_exit(SCITY + "street6","west",0);
    add_invis_exit(SCITY + "slum5","north",0);

    add_item(({"walkways","exits","exit"}),"@@walkway_directions");
    slum_descriptions();
    reset_sanction_room();
}

int
enter_tavern()
{
    write("\nYou step into the filthy tavern...\n\n");
    return 0;
}

string
walkway_directions()
{
    return "Walkways you can follow head off to your " +
    "north, west, south, and east into the tavern.\n";
}

