/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE

int found = 2;
string occupant;

void
area_conquered(string newarmy, string oldarmy)
{
    int align = ARMYMASTER->army_alignment(newarmy);
    int previous = ARMYMASTER->army_alignment(oldarmy);

    if (align >= 0 && previous < 0)
        tell_room(TO,"A number of farmers arrive to rebuild the farm. " +
            "They work quickly and efficiently set up " +
            "the house again.\n");
    else if (align < 0 && previous >= 0)
        tell_room(TO,"A horde of hooded beings of the " + newarmy + 
            "arrive and burn the farm building. Nothing but debris " +
            "is left after they leave again.\n");
    occupant = newarmy;
}

void
create_road_room()
{
    set_short("@@my_short@@");
    set_long("@@my_long@@");

    add_item(({"ruins", "debris", "wood", "farm", "farmhouse", "walls", "cottage",
        "holes"}), "@@farm_desc@@");
    add_search(({"ruins", "farm", "debris", "wood", "farmhouse", "walls",
        "holes"}), 10, "farm_search", 1);

    if (LOAD_ERR(ROAD_OBJECT))
    {
        write("Bug! please report immediately.\n");
	return;
    }

    add_exit("", "west", "@@enter_map:" + ROAD_OBJECT + "|U@@",3,0);
    add_exit("", "east", "@@enter_map:" + ROAD_OBJECT + "|U@@",6,1);
    add_exit("", "south","@@enter_map:" + ROAD_OBJECT + "|U@@",6,1);
    add_exit("", "north","@@enter_map:" + ROAD_OBJECT + "|U@@",6,1);

    occupant = ARMYMASTER->army_in_area("Eastern Solamnian Plains");
}

void
reset_road_room()
{
    found = 2;
}


string
my_short()
{
    if (ARMYMASTER->army_alignment(occupant) < 0)
        return "ruins of a farmhouse on the plains of Solamnia";
    return "A farmhouse on the plains of Solamnia";
}

string
my_long()
{
    if (ARMYMASTER->army_alignment(occupant) < 0)
        return ("These are the ruins of a farmhouse. There is debris " +
            "everywhere, which consists mostly of charred wood and " +
            "splintered planks.\n");
    return ("You are standing outside a farm. The main building is a small " +
            "homely cottage, and a large barn lies next to it.\n");
}

string
farm_desc()
{
    if (ARMYMASTER->army_alignment(occupant) < 0)
        return ("There are planks of wood, a few stones, and a lot of " +
            "debris scattered about. This does not even remotely " +
            "resemble a farmhouse as it used to before the Dragonarmies " +
            "decided to wreak havoc here.\n");
    return ("The farmhouse is built from low quality wood, and has been " +
        "done rather crudely and quickly. There are still a number of " +
        "holes in the walls. Apart from that, you cannot see anything " +
        "unusual about it. A bit of debris is scattered around.\n");
}

string
farm_search(object searcher, string str)
{
    object ob;

    if (ARMYMASTER->army_alignment(occupant) < 0 && found > 0)
    {
	write("You search through the debris and find a few coins.\n");
	ob = clone_object("/std/coins");
	ob->set_coin_type(({"copper","copper","silver"})[random(3)]);
	ob->set_heap_size(random(15)+4);
	ob->move(TP,1);
	found--;
    }
    else
        write("You cannot find anything special.\n");
    return "";
}
