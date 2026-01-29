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
	set_short("large black nut");
	set_adj("large");
	add_adj("black");
	set_name("nut");
	set_herb_name("ylivath");
	set_id_long("This is an Ylivath nut. It tastes good but is " +
		"rather posionus.\n");
	set_unid_long("A large black nut. It almost looks like a piece of coal.\n");
	set_id_diff(25);
	set_find_diff(2);
	set_effect(HERB_POISONING,"spider",10);
}



		

