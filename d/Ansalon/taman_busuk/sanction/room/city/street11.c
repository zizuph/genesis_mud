#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("On a street in the southern parts of Sanction");
    set_extra_long("Here you stand in the southern parts " +
      "of Sanction, to the southeast of a teeming slum and " +
      "to the southwest of houses that once were owned by the " +
      "nobles and rich merchants before the dragonarmy " +
      "occupation of this city. To your southeast you see what " +
      "looks like a marshalling yard.");

    add_item("street","A cobbled street in the city of Sanction.\n");

    add_item(({"yard","marshalling yard"}),
      "To your southeast is what looks like " +
      "a marshalling yard where soldiers of the " +
      "dragonarmies are gathered for deployment.\n");

    add_item("houses",
      "To your northeast rise houses and similar structures " +
      "that were probably owned by the rich and " +
      "influential before the occupation of the city. " +
      "Now they simply stand out as being less rundown " +
      "than those buildings that stand in the expansive " +
      "slums of this city.\n");

    add_exit(SCITY + "street12","north",0);
    add_exit(SCITY + "street5","west",0);
    add_exit(SCITY + "street20","east",0);
    add_exit(SCITY + "yard","southeast",0);

    slum_descriptions();
}

int
no_go()
{
    write("The marshalling yard is off limits " +
      "for the time being. Wannabe soldiers should come " +
      "back when the officers are recruiting.\n");
    return 1;
}
