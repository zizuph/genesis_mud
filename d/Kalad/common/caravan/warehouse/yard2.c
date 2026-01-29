#include "../default.h"
inherit CVAN_ROOM;

#include <filter_funs.h>

#define KGUARD (NPC + "kguard")

void reset_room();

object ob1, ob2;

void
create_cvan_room()
{
    add_prop(ROOM_NO_TIME_DESC, 1);

    set_short("Warehouse Yard");
    set_long("This dry and dusty field is the front yard of the "+
      "warehouse that rises before you. There is no vegetation here, not "+
      "even weeds, there are however a multitude of wagon tracks leading "+
      "from Warehouse Lane in the north to the doors of the warehouse in the "+
      "south.\n");

    add_item(({ "warehouse" }), "A large rectangular structure that fills "+
      "your vision to the south, two large doors lead inside.\n");

    add_item(({ "large doors", "doors", "door" }), "The doors are closed, but "+
      "they don't seem to be locked or barred in any way.\n");

    add_item(({ "wagon tracks", "tracks", "track" }), "The indentations left "+
      "behind by the coming and going of wagons, probably laden with trading "+
      "goods. The marks criss-cross the entire yard.\n");

    add_item(({ "dry field", "dusty field", "field" }), "The front yard is "+
      "nothing but dirt, crossed almost completely by wagon tracks.\n");

    add_exit(CVAN + "warehouse/s1", "north");
    add_exit(CVAN + "warehouse/wh2", "south", "@@query_move");

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

int
query_move()
{
    object *ob;
    int pres, i;

    ob = FILTER_LIVE(all_inventory(this_object()));
    pres = 0;

    for (i = 0; i < sizeof(ob); i++)
    {
	if(ob[i]->query_name() == "Guard")
	{
	    pres = 1;
	}
    }

    if (pres == 1)
    {
	write("You are stopped by the guardsman of Kabal.\n");
	say("The guardsman of Kabal stops " + QTNAME(TP) + " from going into the warehouse.\n");
    }
    return pres;
}
