/* Ashlar, 18 May 97 */
/* This room is intended to be an entrance to the sewers. */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include <macros.h>

#define FOUND_TRAPDOOR          "_neraka_blue_ware1_found_trapdoor"
#define ROOM_BELOW_TRAPDOOR     NSEWER + "s2"

inherit OUTER_IN;

void
create_neraka_room()
{
	set_short("inside a warehouse");
    set_long("This building seems to have served as a warehouse until " +
        "recently. There are still patches in the dust where crates have " +
        "been, but the warehouse is empty now.\n");    

    add_item_inside();
    remove_item("floor");
    add_item("floor","The floor is dusty, except in some places, " +
        "which seems to have been occupied by boxes or crates until just " +
        "recently.\n");
    add_item(({"dust","patches","patches in the dust"}),
        "There are some rectangular patches on the floor, which are free " +
        "from dust. There were probably boxes or crates stored in here " +
        "before. @@show_trapdoor@@\n");

    add_item(({"floorboards","boards","wooden boards"}),
        "Old wooden boards make up the floor of this warehouse.\n");

    add_search(({"floor","dust","patches","patches in the dust"}),
        10, "One large dust-free patch looks odd in some way you cannot " +
            "really define.\n");

    add_item(({"large patch","large dust-free patch"}),
        "The floorboards there look out of place.\n");

    add_search(({"large patch","large dust-free patch"}),
        2, "find_trapdoor", 1);

    add_item("trapdoor","@@exa_trapdoor");

    add_exit(NOUTER+"blue/b13","northeast");
}

int
trapdoor(string arg)
{
    object other_room;

	/* Try to eliminate the player getting hints from wierd syntax */
	if ((query_verb() == "enter") || (query_verb() == "open"))
    {
    	if (!arg || (arg != "trapdoor") || !TP->query_prop(FOUND_TRAPDOOR))
        {
            return 0;
        }
    }
    else
    {
    	if (arg || !TP->query_prop(FOUND_TRAPDOOR))
        {
            return 0;
        }
    }
    /* The only commands to proceed this far is 'enter trapdoor' and 'down'. */
    /* And that only if the player has found the trapdoor. */

    LOAD_ERR(ROOM_BELOW_TRAPDOOR);
    other_room = find_object(ROOM_BELOW_TRAPDOOR);

    if (!other_room)
    {
        write("The trapdoor won't budge!\n");
        return 1;
    }

    write("You pull the trapdoor open and climb down a ladder. " +
    "The trapdoor falls back in place above you.\n");
    TP->move_living("M",other_room,1);
    tell_room(TO,"You glance around, and suddenly realise that " +
        QTNAME(TP) + " is gone!\n");
    tell_room(other_room,QCNAME(TP) + " arrives down the ladder.\n",TP);

    return 1;
}

void
init()
{
	::init();
    add_action(trapdoor,"enter");
    add_action(trapdoor,"open");
    add_action(trapdoor,"down");
}

string
exa_trapdoor()
{
	if (TP->query_prop(FOUND_TRAPDOOR))
    {
    	return "The trapdoor leads down into darkness.\n";
    }
    else
    {
    	return "You find no trapdoor.\n";
    }
}

string
show_trapdoor()
{
	if (TP->query_prop(FOUND_TRAPDOOR))
    {
    	return "There is a trapdoor leading down concealed among the " +
            "floorboards of a large dust-free patch.";
    }
    else
        return "";
}

string
find_trapdoor(object searcher, string searched)
{
	if (searcher->query_prop(FOUND_TRAPDOOR))
    {
    	return "You renew your acquaintance with the trapdoor.\n";
    }
    else
    {
        searcher->add_prop(FOUND_TRAPDOOR,1);
    	return "You find a trapdoor cunningly concealed among " +
            "the floorboards of the " + searched + "!\n";
        
    }
}

