#include "local.h"
inherit TDIR+"eplain_base";

int found = 2;
string occupant = "Free People";

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

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("@@my_short@@");
    set_long("@@my_long@@");

    add_item(({"ruins", "debris", "wood", "farm", "farmhouse", "walls", "cottage",
        "holes"}), "@@farm_desc@@");
    add_search(({"ruins", "farm", "debris", "wood", "farmhouse", "walls",
        "holes"}), 10, "farm_search", 1);

    add_std_exits();

    if (TO->query_area_name())
	occupant = ARMYMASTER->army_in_area(TO->query_area_name());

    herbs = HERB_MASTER->query_herbs( ({ "garden", }) );
}

void
reset_eplains_room()
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
        ob = clone_object("/std/coins");
	ob->set_coin_type(({"copper","copper","silver"})[random(3)]);
	ob->set_heap_size(random(15) + 4);
	ob->move(TP);
	found--;
        
        return "You search through the debris and find a few coins.\n";
    }
    else
        return "You cant find anything special.\n";
    return "";
}
