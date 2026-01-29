inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
 
        set_short("Outside tower");
        set_long("   You are standing in some gardens to the "+
		 "east of a pure white marble tower. They are "+
                 "exquisitely kept and beautifully grown.  There is "+
                 "some wisteria growing lavishly to the west and you "+
                 "think you spy a small path trailing away under it.\n\n");

        add_exit(VILLAGE_DIR + "garden2", "northwest",);
        add_exit(VILLAGE_DIR + "garden1", "southwest",);

        add_item(({"tower"}),"The tower is solidly built from white marble. "+
                  "You notice no cracks in its gleaming surface "+
                  "as if it were built whole from a huge chunk of marble.\n");
        add_item(({"gardens", "patterns"}),"The gardens are arranged with "+
                   "loving care into lovely patterns of beautiful flowers by "+
                   "the tower owner's gardener.\n");
        add_item(({"flowers"}), "The flowers are a mixture of all colours "+
                   "arranged in a nice pattern.\n");
        add_item(({"path"}),"A stone walkway that seems to be "+
                  "leading north under the wisteria.\n");
        add_item(({"wisteria"}),"It is a profusion of low-hanging vines blanketed by"+
                   " tiny, fragrant, lavender flowers.  Perhaps you could "+
                   "duck under it?\n");
        add_prop(ROOM_I_INSIDE, 0);
/* There is (was?) some bug with moving, trying to correct it. SN */
        find_object(VILLAGE_DIR + "g1")->reset_room();
}
 
void
init()
{
    ::init();
    add_action("duck", "duck");
}
 
int
duck(string arg)
{
    notify_fail("Duck what?\n");
    if (arg != "under wisteria")
	return 0;
    set_dircmd(arg);
    this_player()->move_living("under wisteria",VILLAGE_DIR + "g1");
    return 1;
}
