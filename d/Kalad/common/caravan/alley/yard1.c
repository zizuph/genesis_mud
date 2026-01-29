#include "../default.h"
inherit CVAN_ROOM;

#define KGUARD (NPC + "kguard")

void reset_room();

object ob1, ob2;

void
create_cvan_room()
{
    add_prop(ROOM_NO_TIME_DESC, 1);

    set_short("In front of the storage sheds");
    set_long("You are within a dirty, dirt-churned yard just in front of the "+
      "many rows of storage sheds lying to the east. There is a small guard post "+
      "here, apparently to keep intruders out.\n");

    add_item(({ "storage sheds", "storage shed", "sheds", "shed", "rows" }),
      "Uniform one-story structures that are lined up in a row just to "+
      "your east. Each individual unit is only ten feet wide, but since "+
      "there are over a dozen of the units, the sheds seem capable of "+
      "lots of storage space.\n");

    add_item(({ "small guard post", "small post", "guard post", "post" }), "A wooden "+
      "structure, just large enough to hold a few guards, that stands in "+
      "front of the storage sheds.\n");

    add_exit(CVAN + "alley/s1", "west");

    add_cmd_item(({ "south", "post" }), "enter", "@@enter");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(KGUARD);
	ob1->arm_me();
	ob1->move_living("M", TO);
    }

    if (!ob2)
    {
	ob2 = clone_object(KGUARD);
	ob2->arm_me();
	ob2->move_living("M", TO);
	ob1->team_join(ob2);
    }
}

string
enter()
{
    write("You walk into the small guard post.\n");
    set_dircmd("post");
    TP->move_living("into the small guard post", CVAN + "alley/gpost");
    return "The air doesn't seem quite as dusty here.\n";
}
