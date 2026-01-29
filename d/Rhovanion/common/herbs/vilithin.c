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
	set_short("strange violet seed");
	set_adj("strange");
	add_adj("violet");
	set_name("seed");
	set_herb_name("vilithin");
	set_id_long("This is a Vilithin seed. Its a kind of pea " +
		"so if you just leave it here you might get some " +
		"food from it in about 3 months or so.\n");
	set_unid_long("This violet seed is completely round.\n");
	set_id_diff(25);
	set_find_diff(2);
}



		

