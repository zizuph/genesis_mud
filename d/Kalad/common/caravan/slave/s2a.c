#include "../default.h"
inherit CVAN_ROOM;

object slave1;
object slave2;
object slave3;
object slave4;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Cage");
    set_long("You've entered a large and filthy cage. The smell of dried "+
      "urine and undisposed fecal waste assails your nostrils. The straw "+
      "covering the dirt floor is dirty and is stained here and there with "+
      "dried blood, among other things.\n");

    add_item(({ "straw" }),
      "It is pale from extreme age, it seems to have been here for weeks, if "+
      "not months.\n");

    add_item(({ "blood" }),
      "It lies in dried stains on the floor, most likely originating from "+
      "the slaves kept here.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "slave/s2", "out");

    reset_room();
}

void
reset_room()
{
    seteuid(getuid(this_object()));
    if(!slave1)
    {
	slave1 = clone_object(NPC + "slave");
	slave1->move_living("M", this_object());
    }
    if(!slave2)
    {
	slave2 = clone_object(NPC + "slave");
	slave2->move_living("M", this_object());
    }
    if(!slave3)
    {
	slave3 = clone_object(NPC + "slave");
	slave3->move_living("M", this_object());
    }
    if(!slave4)
    {
	slave4 = clone_object(NPC + "slave");
	slave4->move_living("M", this_object());
    }
}

