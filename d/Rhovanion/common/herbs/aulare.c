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
	set_short("shimmering blue berry");
	set_adj("shimmering");
	add_adj("blue");
	set_name("berry");
	set_herb_name("aulare");
	set_id_long("A shimmering blue berry called Aulare. You " +
		"should be careful, as it is poisonus.\n");
	set_unid_long("This is a shimmering blue berry. It looks tasty "+
		"but you have no idea if it is edible.\n"); // nice trap!
							    // -Erane
	set_id_diff(25);
	set_find_diff(3);
	set_effect(HERB_POISONING,"herb",25);
}



		

