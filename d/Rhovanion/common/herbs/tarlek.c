/*
 * This is a herb for the Smaug Esgaroth quest
 *
 * written by: Blackstaff
 *
 * date: 950124
 */
inherit "/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/lib/herb_types.h"

void 
create_herb()
{
	set_short("small black root");
	set_adj("small");
	add_adj("black");
	set_name("root");
	set_herb_name("tarlek");
	set_id_long("This is a Tarlek root. It is " +
		"well known to cure all poisons.\n");
	set_unid_long("This is a small black root.\n");
	set_id_diff(50);
	set_find_diff(8);
	set_effect(HERB_CURING,"all",100);
}


		

