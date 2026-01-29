#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"

inherit SANCOUTROOM;

object drac1;

void
reset_sanction_room()
{
    if(!objectp(drac1))
    {
	drac1 = clone_object(DRAGONARMY_NPC + "baaz");
	drac1->set_color("red");
	drac1->arm_draconian();
	drac1->move(TO);
    }
}

void
create_sanction_room()
{
    set_short("On a street in the center of Sanction");
    set_extra_long("Here you stand in the center of " +
      "Sanction. On the western side of the street is " +
      "a teeming slum, while to the east rise houses " +
      "that once were owned by the nobles and rich merchants " +
      "before the dragonarmy occupation of this city.");

    add_item("houses",
      "To your east rise houses and similar structures " +
      "that were probably owned by the rich and " +
      "influential before the occupation of the city. " +
      "Now they simply stand out as being less rundown " +
      "than those buildings that stand in the expansive " +
      "slums of this city.\n");
    add_item("street","A cobbled street in the city of Sanction.\n");

    add_exit(SCITY + "street14","north",0);
    add_exit(SCITY + "street12","south",0);

    slum_descriptions();
    reset_sanction_room();
}
