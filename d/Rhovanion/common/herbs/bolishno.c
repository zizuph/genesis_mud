/*
 * This is a herb for the Smaug Esgaroth quest
 *
 * written by: Blackstaff
 *
 * date: 950123
 */
inherit "/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/lib/herb_types.h"

void 
create_herb()
{
	set_short("slimy wet seaweed");
	set_adj("slimy");
	add_adj("wet");
	set_name("seaweed");
	set_herb_name("bolishno");
	set_id_long("This is a Bolishno seaweed. It is " +
		"very slimy, but you know it is good to eat " +
		"if you feel tired.\n");
	set_unid_long("This is a slimy wet seaweed.\n");
	set_id_diff(25);
	set_find_diff(5);
	set_effect(HERB_HEALING,"fatigue",50);
}


		

