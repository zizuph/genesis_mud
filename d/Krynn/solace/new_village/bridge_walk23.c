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

    set_long_desc("You are standing before a peculiar building. It " +
		  "seems to have been here for quite sometime and it " +
		  "will probably be here until time ends. There are " +
		  "stairs leading southwest into the building. Attached " +
		  "to the massive trunk is a wooden sign. The bridge-walk " +
		  "continues to the southeast and to the northwest.");

    add_exit(TDIR + "platform7", "southeast");
    add_exit(TDIR + "wise_club", "southwest");
    add_exit(TDIR + "bridge_walk24", "northwest");

    add_item("sign", "It is a plain wooden sign with some words on it.\n");

    add_cmd_parse("[the] [wooden] 'sign'", "read", 
		  "It says:\n" +
		  "  +--------------------------------+\n" +
		  "  | * The Wise people of Genesis * |\n" +
		  "  +--------------------------------+\n");

    seteuid(getuid(TO));
    set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

    reset_solace_room();
}
