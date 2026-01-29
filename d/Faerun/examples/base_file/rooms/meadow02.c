/*
 * A meadow room
 * By Finwe, June 2016 2016
 */

#pragma strict_types

#include "/d/Faerun/defs.h"
#include "../defs.h"

inherit BASE_MEADOW;

// This inherits the drink function from Gondor so we don't have to
// make a new one. Thanks Varian for letting us use it!!
inherit "/d/Gondor/common/lib/drink_water.c";

int ring_found = 0;
object ring;

void
create_meadow()
{
// This adds the room to the magic map
//    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

// You can either define your own set_short() or use the one defined in the
// base file.

// This adds more description to the room.

    set_extraline("The meadow is a sea of green grass. A small brook flows in from the east to a pond. Rumour has it someone lost a valuable ring in the grass, but no one has been able to find it.");

// This sets up the drink function and lists where players can drink from
    set_drink_from(({"brook", "stream", "small brook", "pond"}));

// This adds the add_path() details from the base_meadow file
    add_path();
    add_brook();
    add_pond();

    add_exit(ROOM_DIR + "meadow01",  "west");

// this sets up the search routine to find something in the log
    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(OBJ_S_SEARCH_FUN,"my_search");
    reset_room();
}

void
reset_room()
{
    ::reset_room();
    ring_found = 0;
}

public void
init()
{
    ::init();
// This initializes the drink function.
    init_drink();
}

mixed
my_search(object searcher, string str)
{

    string	msg, where, what;
    int awareness;

    seteuid(getuid());

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < 13)
    {
        return "";
    }


    if (!strlen(str))
    {
	return "";
    }

// This breaks down the search string so we can check where to search (grass)
// and what (ring) to search for
    if (sscanf(str, "%s for %s", where, what) != 2)
    {
    	where = str;
    }

    if(where == "grass")
    {
        if(what == "ring" || what == "valuable ring")
        {
            if(ring_found == 1)
            {
                return "You find nothing in the grass.\n";
            }
            else
            {
                seteuid(getuid(TO));
                ring = clone_object("/d/Faerun/examples/obj/ring");
                ring->move(searcher,1);
                say(QCTNAME(searcher)+ " found something in the grass.\n");
                ring_found = 1;
                return "You find a " + ring->short() + " in the grass.\n";
            }
        }
    }
    return "";
}