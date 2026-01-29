/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

#include "/d/Krynn/common/herbsearch.h"

reset_solace_room()
{
    set_searched(random(2));

}

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("This is a bridge-walk between two platforms. The thick " +
		  "canopy overhead forms a protective shield against " +
		  "the outside world."
                  /* + "Circling the tree are wooden stairs " +
		   * "leading yet higher up in the vallenwood."
		   */
		  );

    add_exit(TDIR + "platform6", "southeast");
    add_exit(TDIR + "platform7", "northwest");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

/*
    add_exit(ROOM_TO_NERAKA, "up");
*/
}
