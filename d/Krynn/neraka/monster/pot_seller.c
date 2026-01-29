/* Potion seller, by Nick */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/sys/money.h"
#include <macros.h>

inherit M_FILE


void
init_living()
{
    ADA("buy");
}

void
create_krynn_monster()
{
    int i;

    set_name("merchant");
    set_adj("strange");
    add_adj("looking");
    set_short("strange looking merchant");
    set_long(BS(
        "When you look closer you are not sure if you see this person or " +
	"not. It's like he's fading away then to reappear, very strange. " +
	"However it seems he offers something for you to buy, a potion " +
	"for which he wants a gold coin.", SL));
    set_race_name("merchant");

    for (i = 0; i < 6; i++)
        set_base_stat(i,70);
    set_alignment(-100);

    set_knight_prestige(100);

    NEVERKNOWN;

    set_all_attack_unarmed(25, 89);
    set_all_hitloc_unarmed(63);


    seteuid(getuid(TO));
    MONEY_MAKE_GC(random(5) + 1)->move(TO);
}

int
buy(string str)
{
    object potion;

    if (!str || str!="potion")
    {
        command("say I only sell potions, one at a time.");
        return 1;
    }

    if (!present("gold coin", TP))
    {
	command("say I demand one gold coin for the potion.");
	return 1;
    }

    if (!MONEY_MOVE(1, "gold", TP, 0))
    {
	write("You pay 1 gold coin for a potion.\n");
	potion = clone_object(KRPOTION + "quenta");
	if (potion->move(TP))
	{
	    write("You drop the potion on the ground.\n");
	    say(QCTNAME(TP) + " drops a potion on the ground.\n");
	    potion->move(environment(TO), 1);
	}
	else
	{
	    write("You get your potion.\n");
	    say(QCTNAME(TP) + " buys a potion.\n");
	}
	write("The merchant whispers to you: I've made the potions " +
	      "stronger now! But they have a side effect...\n");
    }

    return 1;
}
