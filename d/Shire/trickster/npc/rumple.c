/*
**   THis is the ALchemsit which distrubutes the Trickster mischief
**   The Maxium amount of items which can be given is 15 to a player
**   5 items up to a max of 3 of each type.   The amount a player get
**   is based on their Guildstat in The Trickster Guild using this
**    formula Guildstat/10 + 1 with the aforementioned max of 15.
*/

inherit "/std/monster";
inherit "/lib/trade";

#include "/d/Shire/trickster/trickster.h"
#include "/d/Shire/common/defs.h"
#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

#define NUM sizeof(MONEY_TYPES)  /* How many types of money do we use? */
#define TRICKED_ON_PROP "_played_some_nasty_trick_on_rumple_"
#define KIT_ID  "trickster_disguise_kit"
#define SNEEZEPRICE 25
#define ITCHPRICE   50
#define SMOKEPRICE 100
#define STINKPRICE 200
#define LAUGHPRICE 400
#define DISGUISEPRICE 500

int *charges = ({10,10,10,10,10});
int *price_arr = ({SNEEZEPRICE,ITCHPRICE,SMOKEPRICE,STINKPRICE,LAUGHPRICE});
int alarm_id, soul_id;
static string  pay_type, get_type, coin_pay_text, coin_get_text;
static int *money_arr;

/*  Prototypes */
void played_trick_on_me(object player);
void get_me_soul();
int can_afford(int price);
void introduce_me(string who);
void return_nude(object player);
void return_tgrin(object player);
void return_meet(object player);

void
create_monster()
{
    if (!IS_CLONE)
    {
	return;
    }
    set_name("rumple");
    add_name("alchemist");
    set_title("the Recalcitrant Trickster");
    set_race_name("human");
    set_gender(G_MALE);
    set_adj(({"short","intelligent"}));
    set_long("This alchemist has been hired by the Tricksters to " +
      "create and distribute various alchemical devices to aid members " +
      "in having fun at other peoples expense.\n");
    set_stats(({80,80,80,105,105,65,0,0,90}));
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE,      63);
    MAKE_MONEY;
    set_alignment(0);

    add_prop(CONT_I_WEIGHT, 65*1000);
    add_prop(CONT_I_HEIGHT, 165);

    add_ask(({"disguise","disguises","disguise kit","kit"}),
      "@@give_out_disguise@@", 1);
    set_chat_time(5 + random(6));
    add_chat("Do you want me to outfit your stick?");
    add_chat("Renegrato quilocum nomenclatura!");
    add_chat("I can't wait till I perfect my latest creation!");
    add_chat("Will you hurry up!!  I don't have all day!");
    add_chat("Work, work, work is all I ever do!");

    set_cchat_time(3);
    add_cchat("You dare you attack a poor old man like myself!");
    add_cchat("I will turn you into a newt for attacking me!");
    add_cchat("Your regret the day you messed with this alchemist!");
    add_cchat("You are a coward for attacking an unarmed man!");



    soul_id = set_alarm(2.0,0.0,&get_me_soul());
    /* Set up the trading system */
    config_default_trade();

    /*                       Copper Silver Gold Platinum */
    set_money_give_out(   ({ 10000,   700,  10,   10}));  /* Max pay */
    set_money_give_reduce(({     0,     0,   0,    0})); /* Thershold */
}


void
get_me_soul()
{
    TO->add_cmdsoul(TRICKSTER_GUILD_SOUL);
    TO->update_hooks();
    remove_alarm(soul_id);
}

string
give_out_disguise()
{
    if (present(KIT_ID,TP))
	return "say You already got one!! Why should I give you "+
	"another?";
    if (!IS_MEMBER(TP))
	return "say How did you get in here?  Leave this place at once!";

    setuid(); seteuid(getuid());
    clone_object(DISGUISE_KIT)->move(TP);
    return "say Here is the disguise kit you asked for, "+TP->query_name()+".";
}

//  The following two functions are here to simulate the functions
//  Called by the Trickster_soul when it uses powders... so in
//  other words they are here to simulate the ones found in the
//  Trickster shadow.
nomask public int
query_charge(int index)
{
    return charges[index];
}

nomask public void
remove_charge(int index)
{
    charges[index] -= 1;
}

