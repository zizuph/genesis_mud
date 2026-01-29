/* Mortis 01.2006
 *
 * Drink sold at the Green Twitch Inn in Palanthas.
 * Has a pleasant belching effect when consumed en masse.
 */

#include "/sys/stdproperties.h"
#include <language.h>
#include <macros.h>
#include "../../local.h"

inherit "/std/drink";
inherit "/lib/keep";

create_drink()
{
    set_soft_amount(40);
    set_alco_amount(12);
    set_name("ale");
	set_pname("ales");
    add_name(({"mug", "drink"}));
	add_pname(({"mugs", "drinks"}));
    set_adj("twitch");
    set_short("mug of Twitch ale");
    set_pshort("mugs of Twitch ale");
    set_long("A mug of pale golden ale with a frothy head from the "
	+ "Green Twitch Inn.\n");
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
}

void
init()
{
    ::init();
    ADA("smell");
}

int
smell(string str)
{
    NF("Smell what?\n");

    if (!str)
	return 0;

    if (!parse_command(str, ({}), "[mug] [of] [twitch] 'ale'") || str != "mug")
	return 0;

    TP->catch_msg("The mug of frothy Twitch ale has a pungent aroma of hops "
	+ "and grain and smells fresh.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " mug of Twitch ale "
	+ "to " + HIS(TP) + " nose sniffing it for a moment as " + PRONOUN(TP)
	+ " inhales its aroma.\n", ({TO, TP}));
    return 1;
}

void
special_effect(int numofdrinks)
{
	string ales = LANG_WNUM(numofdrinks);

	if (numofdrinks == 1)
	{
		TP->catch_msg("The mug of Twitch ale goes down nicely with a fresh "
		+ "grain taste leaving a slight aftertaste of hops.\n");
	}

	if (numofdrinks > 1 && numofdrinks <= 5)
	{
		TP->catch_msg("You toss back " + ales + " mugs of Twitch ale and "
		+ "let out a groarking belch!\n");
		say(QCTNAME(TP) + " tosses back " + ales + " mugs of Twitch ale and "
		+ "lets out a groarking belch!\n");
	}

	if (numofdrinks > 5 && numofdrinks <= 10)
	{
		TP->catch_msg("You hurl back " + ales + " mugs of Twitch ale and "
		+ "let out a thundering groarka belch of power!\n");
		say(QCTNAME(TP) + " hurls back  " + ales + " mugs of Twitch ale and "
		+ "lets out a thundering groarka belch of power!\n");
	}

	if (numofdrinks > 10 && numofdrinks <= 20)
	{
		TP->catch_msg("You throw your head back and dump " + ales + " mugs "
		+ "of Twitch ale down your throat.\nYou let out a ground shattering "
		+ "mega-belch of thunderous might spraying everyone in the room in "
		+ "the face with bits of the last things you ate.\n");
		say(QCTNAME(TP) + " throws " + HIS(TP) + " head back and dumps "
		+ ales + " mugs of Twitch ale down " + HIS(TP) + " throat.\n"
		+ QCTNAME(TP) + " lets out a ground shattering mega-belch of "
		+ "thunderous might spraying you in the face with bits of "
		+ one_of_list(({"roast pork", "roast boar", "roast boar brains",
			"roast boar heart", "chicken gizzard", "rotisserie chicken",
			"chocolate biscotti", "blueberry muffin", "garlicky spinach",
			"poppy-seeds", "stomach grime", "ass berries", "cod heads",
			"chumbly narnwhiffers", "pizza and sausage"})) + "!\n");
	}

	if (numofdrinks > 20)
	{
		TP->catch_msg("You throw your head back, open your mouth wide "
		+ "enough to swallow a whole boar, and dump " + ales + " mugs "
		+ "of Twitch ale into your gullet.\nYour stomach rumbles "
		+ "disturbingly as you erupt in a volcano like explosive belch "
		+ "of unearthly power and might spraying everyone in the room in "
		+ "the face with streams of bile and bits of the last things you "
		+ "ate.\n");
		say(QCTNAME(TP) + " throws " + HIS(TP) + " head back, opens "
		+ HIS(TP) + " mouth wide enough to swallow a whole boar, and dumps "
		+ ales + " mugs of Twitch ale into " + HIS(TP) + " gullet.\n"
		+ QCTNAME(TP) + "'s stomach rumbles disturbingly as " + HE(TP)
		+ " erupts in a volcano like explosive belch of unearthly power "
		+ "and might spraying you in the face with streams of bile and "
		+ "bits of " + one_of_list(({"roast pork", "roast boar",
			"roast boar brains","roast boar heart", "chicken gizzard",
			"rotisserie chicken","chocolate biscotti", "blueberry muffin",
			"garlicky spinach", "poppy-seeds", "stomach grime", "ass berries",
			"cod heads", "chumbly narnwhiffers", "pizza and sausage"}))
		+ "!\n");
	}
}

string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
}
