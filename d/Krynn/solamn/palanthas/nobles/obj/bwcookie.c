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
    set_name("cookie");
    set_pname("cookies");
    set_adj(({"black", "and", "white"}));
	set_short("black and white cookie");
    set_pshort("black and white cookies");
    set_long("A soft, rich butter cookie that's been double-dipped -- half "
	+ "in rich melted chocolate icing, half in sweet white vanilla icing.\n");
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
	if (!str || !parse_command(str, ({}), "[black] [and] [white] 'cookie' / 'cookies' "))
	return 0;

    TP->catch_msg("The smell of icing and butter cookie fills your nose.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " black and white "
	+ "cookie to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch into a black and white cookie getting a taste of its "
	+ "sweet vanilla and chocolate icing and rich, butter cookie flavour.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches into " + HIS(TP) + " black "
	+ "and white cookie.\n", ({TO, TP}));
}
