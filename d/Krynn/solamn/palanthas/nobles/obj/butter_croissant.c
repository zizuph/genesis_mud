/* Mortis 12.2005
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
    set_amount(70);
    set_name("croissant");
    set_pname("croissants");
    set_adj(({"butter", "apricot", "glazed"}));
	set_short("butter croissant with apricot glaze");
    set_pshort("butter croissants with apricot glaze");
    set_long("The Mer-bakers have outdone themselves with this light, "
	+ "buttery pastry! This version is the butter-rich, flaky classic "
	+ "topped with a sweet, fruity apricot glaze.\n");
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
	if (!str || !parse_command(str, ({}), "[butter] 'croissant' / 'croissants' [with] [apricot] [apricots] "))
	return 0;

    TP->catch_msg("The smell of sugary apricot and butter croissant fills "
	+ "your nose.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " butter croissant "
	+ "with apricot glaze to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You bite through the apricot glazed butter croissant and get "
	+ "a taste of its classic croissant pastriescence.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches through the apricot glazed "
	+ "top of " + HIS(TP) + " butter croissant.\n", ({TO, TP}));
}
