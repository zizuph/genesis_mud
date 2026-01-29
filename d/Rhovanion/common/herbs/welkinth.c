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
	set_short("red dropshaped root");
	set_adj("red");
	add_adj("dropshaped");
	set_name("root");
	set_herb_name("welkinth");
	set_id_long("This root is called tear of Smaug, but the " +
		"real name is Welkinth. The legend says it came " +
		"to be when a drop of blood fell to the ground from" +
		" Smaug when he was dying. It is rumored to give courage" +
		" in battle to people.\n");
	set_unid_long("This red root looks exactly like a drop.\n");
	set_id_diff(25);
	set_find_diff(2);
	set_effect(HERB_ENHANCING,"dis",3);
}



		

