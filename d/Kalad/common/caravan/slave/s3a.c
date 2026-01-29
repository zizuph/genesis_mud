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
      "undisposed fecal matter. Glancing around you note the straw spread "+
      "thinly over the dirt floor. Dried blood stains, among other things "+
      "litter the straw-covered floor.\n");

    add_item(({ "straw" }),
      "It looks like its been here for weeks, maybe even months.\n");

    add_item(({ "dirt floor", "floor" }),
      "A bare floor, except for a few patches of old straw here and there. "+
      "There are blood stains on it, along with other filth.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "slave/s3", "out");

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
