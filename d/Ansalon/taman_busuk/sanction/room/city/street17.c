#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/taman_busuk/sanction/ferrets/defs.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("On a street before an inn in the city of Sanction");
    set_extra_long("Here you stand in the eastern parts " +
      "of Sanction. To your west, nestled between houses " +
      "that were once probably owned by nobles or rich " +
      "merchants, is a two-story inn. A sign hangs above " +
      "its entrance. To your east is a run down shack and a "+
      "large river of lava.");

    add_item(({"inn","two-story inn"}),
      "To your west rises a two-story inn. While not " +
      "opulent, it is certainly a notch above any " +
      "other inn in Sanction.\n");

    add_item(({"entrance","sign"}),
      "A sign hangs above the entrance of the inn, reading: " +
      "'The Resting Blade Inn'.\n");

    add_item("houses",
      "To your west rise houses and similar structures " +
      "that were probably owned by the rich and " +
      "influential before the occupation of the city. " +
      "Now they simply stand out as being less rundown " +
      "than those buildings that stand in the expansive " +
      "slums of this city.\n");

    add_item(({"river of lava","lava","river"}),
      "To your east a river of lava flows past you " +
      "from one of the Lords of Doom to your south. " +
      "Even from this distance the heat is almost unbareable.\n");

    add_exit(SCITY + "street16","north",0);
    add_exit(SCITY + "street18","south",0);
    add_exit(SCITY + "inn","west","@@enter_inn");
    add_exit(ROOM_DIR + "ferret_breeder_room","east",0);
}

int
enter_inn()
{
    write("You step into 'The Resting Blade'.\n");
    return 0;
}
