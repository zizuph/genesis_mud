// -*-C++-*-
// file name:	table.c
// creator(s): 	Sirra -Nov 2002
// revisions:
// last update:  Lilith Nov 2021: added pad of paper and pen.
// purpose:	table in the museum center
// note: Implemented from Idea Report
// bug(s):
// to-do:


inherit "/std/container";

#include <stdproperties.h>


void
fill_table()
{
	object obj1, obj2;
    obj1 = clone_object("/d/Avenir/common/bazaar/museum/obj/pad");
    obj1->move(this_object(),1);
    obj2 = clone_object("/d/Avenir/common/bazaar/Obj/misc/poet_pen");
    obj2->randomize();
    obj2->move(this_object(),1);
	
}
	
void
create_container()
{
	 set_short("table");
	 set_name("table");
	 add_name("tables");

	 set_long("These are wooden tables, low and broad, "
		+"with stained-glassbowl candles atop and plum "
		+"cushions underneath.\n");

	 add_prop(OBJ_M_NO_GET, 1);
	 add_prop(CONT_I_TRANSP, 1);
     add_prop(CONT_I_ATTACH, 1);
	 add_prop(CONT_I_MAX_WEIGHT, 10000);
	 add_prop(CONT_I_MAX_VOLUME, 10000);

	 set_no_show_composite(1);
	 seteuid(getuid(this_object()));
	 fill_table();
}


