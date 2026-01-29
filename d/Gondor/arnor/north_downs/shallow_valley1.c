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
    set_short("Shallow valley");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");
    add_item("slope", 
    "The slope is so steep that stones keep rolling down... \n");

    add_exit(FORNOST_DIR + "hill_top", "up", 0, 3);
    add_exit(NORTH_DOWNS_DIR + "shallow_valley2", "northeast", 0, 2);

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

   desc = "At the southern end on the floor of a shallow valley. "+
   "To the northeast the valley spreads out, green and gentle. To the south a "+
   "steep slope climbs up to a hill-brow. Here, the grass is springy and "+
   "fresh even though the isn't any visible water. ";
   desc += query_arnor_time();

   return BSN(desc);
}
