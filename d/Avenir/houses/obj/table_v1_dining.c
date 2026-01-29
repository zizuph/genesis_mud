/*
 * table_v1_dining
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
	add_name("table_v1_dining");
    set_describe_prefix("The room is dominated by a large oval table");
	set_long("This oval table is made of kesoit wood polished "+
    "to a sheen that reflects the glow of the Source above. There is "+
	"a bench on either side that will seat three, and two high-backed "+
	"chairs at the ends.\n");
	add_item(({"wood", "kesoit wood"}),
	"The table is made of the wood of the kesoit tree native to Sybarus.\n");

	seteuid(getuid());
    clone_object(HOBJ+"fruit_bowl")->move(this_object(), 1);
}

