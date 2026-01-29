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
    set_short("A rocky ridge in the North Downs");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");
    add_item("hollow", "In the hollow grows heather abudantly(?).\n");

    add_exit(NORTH_DOWNS_DIR + "ridge1", "southwest", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "ridge3", "northeast", 0, 2);

/*
    add_herb_file(HERB_DIR + "blueberry");

    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({ "grass", "ground" }));
 */

    add_prop(OBJ_S_SEARCH_FUN, "secret_exit");
    add_prop(OBJ_I_SEARCH_TIME, 5);
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

   desc = "A rocky ridge of high-land in the North Downs, the land falls "+
   "steeply down on both sides. At the brink there is a hollow. "+
   "The ridge goes southwest and northeast. ";
   desc += query_arnor_time();

   return BSN(desc);
}

void
secret_exit(string s)
{
    add_exit(NORTH_DOWNS_DIR + "dell1", "down", 0, 2);
    return;
}
