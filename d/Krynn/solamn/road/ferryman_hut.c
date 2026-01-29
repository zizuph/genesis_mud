/* Aridor, 04/99 */

/* Navarre April 2008: This room never seemed to become non-flooded so I removed the block. */

#include <local.h>
#include <tasks.h>
#include <ss_types.h>

inherit ROOM_BASE

int keys_found = 0;

int not_when_flooded();

int
flooded()
{
    return (VKEEP)->query_flooded();
}

void
reset_road_room()
{
    if (!random(10))
        keys_found = 0;
}

void
create_road_room()
{
    set_short("On the shore of Vingaard River");
    set_long("@@my_long@@");

    add_item(({"river", "vingaard river", "water"}), "@@desc_river@@");
    add_item(({"hut", "small hut", "old hut", "entrance"}), "This small " +
        "hut near the river appears to be old, but fairly well made. A " +
        "single entrance has been built into the hut.\n");
    add_cmd_item(({"hut"}), "enter", "@@enter_hut@@");
    add_cmd_item(({"lock", "hut"}), "unlock",
        "You don't have a key that fits.\n");
    add_cmd_item(({"lock", "door", "hut"}), "open", "@@enter_hut@@");
    add_search(({"hut"}), 3, "search_hut", 1);
    add_item(({"shore", "pebbles"}), "@@exa_shore@@");
    add_item(({"trail"}), "This is a small trail leading from the hut " +
        "northeast along the shore of the river. " +
        "The trail is a bit overgrown, but still clearly visible.\n");
    add_item(({"clearing", "trees", "bushes"}), "The trees and bushes " +
        "here have been cleared to make plenty of room for a " +
        "small hut.\n");

    add_exit("/d/Krynn/solamn/eplains/rooms/eplain-4-21-V", "northeast");
    add_exit("sstore", "northwest", not_when_flooded, 0, 1);
    
    reset();
}

int
not_when_flooded()
{
    if (flooded() && !TP->query_prop("_i_found_ferryman_keys_"))
    {
	write("The river is blocking your way in this direction.\n");
	return 1;
    }
    write("With renewed determism you force your way across the river.\n");
    TP->add_fatigue(-50);
    return 0;
}

string
my_long()
{
    return ("The shore of the Vingaard River spreads out to the northeast " +
            "and southwest from here. A small trail leads from the " + 
            "hut in the middle of a clearing here along the shore to " +
	    "the northeast.\n");
}

string
desc_river()
{
    if (flooded())
        return "This is the mighty Vingaard River, flowing from the " +
            "southwest to the northeast. The river is to your " +
            "northwest, reaching almost to the small hut located here.\n";

    return "This is the Vingaard River, flowing from the southwest to " +
      "the northeast. The river is to your northwest, its " +
      "broad shore littered with pebbles that cover the color spectrum " +
      "from white to dark grey.\n";
}

string
exa_shore()
{
    if(flooded())
        return "The shore of the river is very narrow, due to the " +
            "flooded river. Most of the pebbles are under water.\n";

    return "The shore of the river is very broad now that the floods " +
        "have receeded. The pebbles are rounded and worn smooth from " +
        "the river.\n";
}

string
enter_hut()
{
    return "The entrance is firmly locked.\n";
}

string
search_hut(object searcher, string arg)
{
    int success = searcher->resolve_task(TASK_DIFFICULT,
					 ({ SS_AWARENESS, SS_AWARENESS, 
					      SKILL_MIN, TS_INT, TS_WIS,
					      SKILL_END }));
    if (!keys_found && success > 0)
    {
	clone_object(KEY)->move(searcher,1);
        searcher->add_prop("_i_found_ferryman_keys_", 1);
	keys_found = 1;
	return "Among the debris surrounding the hut, you find a key.\n";
    }
    else
      return "You don't find anything special.\n";
}

