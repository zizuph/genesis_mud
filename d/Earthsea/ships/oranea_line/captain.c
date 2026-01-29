#pragma strict_types

inherit "/d/Genesis/ship/captain.c";
inherit "/lib/trade";
inherit "/d/Earthsea/lib/width_height.c";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "/sys/filter_funs.h"
#include "defs.h"
inherit REMEMBER;

#define NUM sizeof(MONEY_TYPES)
#define ENV(xx) environment(xx)
#define TICKET ORANEA_LINE + "ticket"


object ship;

void
set_ship(object s)
{
    ship=s;
}

void
create_monster()
{
    set_name("dravid");
    add_name("captain");
    set_adj(({"thin", "ascetic"}));
    set_ticket(TICKET);
    add_prop(OBJ_M_NO_ATTACK, "You feel this man is "+
      "protected by the gods of Earthsea.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The spell falls "+
      "harmlessly on thin air.\n");
    set_chat_time(45);
    set_long(break_string("This man is tall and gaunt, having "+
	"hard-calloused hands. While muscular, he is quite thin and "+
	"gives the appearance of one who leads an ascetic life.\n", 70));



    set_living_name("_gont_port_oranea_captain");
    set_race_name("human");
    set_height("very tall");
    set_width("very thin");
    default_config_npc(60);
    set_skill(SS_SWIM,100);
    set_skill(SS_UNARM_COMBAT,45);
    set_skill(SS_DEFENCE,34);

    heal_hp(10000);
    set_hp(50000);


    set_alignment(200);

    config_default_trade();

    setuid();
    seteuid(getuid());

    trig_new("%w 'introduces' %s", "react_introduce");

    set_hp(50000);

    add_act("stares quietly into the distance.");


}


void
intro_hook(string str)
{
    command("introduce myself");
    command("bow");
}
void
add_introduced(string str)
{

    ::add_introduced(str);
    return;
}

void
init_living()
{
    add_action("buy", "buy");
}

int
buy(string str)
{
    object tp = this_player();
    object buy_ob;
    string what, for_c, get_c, change;
    int *result, m_res, price;

    price = 12;

    if (!str) 
    {
	notify_fail("Buy what?\n");
	return 0;
    }

    if(tp->query_average_stat()< 25)
    {
	command("say to "+ lower_case(tp->query_name()) + " "+
	  "You may ride for free. I have taken an oath of poverty.");
	command("emote smiles benevolently.");

	clone_object(TICKET)->move(tp);
	return 1;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;
    if (what != "ticket") 
    {
	notify_fail("I have no such thing for sale.\n");
	return 0;
    }


    buy_ob = clone_object(TICKET);
    if (!objectp(buy_ob))
    {
	notify_fail("I seem to be out of tickets.\n");
	return 0;
    }


    price = buy_ob->query_prop(OBJ_I_VALUE);



    result=pay(price,tp,for_c,0,0,get_c);
    if (sizeof(result)==1) {
	buy_ob->remove_object();
	return 0;
    }
    if (buy_ob->move(tp))
    {
	write("You drop the " + buy_ob->short() + " on the ground.\n");
	say(QCTNAME(tp) + " drops one " + buy_ob->short() +
	  " on the ground.\n");
	buy_ob->move(environment(tp));
    }
    else {
	write("You get your " + buy_ob->short() + ".\n");
	say(QCTNAME(tp) + " buys a " + buy_ob->short() + ".\n");
    }
    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
	write("You get " + change + " as change.\n");

    return 1;
}
