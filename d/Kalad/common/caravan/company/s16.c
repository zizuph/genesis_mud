#include "../default.h"
inherit CVAN_ROOM;

object ob1;
object ob2;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_NO_TIME_DESC, 1);

    set_short("Courtyard");
    set_long("You find yourself in a large courtyard, surrounded by "+
      "hundreds of fragrant roses. To the west lies the imposing Trading "+
      "Company building while small paths lead to the north and south into "+
      "other areas of the courtyard.\n");

    add_item(({ "roses" }), "Beautiful flowers that seem to thrive in the "+
      "harsh climate of Kalad. Their scent pervades this entire area.\n");

    add_item(({ "building" }), "The massive edifice towers dozens of feet "+
      "above you, a harsh contrast to the thriving plants all over this "+
      "courtyard.\n");

    add_item(({ "paths" }), "The paths, along with the rest of the courtyard "+
      "are paved in light grey cobbles, a few of which are cracked and "+
      "loose.\n");

    add_exit(CVAN + "company/s15", "north");
    add_exit(CVAN + "company/s31", "west");
    add_exit(CVAN + "company/s17", "south");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "tcfmaster");
	ob1->move(TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(NPC + "tcfalcon");
	ob2->move(TO);
	ob2->team_join(ob1);
    }
}

void
init()
{
    ::init();
    write("The smell of roses is in the air.\n");
}
