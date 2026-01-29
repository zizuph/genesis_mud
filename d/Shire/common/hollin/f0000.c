#include "forest.h"

create_forest()
{
    set_short("A gloomy forest");
    set_long(
	"You have entered a dark and gloomy forest in Eregion, "+
	"or Hollin as men usually like to call it. Large oak-trees "+
	"prevent light from reaching the ground, thereby making "+
	"it impossible for any plants to grow down here except "+
	"mushrooms and moss. Strangely enough, you can see "+
	"that it is brighter in the southwest, as if someone has "+
	"made a large trail going through the forest. The forest "+
	"extends in all directions, though in the east you surely "+
    "can hear some kind of trickling water.\n");

    ADD_EXA("trail", "Well, surely you'd gain a better view by going there..");
    ADD_EXA("sound,water",
	    "I'll eat my hat if that is not the sound of a river!");
    ADD_EXA("river",
	    "It is in the east, well it must be.. Just try to go east.");
    ADD_EXA("light",
	    "What light? Try to look at the sky.");
   "/d/Shire/common/hollin/trolls_lair"->teleledningsanka();

    add_exit("/d/Shire/common/gondorlink", "southwest");
    add_exit("/d/Shire/common/greenway/gw2", "west");
    NORTH("f0001");
    NORTHEAST("f0101");
    EAST("f0100");
/*
    SOUTHEAST("f01-1");
    SOUTH("f00-1");
*/
}

/* Commented out by Dunstable, we don't need this log anymore.
enter_inv(object to, from)
{
    ::enter_inv(to, from);
    if (!living(to))
	return;
    if (to->query_npc())
	return;

    log_file("ENTER_HOLLIN",
	ctime(time()) + ":" + to->query_name() + "\n");
}
*/
