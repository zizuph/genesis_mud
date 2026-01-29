/*
 * This is a herb for the Smaug Esgaroth quest
 *
 * written by: Blackstaff
 *
 * date: 950123
 */
inherit "/std/herb";

#include "/sys/stdproperties.h"

void 
create_herb()
{
	set_short("beautiful white flower");
	set_adj("beutiful");
	add_adj("white");
	set_name("flower");
	set_herb_name("peliana");
	set_id_long("This is a very common flower called Peliana.\n" +
		"It is often picked and distilled with lavander to make " +
		"perfume.\n"+
		"It smells wonderful.\n");
	set_unid_long("This is a beutiful flower.\n"+
		"It smells wonderful.\n");
	set_id_diff(10);
	set_find_diff(1);
}


		

