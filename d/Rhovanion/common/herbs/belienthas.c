/*
 * This is a herb for the Smaug Esgaroth quest
 *
 * written by: Blackstaff
 *
 * date: 950124
 */
inherit "/std/herb";

#include "/sys/stdproperties.h"

void 
create_herb()
{
	set_short("large ugly flower");
	set_adj("large");
	add_adj("ugly");
	set_name("flower");
	set_herb_name("belienthas");
	set_id_long("This flower is called Belienthas. Although " +
		"it is ugly, it smells very fresh. It is sometimes " +
		"used as spice for food.\n");
	set_unid_long("This is a large ugly flower however it smells "+
		"very fresh.\n");
	set_id_diff(25);
	set_find_diff(3);
}



		

