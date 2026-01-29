/*
 * This is a herb used in the Smaug Esgaroth quest
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
	set_short("yellow slimy fungus");
	set_adj("slimy");
	add_adj("yellow");
	set_name("fungus");
	set_herb_name("baldae");
	set_id_long("This is a rather uncommon fungus called Baldae.\n" +
		"Its has no special effects to your knowledge, and "+
		"it tastes rather foul. You wonder why you even bothered "+
		"to pick it up.\n");
	set_unid_long("This is a foul smelling fungus, you have no idea what "+
		"it possibly could be used for.\n");
	set_id_diff(20);
	set_find_diff(3);
}


		

