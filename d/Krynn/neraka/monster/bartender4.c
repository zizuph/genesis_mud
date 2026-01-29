/* Bartender 4, by Nick */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/sys/money.h"
#include <macros.h>

inherit M_FILE

init_living()
{
    ADA("buy");
}

create_krynn_monster()
{
    int i;
    object money;

    set_name("bartender");
    add_name("pig face");
    set_short("pig faced bartender");
    set_long(BS(
        "This is the bartender of the guardians pub. He looks strong and " +
	"is used to taking care of himself. You can see that he is of human " +
	"race though his face looks like he were something else.", SL));
    set_pname("bartenders");
    set_race_name("human");
    set_adj("strong");
    for (i = 0; i < 6; i++)
        set_base_stat(i,60);
    set_alignment(-100);
    set_knight_prestige(400);
    set_gender(0);

    seteuid(getuid());

    money = clone_object("/std/coins");
    money->set_name("coin");
    money->set_pname("coins");
    money->set_heap_size(random(300));
    money->set_typ(MONEY_TYPES[0]);
    money->move(TO);

    ALWAYSKNOWN;

    set_all_attack_unarmed(25, 19);
    set_all_hitloc_unarmed(23);

}

buy(str)
{
    object beer;

    NF("Buy what?\n");
    if (!str || str!="beer")
        return 0;

/*
    NF("The bartender wants copper coins for a beer.\n");
    if (!present("copper coin", TP))
        return 0;
*/

    NF("You haven't got 12 copper coins to pay the beer with.\n");
    if (TOTAL_MONEY(TP) < 12)
        return 0;

    if (!MONEY_FN->take_money(TP, 12))
	return 0;

    write("You pay 12 copper for a beer.\n");

    beer = clone_object(OBJ + "guard_beer");
    if (beer->move(TP))
    {
	write("You drop the beer on the floor.\n");
	say(QCTNAME(TP) + " drops a beer on the floor.\n");
	beer->move(environment(TO), 1);
    } else
    {
	write("You get your beer.\n");
	say(QCTNAME(TP) + " buys a beer.\n");
    }

    return 1;
}
