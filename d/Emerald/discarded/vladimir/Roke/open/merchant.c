#include "/d/Roke/common/defs.h"
#include "/sys/money.h"
#include <macros.h>
inherit "/std/monster.c";
#include <stdproperties.h>


init_living()
{
    ADA("buy");
}

create_monster()
{
    int i;

    set_name("merchant");
    add_name("tall");
    set_short("palanthian merchant");
    set_long(BS("This is a merchant from far away Palanthas, who"
	+ " has just recently arrived. He seems to be selling a"
	+ " strange item for which he wants 1 gold coin.",70));
 
   set_race_name("human");

    for (i = 0; i < 6; i++)
        set_base_stat(i,70);
    set_alignment(-100);

set_hp(10000);

    NEVERKNOWN;

    set_all_attack_unarmed(25, 89);
    set_all_hitloc_unarmed(63);

    ::create_monster();

    seteuid(getuid(TO));
    MONEY_MAKE_GC(random(5) + 1)->move(TO);
}

buy(str)
{
    object item;

    if (!str || str!="item")
    {
        command("say I only sell items one at a time.");
        return 1;
    }

    if (!present("gold coin", TP))
    {
	command("say I demand one gold coin for the item.\n");
	return 1;
    }

    if (!MONEY_MOVE(1, "gold", TP, 0))
    {
	write("You pay 1 gold coin for a item.\n");
	item = clone_object(ATUAN + "cape/obj/stobj");
	if (item->move(TP))
	{
	    write("You drop the item on the ground.\n");
	    say(QCTNAME(TP) + " drops a item on the ground.\n");
	    item->move(environment(TO), 1);
	} else {
	    write("You get your item.\n");
	    say(QCTNAME(TP) + " buys a item.\n");
	}
	write("The merchant whispers to you: I would be careful with that.\n");
    }

    return 1;
}
