#include "../default.h"
inherit CVAN_ROOM;

#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

#define KALAD_FOUND_LOT_EXIT "_kalad_found_lot_exit"

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 1);

    add_prop(ROOM_S_DARK_LONG, "A dark and dismal room.\n");

    add_prop(OBJ_S_SEARCH_FUN, "search_ceiling");

    set_short("An underground room");
    set_long("The air smells of death and decay.\n"+
      "This damp and dismal room is barely visible to your eyes. "+
      "Undescribable filth lies in reeking piles on the muddy ground. From "+
      "the ceiling above you catch the faint odor of fresh air. Looking "+
      "around the room you see the same filth spread all over the walls, which "+
      "are composed of mud. A dark passage leads east from here.\n");

    add_item(({ "filth", "piles", "refuse" }),
      "Its so disgusting it can't really be described, it lies in stinking "+
      "piles all over the room.\n");

    add_item(({ "ceiling", "above" }),
      "Composed of smelly mud, it hangs above you lurkingly, as though it were "+
      "alive.\n");

    add_item(({ "wall", "walls" }),
      "They seem to be made only of mud, which surprises and scares you "+
      "because there are no visible supports, leading you to believe that "+
      "the ceiling may come crashing down upon you at any moment. In the "+
      "southwestern area of the wall is a small hole.\n");

    add_item(({ "small hole", "hole" }), "It looks just large enough for a "+
      "full grown human to crawl through. The hole lies to the southwest.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur1", "east");
    add_exit(CVAN + "lot/s12", "up", "@@exit_up", 1, 1);

    add_cmd_item(({ "southwest", "hole" }), "enter", "@@enter");
    add_cmd_item("hole", "enter", "@@enter");
}

int
exit_up()
{
    object *witnesses;
    if (TP->query_prop(KALAD_FOUND_LOT_EXIT))
    {
        witnesses = filter(FILTER_CAN_SEE_IN_ROOM(AINV(E(TP)) - ({TP})),
                TP->check_seen);
        foreach (object witness: witnesses)
        {
            if (!witness->query_prop(KALAD_FOUND_LOT_EXIT))
            {
                witness->add_prop(KALAD_FOUND_LOT_EXIT, 1);
                witness->catch_msg(QCTNAME(TP) + 
                    " uses a tunnel hidden in the ceiling!\n");
            }
        }
        return 0;
    }
    write("There is no obvious exit up.\n");
    return 1;
}


string
enter()
{
    write("You squeeze yourself into the cramped hole.\n");
    set_dircmd("hole");
    TP->move_living("into the cramped hole", PORT + "shipline/cave6");
    return "You fall out of the hole and hit your head on some rocks!\n";
}

string
search_ceiling(object me, string arg)
{
    if(arg != "ceiling")
	    return "";

    if (TP->query_skill(SS_AWARENESS) < 30)
	    return "";

    TP->add_prop(KALAD_FOUND_LOT_EXIT, 1);
    return "You search carefully and discover a tunnel leading up!\n";
}
