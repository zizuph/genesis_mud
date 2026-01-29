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
    set_short("Southern part of a broad valley in the North Downs");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");

    add_exit(NORTH_DOWNS_DIR + "broad_valley2", "west", 0, 3);
    add_exit(NORTH_DOWNS_DIR + "bleak_hill", "north", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "broad_valley4", "northeast", 0, 3);

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

   desc = "In the southern part of a broad valley in the North Downs. "+
   "Close by, here at the valley floor, a gurgling sound is heard from "+
   "a fern-choked stream. The valley extends to the west and northeast. "+
   "To the north a steep zig-zag path leads up to a bleak hill. ";
   desc += query_arnor_time();

   return BSN(desc);
}
