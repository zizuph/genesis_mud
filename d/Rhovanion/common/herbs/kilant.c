/* Theobald */
/*  950124 */
/* eating this fungus will give an */
/* unpleasant surprise */


inherit "/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"
#include "macros.h"
void create_herb()
{
 set_name("fungus");
 set_pname("funguses");
 set_adj("red");
 add_adj("white");
 add_adj("dots");
 set_short("red fungus with white spots");
 set_pshort("red funguses with white spots");
 set_herb_name("kilant");
 set_unid_long("This fungus looks really weird.\n");
 set_id_long("This is a small red fungus with white spots on and it is called " +
	"kiliant. This fungus are used by a special sort of flies and they " +
 	"use it to lay their eggs.\n"); 
 set_id_diff(12);
 set_find_diff(14);
 set_effect(HERB_POISONING,"herb",15);
}	

void
init()

{
	::init();
	add_action("do_eat","eat");
}

int do_eat(string str)

{
if (str=="fungus" || str=="kilant")
	{
	say(QTNAME(this_player()) + "starts to eat the fungus and you see that " +
		"the whole fungus is full of worms.\n");
	write("You start to eat the fungus, but when you have eaten half of it " +
		"you realize that it is full of worms. You quickly throw the " +
		"other half away and you can see that you have bitten lots of " +
		"worms to halves.\n"); 
	return 0;
	}
else
	{
	write ("eat what ?");
	return 1;
	}
}
