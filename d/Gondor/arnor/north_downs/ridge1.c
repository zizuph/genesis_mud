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
    set_short("On the shoulder of a hill in the North Downs");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");

    add_exit(NORTH_DOWNS_DIR + "small_valley", "northwest", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "ridge2", "northeast", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "shallow_valley2", "south", 0, 2);

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

   desc = "On the shoulder of a hill in the North Downs, overlooking a "+
   "shallow valley. At the very top is a pile of armour and weapons. "+
   "Upon a stake in the middle is set the head of a great goblin. "+
   "The hill continues to the northeast. A steep slope leads down to the "+
   "northwest, while a gentle slope leads down to the south. ";
   desc += query_arnor_time();

   return BSN(desc);
}