void
init_living()
{
    ::init_living();
    add_action("do_outfit","outfit");
}

int
do_outfit(string str)
{
    int count, guildstat, i, numcharge, price, times;
    int *max = ({0,0,0,0,0});
    object kit;

    if (!(IS_MEMBER(TP)))
    {
	command("itchpowder " + TP->query_real_name());
	command("say You don't belong here!   No get out before I turn you "+
	  "into a newt!\n");
	return 1;
    }
    if (!str)
    {
	NF("Outfit what?  Your head with a new brain perhaps?\n");
	return 0;
    }
    if (str == "head" || str == "head with brain" || str == "head with new brain")
    {
	command("bonk " + TP->query_real_name());
	command("say Don't get smart with me!");
	return 1;
    }
    if (TP->query_prop(TRICKED_ON_PROP))
    {
	command("say Bugger off!");
	command("say I will not sell anything to the likes of you!");
	command("hotfoot "+TP->query_real_name());
	command("say Now leave here at once!");
	return 1;
    }
    if (sscanf(str, "stick and get %s",get_type) != 3)
    {
	get_type = "";
	if (str != "stick")
	{
	    if (str == "kit")
	    {
		kit = present(KIT_ID,TP);
		if (!kit)
		{
		    NF("You don't have a kit to store your disguise material in!\n");
		    return 0;
		}
		guildstat = TP->query_stat(SS_LAYMAN);
		times = (guildstat/50) + 1;
		times -= kit->query_disguises();
		if (!times)
		{
		    NF("But you carry all the disguise material you can!\n");
		    return 0;
		}
		price = DISGUISEPRICE * times;
		if (can_afford(price))
		{
		    command("tgrin");
		    command("say Here you go "+TP->query_nonmet_name()+", hope "+
		      "you enjoy yourself and fool all the crusaders!!");
		    kit->add_disguises(times);
		    return 1;
		}
		else
		{
		    command("say I'm sorry but you can't afford to pay for your "+
		      "disguise material at the moment.");
		    command("say Come back when you have more money.");
		    command("tsmile misch");
		    return 1;
		}
		return 1;
	    }
	    NF("Type 'outfit stick' to outfit your stick, silly!\n");
	    return 0;
	}
    }
    guildstat = TP->query_stat(SS_LAYMAN);

    times = (guildstat/10) + 1;
    if (times > 15)
	times = 15;
    for (i = 0; i < times; i++)
    {
	max[count] += 1;
	if (count < 4)
	    count += 1;
	else
	    count = 0;
    }
    price = 0;

    for (i = 0; i < sizeof(max); i++)
    {
	numcharge = max[i] - (TP->query_charge(i));
	price += (numcharge * price_arr[i]);
    }
    if (price == 0)
    {
	command("bonk " + TP->query_real_name());
	command("say Quit wasting my time!!  Your stick does not need "+
	  "more outfitting!  Now leave me alone!");
	return 1;
    }
    if (can_afford(price))
    {
	TP->catch_msg(QCTNAME(TO)+" quicky grabs your stick from your hand, "+
	  "he then starts to tinker with it, adding various things.  He then "+
	  "promptly returns your stick to you, having completed his work.\n");
	say(QCTNAME(TO)+" grabs a stick from the hand of "+QCTNAME(TP)+" and "+
	  "starts to tinker around with the stick.  "+QCTNAME(TO)+"  then "+
	  "returns the stick it's rightful owner, having completed his work.\n");
	switch (random(3))
	{
	case 0:
	    command("tgrin");
	    break;
	case 1:
	    command("say Have fun spreading that Trickster Mischief!");
	    command("tsmile");
	    break;
	case 2:
	    command("say I wish I could see the face of who you play these tricks on.");
	    command("pout");
	    break;
	}
	TP->set_charges();
	return 1;
    }
    else
    {
	command("tlaugh");
	command("say Nice try...  But you can't pull that one on me!");
	command("say You need "+price+" copper coins if you want me to "+
	  "outfit your stick.");
	return 1;
    }
}

int
can_afford(int price)
{
    if (sizeof(money_arr = pay(price, TP, 0, 0, 0, get_type)) == 1)
	return 0;

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

    write("You pay the alchemist "+coin_pay_text+".\n");
    if (coin_get_text)
	write("You get "+coin_get_text+" in return.\n");
    return 1;
}

