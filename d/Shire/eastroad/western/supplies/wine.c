/* Wine for Shire Inns
 * Taveren, January 2001
 *
 * Emotes and add_items added for fun
 * Raymundo, Jan 2020
 *
 */

inherit "/std/drink";
#include "/d/Shire/sys/defs.h"




void
create_drink()
{
    set_name("wine");
    add_name("house wine");
    set_pname("wines");
    set_short("glass of wine");
    set_pshort("glasses of wine");
    set_adj("glass");
    set_long("This is a glass of house wine. It looks purple and smells "
		+ "sour. It's made of grapes but judging by the aroma, it was "
		+ "fermented and aged in old barrels.\n");
    set_soft_amount(91);
    set_alco_amount(14);
	
	add_item("aroma", "The aroma looks completely clear and invisible, but "
		+ "then that's likely because people smell wine.\n");
	add_item("glass", "The glass is a cup shape on top of a stem, "
		+ "perfect for swirling and smelling the wine.\n");
	
}

void
init()
{
	::init();
	add_action("do_smell", "smell");
	add_action("do_swirl", "swirl");
}

int
do_smell(string str)
{
	if(str == "wine" | str == "glass" | str == "glass of wine")
	{
		write("You smell the wine. It smells sour and flat, as if the "
			+ "winemaker cared about turning grapes into alcohol, but "
			+ "but didn't care at all how it'd taste.\n");
		say(QCTNAME(TP) + " puts " + HIS_HER(TP) + " nose into the "
			+ "wine glass and inhales through " + HIS_HER(TP)
			+ " nose. " + CAP(HE_SHE(TP)) + " looks disappointed.\n");
		return 1;		
		
	}
	else
	{
		return 0;
	}
}

int
do_swirl(string str)
{
	if(!strlen(str) | str == "glass" | str == "wine")
	{
		say(QCTNAME(TP) + " swirls the glass of wine around, examining its "
			+ "'legs'.\n");
		write("You swirl the glass of wine around, examining its 'legs'.\n");
		return 1;
		
	}
	else
	{
		notify_fail("Swirl what? The wine?\n");
		return 0;
	}
}