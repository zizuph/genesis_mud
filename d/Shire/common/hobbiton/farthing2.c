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
      "You are in the garden of a herbfarm. This particular slab "
    + "of land is used to grow crop and flowers, which are to be dried "
    + "and smoked. The land has recently been harvested, though. The "
    + "ground seems empty.\n", 70));

    add_item("ground", break_string(
      "The ground seems to be void of useful greens, but perhaps "
    + "not everything has been harvested and taken away.\n", 70));

    add_prop(ROOM_I_INSIDE,0);

    add_prop(OBJ_I_SEARCH_TIME, 8);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"ground"}));
    add_herb_file(STAND_HERB + "treemushroom");

    add_exit(STAND_DIR + "farthing1.c","east");
    add_exit(STAND_DIR + "farthing4","west");
}

