#include "/d/Gondor/defs.h"
inherit "/d/Genesis/ship/deck";
inherit "/d/Gondor/common/lib/time.c";

#include <stdproperties.h>

void
create_deck()
{
    set_short("In the boat");
    set_long(BS("You are in a small rowing boat. A small part towards " +
      "the bow has been covered by a tarpaulin. If you are looking for cover " +
      "from wind or rain, you might try to crawl under it. There is only a single " +
      "pair of oars to move the boat.\n"));
    add_item("oars",BS("You notice a pair of oars fastened to the sides of the " +
      "boat, from where they are sticking out into the water. \n"));
    add_item(({"bow","tarp","tarpaulin"}), BS(
      "The bow of the ferry has been covered by a tarpaulin to " +
      "give some protection against wind and weather. To crawl under the " +
      "tarpaulin, just go towards the bow. \n"));
    add_item(({"anduin", "water"}), BS(
      "The Anduin is a wide band of water here, running to southwards " +
      "to its mouths in the Bay of Belfalas. \n"));
    add_item(({"boat", "ferry"}), BS(
        "This is a small rowing boat that is used as a ferry to cross the " +
        "Anduin. The boat has been painted dark so that it will be harder " +
        "to discover in the night. A small part of the boat towards the bow " +
        "has been covered by a tarpaulin to give some cover against rain and wind. " +
        "The boat cannot hold more than four persons, including the ferryman.\n"));
    add_item(({"oar","oars","pair of oars"}), BSN(
        "A pair of heavy wooden oars to move the rowing boat. But only " +
        "the ferryman should use them. "));
    add_exit(OSG_DIR + "ferry/tent", "fore", 0);
    set_deck_sound("The boat rocks with the waves.\n");
    set_bump_sound("The ferry lands on the shore.\n");
}

void
init()
{
    ::init();
    add_action("do_row","row");
    add_action("do_row","pull");
    add_action("check_time","time");
}

int
do_row(string str)
{
    object ferryman;

    if(query_verb() == "pull" &&
        (!str || (str != "oar" && str != "oars" && str != "pair of oars")))
    {
        NF("What ?\n");
        return 0;
    }
    if(ferryman = present("ferryman",TO))
    {
        ferryman->command("glare " + TP->query_real_name());
        ferryman->command("say Stop this! ");
        ferryman->command("say I'm the ferryman, and I'm the only one who's using the oars here!");
    }
    else if(present("ferryman",({find_object(OSG_DIR + "underbridge"),
        find_object(ITH_DIR + "osgiliath/underbridge")})))
    {
        write("You try to row, but you cannot move the rowing boat.\n");
        write("It is probably tied fast to the bank.\n");
    }
    else
        write("The oars are secured with a chain so you cannot use them.\n");
    return 1;
}
