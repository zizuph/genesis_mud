/* Whiskey for Shire Inns
 * Taveren, January 2001
 *
 * Added some emotes for fun.
 * Raymundo, Jan 2020
 *
 */

inherit "/std/drink";
#include "/d/Shire/sys/defs.h"

void
create_drink()
{
        set_name("whiskey");
        set_short("glass of whiskey");
        set_pshort("glasses of whiskey");
        set_long("A tumbler of neat golden whiskey.\n");
        set_soft_amount(50);
        set_alco_amount(30);
        set_adj("glass");
		
		add_item( ({"tumbler", "glass"}), "You look closely at the glass "
			+ "and notice some condensation on the outside of the glass. "
			+ "Clearly the whiskey is cold, but not so cold as to ruin its "
			+ "smell.\n");
		add_item("condensation", "The condensation is a little bit of "
			+ "water that has accumulated on the outside of the glass.\n");
		set_drink_msg("The whiskey burns on the way down, but in a good way. "
			+ "You smile.\n");
}     

void
init()
{
	::init();
	add_action("smell_whiskey", "smell");
	
}

int
smell_whiskey(string str)
{
	if(str == "whiskey" | str == "glass")
	{
	write("You smell the " + query_short() + ". It smells like vanilla "
		+ "and alcohol, with a little bit of smoke in the background.\n");
	say(QCTNAME(TP) + " closes " + HIS_HER(TP) + " eyes as " + HE_SHE(TP)
		+ " inhales the scent of the " + query_short() + ".\n");
		
	return 1;	
	}
	else
	{
		return 0;
	}
}