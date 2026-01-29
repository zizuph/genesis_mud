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
    set_short("At the southern bank of a stream in the North Downs");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");

    add_exit(NORTH_DOWNS_DIR + "stream1", "northeast", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "narrow_valley", "southeast", 0, 2);

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

   desc = "At the southern bank of a stream in the North Downs. The swift "+
   "and deep-looking stream flows from the northwest to the southeast. "+
   "There is some sort of stone foundation high up on the river bank. "+
   "The stream is to the northeast, the valley extends to the southeast. ";
   desc += query_arnor_time();

   return BSN(desc);
}
