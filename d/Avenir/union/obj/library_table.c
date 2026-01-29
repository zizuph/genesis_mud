/*
 * File:     library_table
 * Created:  Lilith, April 
 * Purpose:  table for the novice library
 */
#pragma strict_types
#include "../defs.h"

inherit (UNION + "obj/table_base");

public void
create_table(void)
{
    set_name("table");
    add_name("_union_novice_table");
    set_adj(({"low","long","wide","stone","library","polished"}));
    set_short("stone slab table");
    set_long("This table is a long stone slab, probably hewn "+
      "from the living rock of this very room. Its surface "+
      "has been polished to a high sheen. It is wide and "+
      "low, designed to be used for reading while seated.\n");

    set_describe_prefix(" A table consisting of a thick stone "+
	"slab resting on a wide base near the center of the room");
}
