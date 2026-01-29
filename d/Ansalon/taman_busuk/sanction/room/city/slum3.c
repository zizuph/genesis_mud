#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Krynn/common/clock/clock.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("Before a brothel within one of the filthy " +
      "slums of Sanction.\nThere are a number of obvious exits");
    set_extra_long("Here you stand within one of the " +
      "slum areas of Sanction, consisting of densely packed, ramshackle " +
      "buildings that connect onto a maze of winding alleys " +
      "and walkways. To your east rises a two-story building with " +
      "a sign of a naked sylph on it, marking it as one of the " +
      "many brothels of Sanction.");

    add_item(({"two-story building","building","brothel"}),
      "To your east rises one of the many brothels of Sanction. " +
      "On the second floor of the building is a balcony, where " +
      "the ladies of the night try and persuade customers to " +
      "enter their shady premise.\n");
    add_item(({"sign","naked sylph","sylph"}),
      "The sign of the naked sylph marks this place " +
      "as one of the many brothels of Sanction.\n");
    add_item("balcony","On the second floor of the brothel " +
      "is a balcony where the ladies of the night try and " +
      "seduce people into this shady establishment. You cannot " +
      "seem to find any way to climb up to it.\n");

    add_invis_exit(SCITY + "slum1","south",0);
    add_invis_exit(SCITY + "brothel","east","@@enter_brothel");

    add_item(({"walkways","exits"}),"@@walkway_directions");
    slum_descriptions();
}

int
enter_brothel()
{
    int *the_time = GET_TIME;

    if(the_time[HOUR] >= 6 && the_time[HOUR] <= 17)
    {
	write("The brothel is closed during the daylight hours..."+
	  "come back when the sun falls.\n");
	return 1;
    }

    write("\nYou step into the shadowy brothel...\n\n");
    return 0;
}


string
walkway_directions()
{
    return "Walkways you can follow head off to your " +
    "south and to your east into a local brothel.\n";
}

