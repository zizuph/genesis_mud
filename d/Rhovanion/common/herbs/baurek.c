/*
 * This is a herb for the Smaug Esgaroth quest
 *
 * written by: Blackstaff
 *
 * date: 950125
 */
inherit "/std/herb";

#include "/sys/stdproperties.h"

void 
create_herb()
{
	set_short("small golden nut");
	set_adj("small");
	add_adj("golden");
	set_name("nut");
	set_herb_name("baurek");
	set_id_long("This is a Baurek nut. It tastes good but is " +
		"pretty useless.\n");
	set_unid_long("A small golden nut. It almost looks like a nugget.\n");
	set_id_diff(25);
	set_find_diff(2);
}



		

