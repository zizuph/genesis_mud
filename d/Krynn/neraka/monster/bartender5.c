/* Bartender 5, by Nick */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>

inherit M_FILE

init_living()
{
    string str;

    ADA("buy");
    str = TP->query_race();
    if ((str == "dwarf") || (str == "hobbit") || (str == "gnome"))
      set_alarm(2.0,0.0,"throw_out", TP);
}

create_krynn_monster()
{
    int i;
    set_name("bartender");
    add_name("giant");
    set_short("giant bartender");
    set_long(BS(
        "This is the bartender of the Giants inn. He looks very big and " +
	"strong. He seems to have much to do tending to his fellow giants." +
	"",SL));
    set_race_name("giant");
    set_adj("giant");
    for (i = 0; i < 6; i++)
        set_base_stat(i,60 + random(20));
    set_skill(SS_DEFENCE, 100);

    set_alignment(-300);
    set_knight_prestige(500);
    set_gender(0);

    //ALWAYSKNOWN;

    set_all_attack_unarmed(49, 50);
    set_all_hitloc_unarmed(57);

    MONEY_MAKE_SC(13 + random(20))->move(TO);
}

buy(str)
{
    object beer;
    int *arr;

    if (str != "beer")
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    command("say You don't look like no Giant to me.");
    command("laugh");
    command("say Get lost you little bug.");
    write("You didn't get any beer.\n");
    say(QCTNAME(TP) + " obviously didn't manage to buy a beer.\n");

    return 1;
}

throw_out(ob)
{
    if (environment(ob) == environment(TO))
    {
	if (ob->query_invis())
	{
	    set_alarm(7.0,0.0,"throw_out", ob);
	    return ;
	}
	write("When the bartender sees you he screams:\n");
	say("The bartender spots " + QTNAME(ob) + " in the pub and cries:\n");
	tell_room(environment(TO), "  WHO LET THAT LITTLE MAGGOT IN HERE???\n");
	write("The bartender throws you out.\n");
	say("The bartender throws " + QTNAME(ob) + " out.\n");
	ob->move_living("north flowing through the air",
		TDIR + "city10", 1);
    }
}
