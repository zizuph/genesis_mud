#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("On a street alongside a river of lava");
    set_extra_long("Here you stand to the north " +
      "of houses that once were owned by the nobles " +
      "and rich merchants before the city was occupied by " +
      "the Dragonarmies. Between two such houses a shop of " +
      "some kind has been constructed to your south. " +
      "A river of lava runs past you to your north.");

    add_item("houses",
      "To your south rise houses and similar structures " +
      "that were probably owned by the rich and " +
      "influential before the occupation of the city. " +
      "Now they simply stand out as being less rundown " +
      "than those buildings that stand in the expansive " +
      "slums of this city. Between two such buildings a " +
      "shop of some kind has been constructed.\n");

    add_item("shop",
      "To the south stands some kind of shop. You can't " +
      "tell much about it, as its sign is too dirty to read.\n");

    add_item("sign",
      "As this shop stands fairly close to a lava flow, " +
      "its sign has been charred so badly that no features " +
      "of it can be recognized.\n");

    add_item(({"river of lava","lava","river"}),
      "To your north a river of lava flows past " +
      "you from the east to the west towards " +
      "the harbour. Even from this distance the " +
      "heat is almost unbareable.\n");

    add_exit(SCITY + "street16","east",0);
    add_exit(SCITY + "arms_store","south",0);
    add_exit(SCITY + "street14","west",0);
}
