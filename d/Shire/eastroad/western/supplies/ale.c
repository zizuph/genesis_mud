/* Ale for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/drink";
#include "/d/Shire/sys/defs.h"


string
drink_message()
{
	say(QCTNAME(TP) + " licks around " + HIS_HER(TP) + " mouth, making sure "
		+ "sure to get every last delicious drop of the head from the ale.\n");
	return("You notice a lot of the head from the ale is around your mouth, "
		+ "instead of in it, so you lick your lips and savor every last "
		+ "drop.\n");
}

void
create_drink()
{
        set_name("ale");
        add_name("pint");
        add_name("pint of ale");
        set_pname("ales");
        add_pname("pints");
        add_pname("pints of ale");
        set_adj(({"pint", "mug"}));
        set_short("pint of ale");
        set_pshort("pints of ale");
        set_long("The drink that the inn is named "
         +"after, this is a pint of foamy ale. It has a head that's far "
		 + "thicker than most ales you've come across, and is a light "
		 + "golden color. It looks like it'll be a refreshing beverage "
		 + "after a long day on the road.\n");
        set_soft_amount(115);
        set_alco_amount(7);
		
		add_item("mug", "This mug is about one and a half hobbit hands high, "
			+ "and is wider at the top than it is at the bottom. It has a "
			+ "diamond pattern etched into the glass, and is, at the moment, "
			+ "completely full of ale. This is the stuff that makes Dwarves' "
			+ "hearts go pitter patter.\n");
		add_item( ({"foam", "head"}), "The foam on top of the beer, sometimes "
			+ "called 'the head', is where the real afficianados go to appraise "
			+ "the quality of the brew. This head is almost half an inch high, "
			+ "and is holding up quite well. Likely this will be a memorable "
			+ "pint of ale!\n");
		add_item( ({"pattern", "diamond pattern"}), "The diamonds look like "
			+ "squares would look if you rotated them onto their corners.\n");
		set_drink_msg(drink_message());
}
