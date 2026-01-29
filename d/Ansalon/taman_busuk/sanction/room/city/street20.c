#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("On a street in the southern parts of Sanction");
    set_extra_long("Here you stand in an area " +
      "of the city that was largely residential, with " +
      "houses that once were probably owned by nobles " +
      "and rich merchants before the occupation of " +
      "the city by the dragonarmies, rising " +
      "predominantly to your north.");

    add_item("houses",
      "To your east rise houses and similar structures " +
      "that were probably owned by the rich and " +
      "influential before the occupation of the city. " +
      "Now they simply stand out as being less rundown " +
      "than those buildings that stand in the expansive " +
      "slums of this city.\n");
    add_item(({"street","streets"}),
      "You stand on a roughly cobbled street in the city " +
      "of Sanction.\n");

    add_exit(SCITY + "street11","west",0);
    add_exit(SCITY + "street19","east",0);

}
