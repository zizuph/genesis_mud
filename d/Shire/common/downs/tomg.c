inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/herbsearch";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

void
create_shire_room()
{
    set_short("a garden");
    set_long(break_string(
	  "You are in Tom Bombadil's garden. His wife, the beautiful "
	+ "riverdaughter Goldberry, keeps it filled with fresh flowers. "
        + "Southwest you see the grim old forest, and far to the east "
        + "you can barely catch a glimpse of the village Bree.\n",70));

    add_item("flowers", break_string(
	  "The fair lady Goldberry provides the garden with the most "
	+ "beautiful flowers you have ever seen. She picks them in the "
	+ "forest near the river every day.\n",70));

    add_item(({"ground","garden"}), break_string(
          "The garden is kept by the fair Lady Goldberry. It is very "
        + "pretty, and well-kept.\n",70));

    add_exit(DOWNS_DIR + "tomg2", "west");

    /* Allow the searching for herbs */
    add_prop(OBJ_I_SEARCH_TIME,4);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    set_search_places(({"ground","garden"}));
    add_herb_file("/d/Gondor/common/herbs/lothore");
    add_herb_file(HERB_DIR + "pawnrose");
}
