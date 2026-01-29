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
	set_short("withered brown leaf");
	set_adj("withered");
	add_adj("brown");
	set_name("leaf");
	set_herb_name("herkin");
	set_id_long("This leaf grows on the Herkin tree. You are lucky\n" +
		"that it is withered, as it otherwise would be poisonus to touch.\n");
	set_unid_long("A withered brown leaf. It looks shriveled up and useless.\n");
	set_id_diff(25);
	set_find_diff(2);
}



		

