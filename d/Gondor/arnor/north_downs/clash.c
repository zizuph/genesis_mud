inherit "/d/Gondor/arnor/arnor_room.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/arnor/north_downs/nd_defs.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
#include "/d/Gondor/common/lib/herb_list.h"

void   reset_room();
string set_arnor_long();
int test_climb();

void
create_gondor()
{
    set_short("Near a clash between two valleys in the North Downs");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");

    add_exit(NORTH_DOWNS_DIR + "narrow_valley", "northwest", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "broad_valley7", "east", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "ridge3", "up", "@@test_climb@@", 2);

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

   desc = "At the end of a narrow valley in the North Downs. The narrow "+
   "valley, which comes from the northwest, leads out to a broad valley "+
   "to the east. South a steep slope climbs up to a ridge. ";
   desc += query_arnor_time();

   return BSN(desc);
}

int
test_climb()
{
/*
 * Add more later
 */
    return 0;
}
