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
    set_long("You enter the cage to the smell of dried urine and "+
      "undisposed fecal waste. Dirty, lice-ridden straw thinly blankets the "+
      "dirt floor. Along with the other filth, dried blood stains lie here "+
      "and there.\n");

    add_item(({ "straw" }),
      "It looks like its been here for weeks. perhaps months.\n");

    add_item(({ "dirt floor", "floor" }),
      "The floor is just hard-packed earth and is covered with all manner "+
      "of filth.\n");

    add_item(({ "blood stains", "stains" }),
      "There are splotches of it across the floor of this cage, you deduce "+
      "that the blood belongs to the many slaves kept here.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "slave/s5", "out");

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
