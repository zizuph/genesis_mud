inherit "/std/room";

#include "defs.h"
#include "/d/Shire/open/herbsearch.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

object dog;

create_room()
{
    set_short("garden");
    set_long(break_string(
     "You are in the garden of a herbfarm. This seems to be the western "
    + "end of the farm, as there is a grove of trees blocking "
    + "further cultivation westward.\n", 70));

    add_item("trees", break_string(
    "The trees in the grove are willows, and since you know willows grow "
    + "near water, you wonder the source of its nourishment.\n", 70));

    add_prop(ROOM_I_INSIDE,0);

    add_prop(OBJ_I_SEARCH_TIME, 8);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"ground"}));
    add_herb_file(STAND_HERB + "grass");

    add_exit(STAND_DIR + "farthing4","east");
}

