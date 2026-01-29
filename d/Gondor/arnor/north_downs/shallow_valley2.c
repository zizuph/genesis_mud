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
    set_short("A shallow valley in the North Downs");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");

    add_exit(NORTH_DOWNS_DIR + "shallow_valley1", "southeast", 0, 1);
    add_exit(NORTH_DOWNS_DIR + "ridge1", "up", 0, 3);

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

   desc = "At the middle of a shallow valley in the North Downs. The valley "+
   "is long but the springy turf makes travelling easy. This is the lowest "+
   "point in the valley. ";
   desc += query_arnor_time();

   return BSN(desc);
}
