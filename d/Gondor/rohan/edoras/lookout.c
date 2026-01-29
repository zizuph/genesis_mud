inherit "/d/Gondor/common/lib/sky";
#include <language.h>
#include <composite.h>
#include "/d/Gondor/elessar/lib/time.c"

object lguard;

create_room() {
    set_short("The lookout on top of the city gate of Edoras");
    extraline="You stand on the lookout point of the gates to Edoras. The "+
    "wind is playing in your hair. Over the south wall you see the houses of Edoras "+
    "on the slopes of the hill on which the town is built. Overlooking the "+
    "whole town is Meduseld, the palace of the King of Rohan, built on the "+
    "top of the hill of the town. The city is truly a beautiful sight now. " +
    "Looking out over the stonewall to the north, you can see endless lovely, " +
    "green grass stretching out as far as you can see to the north. You also " +
    "see the river Snowbourn, running from the valley of Harrowdale south of Edoras. " +
    "On the eastern bank of the river, a road runs towards the crossroads visible " +
    "to the north, passing through two groups of gravemounds. From this lookout post " +
    "you can see who passes on the road.";
    make_the_room();
    reset_room();
    add_exit("/d/Gondor/rohan/edoras/gat_stairs","down",0,0);
    seteuid(getuid(this_object()));
    add_item(({"road","gate"}),"@@on_road");
}

on_road()
{
    object *list, *lnames;
    int i, size;
    string desc;
    mixed room;

    seteuid(getuid(this_object()));
    "/d/Gondor/rohan/edoras/city_entr"->teledingska();
    if(!(room = find_object("/d/Gondor/rohan/edoras/city_entr"))) write("Not loaded!\n");
    desc = "The road in front of the gate is empty. ";
    lnames = ({ });
    list = all_inventory(room);

    for(i = 0; i < sizeof(list); i++)
    {
	if(living(list[i])) lnames += ({list[i]});
    }

    size = sizeof(lnames);
    if(size)
    {

	desc = "On the road in front of the gate you can see " + COMPOSITE_LIVE(lnames) + ". ";
    }

    "/d/Gondor/rohan/road/graves"->teledingska();
    if(!(room = find_object("/d/Gondor/rohan/road/graves"))) write("Not loaded!\n");

    lnames = ({ });
    list = all_inventory(room);

    for(i = 0; i < sizeof(list); i++)
    {
	if(living(list[i])) lnames += ({list[i]});
    }

    size = sizeof(lnames);
    if(size)
    {
	desc += "Further to the north, near the gravemounds, you can see " + COMPOSITE_LIVE(lnames) + " on the road.";
    }

    desc = break_string(desc + "\n",60);
    return desc;
}


reset_room()
{
    if(!lguard)
    {
	lguard = clone_object("/d/Gondor/rohan/edoras/npc/lguard");
	lguard->arm_me();
	lguard->move(this_object());
    }
}

enter_road(object who, object from)
{
    if(from->query_short() == "A broad, stonelaid road in Rohan")
    {
	if(lguard)
	{
	    lguard->command("shout Attention!");
	    lguard->command("shout I can see " + LANG_ADDART(who->query_nonmet_name()) + " coming towards the city gates!");
	}
    }
}
