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
    set_short("The northwestern part of a broad valley in the North Downs");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");

    add_exit(NORTH_DOWNS_DIR + "clash", "west", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "broad_valley6", "east", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "broad_valley1", "south", 0, 2);

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

   desc = "The northwestern part of a broad valley in the North Downs. "+
   "The sign of wanton destruction is everywhere. Rotting bushes litter "+
   "the area. The ground has been trampled to mud by many feet. A small "+
   "stream runs north. To the west a small valley joins this one, east "+
   "and south this valley continues. ";
   desc += query_arnor_time();

   return BSN(desc);
}
