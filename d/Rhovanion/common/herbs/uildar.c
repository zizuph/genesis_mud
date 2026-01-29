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
	set_short("chunk of coagulated silverish tree sap");
	set_adj("silverish");
	add_adj("tree");
	set_name("sap");
	set_herb_name("uildar");
	set_id_long("You suspect that this is a piece of sap from " +
		"the Uildar tree. You wonder how it came here, as no Uildar " +
		"tree grows here.\n");
	set_unid_long("This is a silverish chunk of sap.\n");
	set_id_diff(25);
	set_find_diff(2);
	set_decay_time(99999999);
}



		

