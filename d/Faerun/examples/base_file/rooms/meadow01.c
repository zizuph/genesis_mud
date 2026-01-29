/*
 * A meadow room
 * By Finwe, June 2016
 */

#pragma strict_types

#include "/d/Faerun/defs.h"
#include "../defs.h"

// This inherits the drink function from Gondor so we don't have to
// make a new one. Thanks Varian for letting us use it!!
inherit "/d/Gondor/common/lib/drink_water.c";
inherit BASE_MEADOW;

int pelt_found = 0;
object pelt;

void
create_meadow()
{
// This adds the room to the magic map
//    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

// You can either define your own set_short() or use the one defined in the
// base file.

// This adds more description to the room.
    set_extraline("The grass is a deep green and thick. Wild flowers grow " +
        "scattered in the meadow, dotting the grass with vibrant colors. " +
        "A small brook runs east along a small path. A fallen log is " +
        "hidden in the grass, and a road leads north to some stables.");

    add_item(({"log", "fallen log"}),
        "The log looks half rotted. Grass grows up around it, hiding most " +
        "of it in the meadow.\n");
// This sets up the drink function and lists where players can drink from
    set_drink_from(({"brook", "stream", "small brook"}));

// This adds the add_path() details from the base_meadow file
    add_path();
    add_brook();

// this sets up the search routine to find something in the log
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN,"my_search");

    add_exit(ROOM_DIR + "meadow02",  "east");
//    add_exit("/d/Faerun/stables/yard",  "north");

    reset_room();
}

void
reset_room()
{
    ::reset_room();
    pelt_found = 0;
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
    int awareness;

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < 13)
    {
        return 0;
    }

    if(str=="log" || str=="fallen log" || str=="rotting log" || 
       str=="half rotted log")
    {
        if(pelt_found == 1)
        {
            return "You found nothing in the log.\n";
        }
        else
        {
            seteuid(getuid(TO));
            pelt = clone_object("/d/Faerun/examples/obj/mink_pelt");
            pelt->move(searcher,1);
            say(QCTNAME(searcher)+ " finds something inside the fallen log.\n");
            pelt_found = 1;
            return "You find a " + pelt->short() + " inside the fallen log.\n";
        }

      return "You found nothing inside the log!\n";
    }
    else
    {
        return ;
    }
}
