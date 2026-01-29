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
	set_short("little brown seed");
	set_adj("little");
	add_adj("brown");
	set_name("seed");
	set_herb_name("pinotta");
	set_id_long("This is a Pinotta seed. Maybe it will " +
		"grow into a huge Pinotta tree some day.\n");
	set_unid_long("This is a little brown seed.\n");
	set_id_diff(25);
	set_find_diff(5);
}


		

