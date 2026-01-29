/* created by Aridor 06/19/93 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit "/lib/trade";

inherit AM_FILE
inherit AUTO_TEAM

#define PLAYER_I_BOUGHT_CRYSTALS  "_player_i_bought_crystals"

void
create_krynn_monster()
{

    set_pick_up_team(({"minotaur"}));
    set_max_team_size_auto_join(3);
    set_name("t'nahcrem");
    add_name("merchant");
    set_race_name("human");
    set_adj("rich");
    add_adj("confident");
    set_short("confident rich merchant");
    set_long("Before you stands a merchant draped in fineries. His " +
      "shrewd gaze and expensive robe mark him as a merchant who is quite successful. " +
      "Perhaps if you ask him about his wares, he might sell you something.\n");
    add_ask("wares",VBFC_ME("return_wares"));
    set_stats(({120,80,130,70,80,92}));
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENSE,65);
    set_skill(SS_AWARENESS,75);
    set_skill(SS_PARRY,45);
    set_introduce(1);
    set_alignment(1000);
    set_knight_prestige(-20);
    set_title("the Wealthy Merchant of Ergoth");
    set_act_time(3);
    add_act("emote ponders the costs of transporting goods to Palanthus.");
    add_act("say I am a collector of fine works, and often come into " +
      "possession of some very interesting items.");
    add_act("say I am so rich. I own an island off Sancrist.");
    add_act("emote smiles wealthily.");
    add_act("say The rich mens club is a bit of a joke. Their combined " +
      "wealth I could make in a day!");
    add_act("say During my younger, and poorer, days, I used to live " +
      "in Flotsam.");
    add_act("say My bodyguards cost a fortune, but are worth every " +
      "penny.");
    set_cact_time(1);
    add_cact("shout Scum!");
    add_cact("say You will pay for this dearly!");
    add_cact("say Get out of here!");
    config_default_trade();
}


void
arm_me()
{
    object arm, wep;
    seteuid(getuid(TO));
    clone_object(KOBJ + "weapon/rapier")->move(TO);
    clone_object(KOBJ + "armour/m_armour")->move(TO);
    clone_object(KOBJ + "armour/robe")->move(TO);
    MONEY_MAKE_PC(2)->move(TO);
    MONEY_MAKE_GC(6)->move(TO);
    MONEY_MAKE_SC(12)->move(TO);
    command("wear all");
    command("wield all");
}


string
return_wares()
{
    return "The " +short()+" says: I usually only deal with those " +
    "people I like, as my wares are rare and in great demand. At " +
    "the moment, most of my goods are on their way to Palanthus, " +
    "as rumours of the dragonarmy heading this way has been bad for " +
    "business. Still, I do have a few blue-tinged crystals in stock. " +
    "I'd be willing to part with a bag of them for 12 platinum " +
    "coins. Simply buy them " +
    "if you want them.\n";
}

void
init_living()
{
    add_action("do_buy","buy");
    init_team_pickup();
    ::init_living();
}


int
do_buy(string str)
{
    int int_str, value, *money_arr;
    string pay_type, get_type, coin_pay_text, coin_get_text;
    object item;
    if(str == "crystals" | str == "bag of crystals" | str == "bag" | str == "pouch" | str == "blue-tinged crystals")
    {
	if(TP->query_prop(PLAYER_I_BOUGHT_CRYSTALS))
	{
	    NF("The confident rich merchant says to you: Sorry, I have only enough stock for " +
	      "one bag per customer.\n");
	    return 0;
	}
	item = clone_object(KOBJ + "pouch");
	clone_object(KOBJ + "scry_crystal")->move(item,1);
	clone_object(KOBJ + "scry_crystal")->move(item,1);
	clone_object(KOBJ + "scry_crystal")->move(item,1);
	clone_object(KOBJ + "scry_crystal")->move(item,1);
	clone_object(KOBJ + "scry_crystal")->move(item,1);
	value = 20736;
	TP->add_prop(PLAYER_I_BOUGHT_CRYSTALS,1);
    }
    else
    {
	NF("Simply buy crystals.\n");
	return 0;
    }
    item->add_prop(OBJ_I_VALUE,value);        
    if (sizeof(money_arr = pay(value, TP, pay_type, 0, 0, get_type)) == 1)
	return 0;
    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
	sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay the merchant " +coin_pay_text+ ".\n");
    if (coin_get_text)
	write("You get " + coin_get_text + " in return.\n");
    say(QCTNAME(TP) + " buys a pouch of something from the merchant.\n");
    if(item->move(TP))
    {
	write("You get your "+item->short()+", but its too heavy, and drop it.\n");
	item->move(E(TP));
	return 1;
    }
    write("You get your "+item->short()+".\n");
    if(str == "4")
	command("say That, my friend, brings good luck!");
    return 1;
}

