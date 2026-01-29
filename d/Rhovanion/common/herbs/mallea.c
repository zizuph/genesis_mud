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
	set_short("slimy sticky weed");
	set_adj("slimy");
	add_adj("sticky");
	set_name("weed");
	set_herb_name("mallea");
	set_id_long("This weed is in fact an algae of the Mallea family." +
		 "Some old fishermen claim it has magic properties, but that " +
		"has never been proven.\n");
	set_unid_long("This is a slimy sticky weed, and you sure regret " +
		"picking it up.\n");
	set_id_diff(25);
	set_find_diff(4);
}



		

