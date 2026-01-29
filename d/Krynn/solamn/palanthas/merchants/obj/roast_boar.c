/*
 * Food available from Green Twitch Inn in Palanthas.
 * Whole boar too large to consume.  Can be carved into
 * boar brains, boar head, boar heart, four boar legs,
 * twenty shredded boar meats, six boar chops.
 *
 * Mortis 01.2006
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <composite.h>
#include <wa_types.h>
#include "../../local.h"

inherit "/std/food.c";
inherit "/lib/keep";

public void
create_food()
{
    seteuid(getuid());

	set_amount(12000);
    set_name("boar");
    set_pname("boars");
    set_adj("whole");
	add_adj("roast");
    set_long("This whole, roast boar is dripping with its own juices, "
	+ "its dark brown skin concealing succulent meat within.  It's far "
	+ "too large for any ordinary mortal to consume at once.  You'll need "
	+ "to carve it before you can enjoy it.\n");
	add_prop(OBJ_I_WEIGHT, 1100);

}

void
init()
{
    ::init();
    ADA("smell");
	ADA("carve");
}

int
smell(string str)
{
	if (!str || !parse_command(str, ({}), "[whole] [roast] 'boar'"))
	return 0;

    TP->catch_msg("You smell " + short() + ".  The scent of "
	+ "freshly cooked, rotisserie style, roast boar fills your senses.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " " + short()
	+ " to " + HIS(TP) + " nose sniffing it for a moment as " + PRONOUN(TP)
	+ " inhales its scents.\n", ({TO, TP}));
    return 1;
}

void
special_effect(int n)
{
	write("You begin consuming " + short() + ", its juices and "
	+ "oils filling your mouth with the taste of freshly cooked, rotisserie "
	+ "style, roast boar.  Whoa!  How the hell did you eat a whole boar like "
	+ "that?!?\n");
	tell_room(E(TP), QCTNAME(TP) + " begins consuming " + HIS(TP) + " "
	+ short() + ", its juices spilling into " + HIS(TP) + " mouth and "
	+ "filling the air with the scent of freshly caught, rotisserie style, "
	+ "roast boar.  Whoa!  How the hell did " + HE(TP) + " eat a whole "
	+ "boar like that?!?\n", ({TO, TP}));
}

int
carve(string str)
{
	NF("Carve what?\n");

	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[whole] [roast] 'boar'"))
		return 0;

	object food;
	string wname;
	object *wep = TP->query_weapon(-1);

	if (sizeof(wep) == 0)
	{
		write("What did you think?  That you could carve this boar with "
		+ "your bare hands???\n");
		say(QCTNAME(TP) + " considers ways to rip " + HIS(TP) + " whole, "
		+ "roast boar apart with " + HIS(TP) + " bare hands.\n");
		return 1;
	}
	
	wname = wep[0]->short();
	
	write("You carve your whole roast boar a boar head, boar brains, "
	+ "boar heart, four boar legs, twenty shredded boar meats, and "
	+ "six boar chops with your " + wname + ".\n");
	say(QCTNAME(TP) + " carves " + HIS(TP) + " whole roast boar "
	+ "into a boar head, boar brains, boar heart, four boar legs, "
	+ "twenty shredded boar meats, and six boar chops with " + HIS(TP)
	+ " " + wname + ".\n");

	food = clone_object(MERCH + "obj/boar_head");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_brains");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_heart");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_leg");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_leg");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_leg");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_leg");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_meat");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_chops");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_chops");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_chops");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_chops");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_chops");
	food->move(TP);
	food = clone_object(MERCH + "obj/boar_chops");
	food->move(TP);

	int quant = num_heap();
	if (quant > 1)
	{
		quant--;
		set_heap_size(quant);
		return 1;
	}

	remove_object();
	return 1;
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
