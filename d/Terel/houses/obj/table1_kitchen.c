/*
 * table_v1_kitchen
 * Lilith, Feb 2022
 *
 */
#pragma strict_types
#include "../defs.h"

inherit HOBJ +"table_base";

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

/*
 * Function name: create_table
 * Description:   Call this function to set up the
 *                non-default values for your table.
 */
public void
create_table()
{
    ::create_table();
	add_name("table_h1_kitchen");
    set_describe_prefix("There is a large round table at the center "+
        "of the room");
	set_long("This table is made of silver pine wood polished "+
    "to a sheen that reflects the light. There are two high-backed "+
	"chairs at the east and west ends of the table.\n");
	add_item(({"wood", "pine wood"}),
	"The table is made of the wood of the silver pine tree that "+
    "grows to plentifully around here.\n");

	seteuid(getuid());
}

