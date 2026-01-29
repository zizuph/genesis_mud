inherit "/std/room";

#include "defs.h"
#include "/d/Shire/open/herbsearch.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_room()
{
    set_short("garden");
    set_long(break_string(
      "You have entered the garden of a herbfarm. Here special herbs "
    + "are grown for many people. Most people smoke the herbs, but "
    + "others are said to be using the herbs as magical ingredients. "
    + "There are some low trees here that smell pleasant.\n", 70));

    add_item(({"tree","trees","low trees"}), break_string(
      "The low trees are giving off a quite pleasant smell. There are "
    + "berries hanging on them, but they do not seem ripe yet. "
    + "Perhaps you would find some ripe ones if you would search "
    + "the trees somewhat better.\n", 70));

    add_prop(ROOM_I_INSIDE,0);

    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"tree","trees","low trees"}));
    add_herb_file(STAND_HERB + "huckleberry");

    add_exit(STAND_DIR + "er20","north",0);
    add_exit(STAND_DIR + "farthing2.c","west");
    add_exit(STAND_DIR + "farthing3.c","south");
}
