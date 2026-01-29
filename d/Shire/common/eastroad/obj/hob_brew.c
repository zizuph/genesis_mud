inherit "/std/drink";

#include <composite.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

#define MANA_DROP_ELSE		 50
#define HEAL_ELSE  			100
#define MANA_DROP_HOBBIT	120
#define HEAL_HOBBIT			300

create_drink()
{
	set_soft_amount(330);	// 0.33 Ltr
	set_alco_amount(33);	// 10% alco
	set_name("bottle");
	add_name("brew");
	set_pname(({"bottles", "brews"}));
	set_adj("wonderful");
	set_short("bottle of a wonderful smelling brew");
	set_pshort("bottles of a wonderful smelling brew");
	set_long(
		"This is a bottle of Bree Brew, from the famous guesthouse "+
		"' the Prancing Poney'. smelling it you fell like drinking it "+
		"all up in one ig mouth!\n");
}

int
drink_one_thing(object ob)
{
	if (!::drink_one_thing(ob))
		return 0;

	if (TP->query_race_name() == "human" || TP->query_race_name() == "hobbit")
	{
		write("Yummy, just what you needed to cool yourself.\n");
		say(QCTNAME(TP)+" throws in some Bree special brew with delight in "+HIS_HER(TP)+" eyes.\n");
		TP->command("burp");
		TP->heal_hp(HEAL_HOBBIT);
		TP->add_mana(MANA_DROP_HOBBIT);
		return 1;
	}
}
