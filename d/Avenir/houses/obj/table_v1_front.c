/*
 * table_v1_front
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
	
	add_name("table_v1_front");
    set_describe_prefix("In the center of the room is a marble-topped table");
	set_long("This is a tall, round table made of kesoit wood, with "+
	    "a piece of polished marble on top. ");
	add_item(({"wood", "kesoit wood"}),
	"The table is made of the wood of the kesoit tree native to Sybarus.\n");
	
	add_item(({"marble", "marble-top", "matble top"}),
    "A thick slab of marble has been cut to fit the top of the table.\n");
	
	seteuid(getuid());
    clone_object(HOBJ+"vase")->move(this_object(), 1);
}

