inherit "/d/Gondor/arnor/arnor_room.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/arnor/north_downs/nd_defs.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
#include "/d/Gondor/common/lib/herb_list.h"

void   reset_room();
string set_arnor_long();

void
create_gondor()
{
    set_short("Eastern part of a broad valley in the North Downs");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");

    add_exit(NORTH_DOWNS_DIR + "broad_valley3", "southwest", 0, 3);
    add_exit(NORTH_DOWNS_DIR + "shore", "north", 0, 3);
    add_exit(NORTH_DOWNS_DIR + "broad_valley5", "northeast", 0, 3);

    add_herb_file(HERB_DIR + "blueberry");

    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_prop(OBJ_I_SEARCH_TIME, 5);

    set_search_places(({ "grass", "ground" }));
}

void
reset_room()
{
    set_searched(0);
}

string
set_arnor_long()
{
   string desc;

   desc = "In the eastern part of a broad valley in the North Downs. "+
   "In the steep slope to the southeast is a dark ravine. Large boulders "+
   "block the bottom of the ravine. The valley extends to the southwest, "+
   "north and northeast. ";
   desc += query_arnor_time();

   return BSN(desc);
}

void
init()
{
    ::init();
    add_action("do_climb","climb");
}

int
do_climb(string s)
{
    if(s == "blocks")
    {
        set_dircmd("blocks");
        TP->move_living("into the ravine", NORTH_DOWNS_DIR + "ravine");
        return 1;
    }
    NFN0("Climb what?");
}
