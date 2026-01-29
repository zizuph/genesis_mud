/* Mortis 02.2006
 *
 * Candy found in kitchen of merchant house Trusq.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include "../../local.h"

public void
create_food()
{
    set_amount(10);
    set_name("gumdrop");
    set_pname("gumdrops");
	add_name("drop");
    set_adj(({"orange", "shaped", "citrus", "gum"}));
	set_short("orange shaped citrus gumdrop");
    set_pshort("orange shaped citrus gumdrops");
    set_long("Shaped like a slice of peeled orange and completely encrusted "
	+ "in sugar, this gummy candy has an appealing citrus sweet aroma.  It "
	+ "is firm but gives when squeezed.\n");
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
	if (!str || !parse_command(str, ({}), "[orange] [shaped] [citrus] [gum] 'drop' / 'gumdrop' "))
	return 0;

    TP->catch_msg("You smell the orange shaped citrus gumdrop getting a hint "
	+ "of its sugary sweetness with a hint of citrus.\n");
    tell_room(E(TP), QCTNAME(TP) + " lifts " + HIS(TP) + " orange shaped "
	+ "citrus gumdrop to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_candy(object ob)
{
	ob->catch_msg("Ooooo, that gumdrop was soooo good!  You can feel it "
	+ "tingling your tummy and deliriously renewing your life force!\n");
	tell_room(E(ob), QCTNAME(ob) + " " + one_of_list(({"moans:  Ohhhhh, so "
	+ "yummy in my tummy.", "moans and rubs " + HIS(ob) + " tummy sensually.",
	  "says:  Ooooo, I need more in my tummy, yeah, my tummy!", "squeezes "
	+ HIS(ob) + " legs together as " + HIS(ob) + " eyes roll up under "
	+ HIS(ob) + " eyelids.", "cries:  Oh so gummy in my tummy!", "goes:  "
	+ "Mmmm, me rubby tummy gummy so good and ooooo!\n" + QCTNAME(ob)
	+ " hugs your leg while gyrating with " + HIS(ob) + " eyes rolled up "
	+ "under " + HIS(ob) + " eyelids."})) + "\n", ({TO, TP}));
}

void
special_effect(int n)
{
	string candyrace = QRACE(TP);

	write("You crunch through the sugar-encrusted outside of your orange "
	+ "shaped citrus gumdrop getting a taste of its sweet gummy interior "
	+ "with a slight hint of tart citrus.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches through the sugar-encrusted "
	+ "outside of " + HIS(TP) + " orange shaped citrus gumdrop.\n",
	({TO, TP}));

	if (parse_command(candyrace, ({}), "'kender' / 'hobbit'"))
		set_alarm(1.5, 0.0, "special_candy", TP);
}
