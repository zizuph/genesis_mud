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
	set_short("green thorny weed");
	set_adj("green");
	add_adj("thorny");
	set_name("weed");
	set_herb_name("belakin");
	set_id_long("This is a weed called Belakin. It is quite common " +
		"in wooded areas. It is quite useless.\n");
	set_unid_long("A green thorny weed.\n");
	set_id_diff(25);
	set_find_diff(2);
}



		

