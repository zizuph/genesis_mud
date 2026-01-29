#pragma save_binary
#pragma strict_types

inherit "/std/monster.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

public void
create_monster()
{
    set_name("gayryn");
    add_name(({"bartender", "barkeeper", "keeper", "barkeep" }));
    set_race_name("human"); 
    set_adj("unshaved");
    set_title("the bartender");
    add_adj(({"fat", "big", "smiling", }));

    set_long("He's a big fat generally smiling bartender.\n");

    default_config_npc(55);
    set_base_stat(SS_CON, 65);
    set_alignment(160);

    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_HEIGHT, 1730);
    add_prop(CONT_I_VOLUME, 100000);

    set_skill(SS_UNARM_COMBAT, 45);
    set_skill(SS_WEP_CLUB,     55);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_PARRY,   40);

    set_skill(SS_TRADING, 50);
    set_skill(SS_AWARENESS, 80);

    seq_new("do_things");
    seq_addfirst("do_things",
	({"smile","say G'day folks! What can I do for you?",
	  "say May I tempt thee with a beer perhaps?","smile"}));
}

string query_nonmet_name() { return "human bartender"; }

public void
do_introduce(object tp)
{
    if (!present(tp, ENV(TO)))
        return;

    command("present me to "+tp->query_real_name());
}

public void
add_introduced(string str)
{
    if (TP->query_npc() || TP->query_met(query_name()))
        return;

    set_alarm(2.0, 0.0, &do_introduce(TP));
}

#if 0
sell(what, price, to) {
    object ob;
    int stat, modifyer;

    modifyer = 1;

    if (what == "?") {
	command("shrug");
	command("say Sorry, I don't keep such things in here.");
	return 1;
    }

    if (!to->query_wiz_level())
    {
        command("sigh");
        command("say I have no beverages of any kind.");
        command("say Styles hasn't made 'em yet.");
        return 1;
    }
    else
    {
        command("say Sorry, I doen't have drinks for wizards either.");
        return 1;
    }
}
#endif

public void
arm_me()
{
    seteuid(getuid(TO));

    clone_object("/d/Genesis/start/human/obj/bat")->move(TO);
    command("wield bat");

    clone_object("/d/Genesis/start/human/obj/apron")->move(TO);
    command("wear apron");
}

