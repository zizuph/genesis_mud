/*
 * This is a herb for the Smaug Esgaroth quest
 *
 * written by: Blackstaff
 *
 * date: 950124
 */
inherit "/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"

void 
create_herb()
{
	set_short("tiny bloodred root");
	set_adj("tiny");
	add_adj("bloodred");
	set_name("root");
	set_herb_name("caltire");
	set_id_long("This root is named Caltire. It is also " +
		"called Bloodroot as it is known to heal wounds.\n");
	set_unid_long("This is a tiny blood-red root.\n");
	set_id_diff(25);
	set_find_diff(6);
	set_effect(HERB_HEALING,"hp",20);
}



		

