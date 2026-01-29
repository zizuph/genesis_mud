#include "../default.h"
inherit CVAN_ROOM;

#define NO_OF_PEAR 6;

void reset_room();

int pear;

void
create_cvan_room()
{
    add_prop(ROOM_NO_TIME_DESC, 1);

    set_short("Courtyard");
    set_long("You find yourself in a large courtyard, surrounded by "+
      "hundreds of fragrant roses. To the west lies the imposing Trading "+
      "Company building while small paths lead to the north and south into "+
      "other areas of the courtyard. A large pear tree stands here.\n");

    add_item(({ "large pear tree", "pear tree", "large tree", "tree" }), "A "+
      "tall and slender tree with ripe pears hanging from its branches.\n");

    add_item(({ "pears", "pear" }), "They look ripe and ready to pick.\n");

    add_item(({ "branch", "branches" }), "Long and slender, the weight of "+
      "the pears has caused them to droop slightly, just enough for you to "+
      "be able to reach a few.\n");

    add_item(({ "roses" }), "Beautiful flowers that seem to thrive in the "+
      "harsh climate of Kalad. Their scent pervades this entire area.\n");

    add_item(({ "building" }), "The massive edifice towers dozens of feet "+
      "above you, a harsh contrast to the thriving plants all over this "+
      "courtyard.\n");

    add_item(({ "paths" }), "The paths, along with the rest of the courtyard "+
      "are paved in light grey cobbles, a few of which are cracked and "+
      "loose.\n");

    add_exit(CVAN + "company/s16", "north");
    add_exit(CVAN + "company/s32", "west");
    add_exit(CVAN + "company/s18", "south");

    reset_room();
}

void
reset_room()
{
    pear = NO_OF_PEAR;
}

int
do_pick(string str)
{
    if(!str || str != "pear")
    {
	notify_fail("You can't pick '" + str + "'.\n");
	return 0;
    }

    if(!pear)
    {
	write("There aren't any pears within your reach.\n");
	return 1;
    }
    write("You pick a pear from the tree.\n");
    say(QCTNAME(TP) + " picks a pear from the tree.\n");
    pear--;
    clone_object(OBJ + "pear")->move(TP);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_pick, "pick");
}
