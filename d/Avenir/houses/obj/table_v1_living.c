/*
 * table_v1_living
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
    set_describe_prefix("In the center of the room is a low table");
	set_long("This is a low, round table made of kesoit wood polished "+
    "to a sheen that reflects the glow of the Source above.\n");
	add_item(({"wood", "kesoit wood"}),
	"The table is made of the wood of the kesoit tree native to Sybarus.\n");
}

