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
	set_short("twisted gnarled root");
	set_adj("twisted");
	add_adj("gnarled");
	set_name("root");
	set_herb_name("linthor");
	set_id_long("This is a linthor root. It has a strong, peppery taste " +
		"and is commonly used in cooking.\n");
	set_unid_long("A twisted gnarled root. You think it might be edible, " + 
                 "but then again it might not be...\n");
	set_id_diff(25);
	set_find_diff(2);
}



		

