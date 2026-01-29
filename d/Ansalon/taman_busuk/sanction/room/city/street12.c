#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("On a street in the center of Sanction");
    set_extra_long("Here you stand in the center of " +
      "Sanction. On the western side of the street is " +
      "a teeming slum, while to the east rise houses " +
      "that once were owned by the nobles and rich merchants " +
      "before the dragonarmy occupation of the city. Between "+
      "two such buildings stands a building that has seen better times, the "+
      "Bank of Sanction.");

    add_item("street","A cobbled street in the city of Sanction.\n");
    add_item("houses",
      "To your east rise houses and similar structures " +
      "that were probably owned by the rich and " +
      "influential before the occupation of the city. " +
      "Now they simply stand out as being less rundown " +
      "than those buildings that stand in the expansive " +
      "slums of this city. Nestled between two such buildings "+
      "is a once prestigious building that has seen better " +
      "times, the Bank of Sanction.\n");
    add_item(({"bank","bank of sanction"}),
      "This once-prestigious building has, as with many other buildings "+
      "of Sanction, fallen into disrepair. Still, it seems it is still "+
      "in use.\n");


    add_exit(SCITY + "street13","north",0);
    add_exit(SCITY + "street11","south",0);
    add_exit(SCITY + "bank","east",0);

    slum_descriptions();
}
