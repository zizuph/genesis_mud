/*
 * table_v1_dining
 * Lilith, Feb 2022
 *
 */
#pragma strict_types

#include "../outpost.h"
inherit OBJ +"table_base";

/*
 * Function name: create_table
 * Description:   Call this function to set up the
 *                non-default values for your table.
 */
public void
create_table()
{
    ::create_table();
	add_name("table_dining_rm");
    set_describe_prefix("The room is dominated by a large rectangular table");
	set_long("This long table is made of slabs of basalt laid across "+
    "blocks of the same stone. It has been polished to a soft sheen over "+
	"its many years of use. The benches on either side will seat three.\n");

	seteuid(getuid());
    clone_object("/d/Avenir/houses/obj/fruit_bowl")->move(this_object(), 1);
}

