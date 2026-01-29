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
    set_short("At the shore of a lake in the North Downs");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");

    add_exit(NORTH_DOWNS_DIR + "broad_valley6", "west", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "broad_valley5", "east", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "broad_valley4", "south", 0, 2);

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

   desc = "At the shore of a lake in the North Downs. "+
   " ... something about the lake here ... "+
   "The bushes grow very high here, close to the lake. Some few birches "+
   "also grow close to the shore. The rest of the valley can be reached "+
   "to the west, east and south. ";
   desc += query_arnor_time();

   return BSN(desc);
}