//   Some trigger feelings to make this NPC more vivid.


int
add_introduced(string name)
{
    alarm_id = set_alarm(3.0,0.0,&introduce_me(name));
    return 1;
}

void
introduce_me(string who)
{
    object obj;

    if (obj = present(who, environment()))
    {
	command("introduce myself");
	switch (random(3))
	{
	case 0:
	    command("meet " +who);
	    command("say Nice to meet a fellow Trickster.");
	    break;
	case 1:
	    command("say Hullo there "+ obj->query_name() +"!");
	    break;
	case 2:
	    command("bonk " +who);
	    command("say Hurry up and finish your bussiness here, I'm in a hurry "+
	      "you slow poke!");
	    break;
	}
    }
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    switch(emote)
    {
    case "hex": case "itchpowder": case "stinksplash": case "hotfoot": case "laughgas": case "sneezepowder":
	set_alarm(1.0,0.0,&played_trick_on_me(actor));
	break;
    case "meet":
	set_alarm(1.0,0.0,&return_meet(actor));
	break;
    case "nude":
	set_alarm(1.0,0.0,&return_nude(actor));
	break;
    case "tgrin": case "tsmile":
	set_alarm(1.0,0.0,&return_tgrin(actor));
	break;
    }
}

void
played_trick_on_me(object player)
{
    string name = player->query_real_name();

    if (!present(player, ENV(TO)))
	return;
    if (!player->query_prop(TRICKED_ON_PROP))
	player->add_prop(TRICKED_ON_PROP, 1);
    switch(random(7))
    {
    case 0:
	command("say How dare you do such a thing to me!");
	command("say Leave here at once before I turn you into a newt!");
	command("wigg "+name);
	break;
    case 1:
	command("sigh depres");
	command("say Why do people always play tricks on me?");
	command("say What did I ever do to you?");
	command("cry "+name);
	break;
    case 2:
	command("grumble ang");
	command("itchpowder "+name);
	command("say That will teach you some manners!");
	break;
    case 3:
	command("scream");
	command("say Oh my dear "+player->query_nonmet_name()+", you'll "+
	  "pay for that insult!");
	command("kill "+name);
	break;
    case 4:
	command("say Nice trick, but I like this one better");
	command("tgrin");
	command("stinksplash "+name);
	break;
    case 5:
	command("hex "+name);
	command("tlaugh "+name);
	command("say to "+name+" Boy do you look ridiculious!");
	break;
    case 6:
	command("say I don't have to put up with this!");
	command("smokebomb");
	command("say I'm outta here");
	set_alarm(2.0,0.0,remove_object);
	break;
    }
}

void
return_meet(object player)
{
    string name = player->query_real_name();

    switch(random(4))
    {
    case 0:
	command("say Ouch!!!");
	command("emote yanks his hand back in obivious pain.");
	break;
    case 1:
	command("tgrin cold "+name);
	command("meet "+name);
	command("say Enjoy a taste of your own medicine!!");
	break;
    case 2:
	command("say Nice to meet you "+player->query_nonmet_name()+".");
	break;
    case 3:
	command("say Do that again my dear "+player->query_race()+" and I shall "+
	  "melt that tack and your hand along with it!!");
	command("tcackle");
	command("twinkle misch");
	break;
    }
}

void
return_tgrin(object player)
{
    string name = player->query_real_name();

    switch(random(3))
    {
    case 0:
	command("say What devious plan have you invented my dear "+
	  player->query_nonmet_name()+"?");
	command("eyebrow "+name);
	break;
    case 1:
	command("peer nerv");
	command("say What are you up to "+player->query_nonmet_name()+"?");
	break;
    case 2:
	command("scratch");
	command("say Please finish your business here and leave at once.");
	break;
    }
}

void
return_nude(object player)
{
    string name = player->query_real_name();

    switch(random(3))
    {
    case 0:
	command("gasp");
	command("blush");
	command("emote picks up his pants from the ground and prompty wears them.");
	break;
    case 1:
	command("scowl "+name);
	command("hex "+name);
	command("say Take that your pervert!");
	break;
    case 2:
	command("grumble");
	command("search here for his pants");
	break;
    }
}
