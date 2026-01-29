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
	set_short("small slick leaf");
	set_adj("small");
	add_adj("slick");
	set_name("leaf");
	set_herb_name("taurin");
	set_id_long("This is a leaf from the Taurin bush. Housewives use this\n" +
		"in jams and other things, because it has preserving properties.\n");
	set_unid_long("A small slick leaf. It almost looks like it is covered with enamel.\n");
	set_id_diff(25);
	set_find_diff(2);
}



		

