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
    set_amount(75);
    set_name("cookie");
    set_pname("cookies");
	add_name("nut");
	add_pname("nuts");
    set_adj(({"white", "choc", "chocolate", "macadamia", "nut"}));
	set_short("white chocolate macadamia nut cookie");
    set_pshort("white chocolate macadamia nut cookies");
    set_long("This enormous, round cookie perfectly pairs silky white "
	+ "chocolate chips with large chunks of rich macadamia nuts.\n");
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
	if (!str || !parse_command(str, ({}), "[white] [choc] [chocolate] [macadamia] [nut] 'nut' / 'nuts' / 'cookie' / 'cookies' "))
	return 0;

    TP->catch_msg("The smell of white chocolate and macadamia nut cookie "
	+ "fills your nose.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " white chocolate "
	+ "macadamia nut cookie to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You bite into your cookie getting a taste of its "
	+ "silky, white chocolate and large chunks of rich macadamia nuts.\n");
	tell_room(E(TP), QCTNAME(TP)+ " bites into " + HIS(TP) + " white "
	+ "chocolate macadamia nut cookie.\n", ({TO, TP}));
}
