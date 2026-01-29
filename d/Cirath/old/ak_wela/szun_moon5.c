inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("Szun Moon Boulevard");
    set_long("This spot is a big center of conflict.  The entrances to " +
             "the two major guilds of the city, the Alchemists and the " +
             "Astrologers, lie on opposite sides of the street.  The " +
             "towering height of the Astrologers hall seems to dwarf the " +
             "squat structure to the south, but rumor has it the depth of " +
             "the catacombs under the Alchemist hall is equal to any mine " +
             "in Genesis, and the cloud of smoke rising from the back of " +
             "the hall reaches almost to the clouds.  The boardwalk and " +
             "piers are a ways to the east, and immediately to the west is " +
             "the intersection with Qua Phing Avenue.\n");

    add_item(({ "smoke", "cloud" }), "This huge cloud of smoke turns the " +
             "entire sky hazy.  The Astrologers certainly can not enjoy " +
             "the effect it has on their observations.\n");

    add_exit(AK_WELA_DIR + "astr_entr", "north", "@@closed1", 2);
    add_exit(AK_WELA_DIR + "alch_entr", "south", "@@closed2", 2);
    add_exit(AK_WELA_DIR + "szun_moon4", "east", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon51", "west", 0, 2);
}


int
closed1()
{
    write("The guild is doing some very sensitive and delicate observations " +
          "and does not want to be disturbed.\n");
    return 1;
}


int
closed2()
{
    write("The guild is performing some very sensitive and delicate " +
          "experiments and does not want to be disturbed.\n");
    return 1;
}
