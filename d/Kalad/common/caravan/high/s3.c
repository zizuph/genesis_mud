#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("High street");
    set_long("You are travelling along High Street, a wide concourse that "+
      "cuts through the center of Kabal. The road continues north and south "+
      "from here and is bordered on the west by a large group of trees, a "+
      "park in the neighboring Upper Class district. To the east you can "+
      "see several buildings. A large intersection lies to the south.\n");

    add_item(({ "high street", "concourse", "road" }),
      "The street is paved in slate-grey cobblestones that appear slightly "+
      "worn and cracked, though in relatively good shape for such a heavily "+
      "travelled road.\n");

    add_item(({ "trees", "park" }),
      "As you examine the woods, you get the impression that thieves and other "+
      "brigands would find safe haven within its shadowy interior.\n");

    add_item(({ "buildings" }),
      "Tidy-looking wooden homes that line High Street along the eastern "+
      "side. This area looks to be middle-class, where the residents have "+
      "enough money to not go hungry, but not enough to live in comfort. "+
      "One such house lies directly to the east.\n");

    add_item(({ "house" }), "A comfortable-looking home, probably the residence "+
      "of some middle class family.\n");

    add_exit(CVAN + "high/s2", "north");
    add_exit(CVAN + "high_serv", "south");

    add_cmd_item(({ "east", "house" }), "enter", "@@enter");
    add_cmd_item("house", "enter", "@@enter");
}

string
enter()
{
    write("You open the door to the house.\n");
    set_dircmd("house");
    TP->move_living("into the house", CVAN + "high/house");
    return "You close the door behind you.\n";
}
