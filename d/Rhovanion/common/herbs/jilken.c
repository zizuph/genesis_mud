/*
 * This is a herb for the Smaug Esgaroth quest
 *
 * written by: Blackstaff
 *
 * date: 950125
 */
inherit "/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"

void 
create_herb()
{
	set_short("red bellshaped flower");
	set_adj("red");
	add_adj("bellshaped");
	set_name("flower");
	set_herb_name("jilken");
	set_id_long("This flower is named Jilken. It is also known as " +
		"hells bells, because of it's bell shape and that it is " +
		"mildly poisonus.\n");
	set_unid_long("This red flower looks exactly like a small bell\n");
	set_id_diff(25);
	set_find_diff(2);
	set_effect(HERB_POISONING,"spider",5);
}



		

