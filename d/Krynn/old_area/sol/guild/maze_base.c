/* Maze to the guild by Lord Rastlin */
/* base file to inherit into the maze rooms (with the herbsearch functions),
   by Aridor, 09/94 */

#include "/d/Krynn/common/defs.h"
#include "guild.h"
#include "local.h"
#define  GONDOR_HERB_PATH  "/d/Gondor/common/herbs/"

inherit OUTSIDE_BASE;

#include HERBSEARCH

void
create_maze()
{
}

void
reset_solace_room()
{
    set_searched(random(11));
}

void
create_solace_room()
{
    set_short("In a forest maze");
    set_long("You are walking in the forest. "
	     + "The forest is very thick, and it looks "
	     + "the same wherever you look.\n");
    add_item(({"trees","tree","forest"}),
	     "There are trees in the forest all around you.\n");
    LIGHT;
    seteuid(getuid(TO));
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,2);
    set_search_places(({"forest"}));
    add_herb_file(GONDOR_HERB_PATH + "athelas");
    add_herb_file(GONDOR_HERB_PATH + "mint");
    add_herb_file(GONDOR_HERB_PATH + "hemlock");
    add_herb_file(GONDOR_HERB_PATH + "blueberry");
    add_herb_file(GONDOR_HERB_PATH + "foxglove");
    add_herb_file(GONDOR_HERB_PATH + "holly");
    create_maze();
}
