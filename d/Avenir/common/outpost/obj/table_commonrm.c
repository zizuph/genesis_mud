/*
 * table_v1_dining
 * Lilith, Feb 2022
 *
 */
#pragma strict_types
#include "../outpost.h"

inherit OBJ +"table_base";

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
	add_name("common_table_fort");
//    set_describe_prefix("The room is dominated by a large table");
	set_long("This rectangular table is one of several scattered throughout "+
     "the common room. It is made of the same pale limestone as "+
     "the floor. There are two benches placed alongside it.\n");

}

