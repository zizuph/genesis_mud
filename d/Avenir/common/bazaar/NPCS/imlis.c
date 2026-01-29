// Lapidis      /d/Avenir/common/bazaar/NPCS/lapidis.c
// creator(s):  Zielia & Lucius, May 2007
// last update: 
//      May '07: Updated to add purses and a small quest to
//               introduce players to the ziggurat being open.
// purpose:     To be shopkeeper for the lapidary shop.
// note:  Original by Lilith, Dec 1997
// bug(s):
// to-do:
#pragma strict_types

#include <money.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../bazaar.h"
#include "/d/Avenir/include/guilds.h"

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/logrotate";

#define IMLIS_I_QUEST   "__imlis_i_questing"

private void sequence(mixed *seq);
private string order_help(string str);
private string offer_help(string str);

private static int alarm, busy;

private string
ask_quest(void)
{	
    if (busy)
	return "emote appears too busy to answer you.";

    if (TP->query_prop(IMLIS_I_QUEST))
	return "say I thought you were making a delivery for me. I hope "+
	    "you didn't lose the dust I gave you.";

    sequence(({"say to "+ OB_NAME(TP) +" Thank the Idrys! I was praying "+
        "I'd find someone to help me.", "say Ever since I started making "+
    	"these beautiful money purses, I've been too busy to keep up with "+
    	"my deliveries.", "say I was supposed to take some gem dust to "+
    	"Lyrelle in the Ziggurat, but I just haven't had time.", "say They "+
    	"say Lyrelle is not someone you want to make angry either.", "say "+
    	"She looks nice until she slips you an exploding soap!", 
    	"say If you can deliver this to her, I'd be so relieved.",
    	"give dust to "+ OB_NAME(TP)}));
 
    TP->add_prop(IMLIS_I_QUEST, 1);    	
    	   
    object dust = clone_object(CITY + "zigg/obj/dust");
    dust->move(TO, 1);
    
    return "";    	
}

private string
ask_zig(void)
{
    if (busy)
	return "emote appears too busy to answer you.";

    return "say The Pleasure Palace. In the Forbidden City.";     
}

private string
ask_lyrelle(void)
{
    if (busy)
	return "emote appears too busy to answer you.";

    return "say She makes wonderful cosmetics, including some lotions that "+
      "include my left over gem dust.";     
}

public void
create_monster(void)
{
    set_name("imlis");
    set_title("icu Sisaer, Sybarite Gemologist");
    add_name(({"shopkeeper","keeper"}));
    set_race_name("gnome");
    set_gender(G_MALE);
    set_adj("slender");
    add_adj("myopic");
    set_long("A gnome of indeterminate age with the myopic eyes " +
      "of one who spends hours staring at small items. He " +
      "is a gemologist well-known for his talents and fair-"+
      "dealing.\n");

    set_act_time(50);
    add_act("emote studies a gem under the lens.");
    add_act("emote lovingly polishes a gemstone.");
    add_act("emote taps a tool against a gem.");
    add_act("emote seems engrossed in his work.");
    add_act("emote holds a gem up to the light.");
    add_act("smile soft");
    add_act("emote carefully scrapes some gemdust into a pouch.");
    add_act("emote measures out some fabric for a money purse.");
    add_act("emote sews a finely-cut gem onto a money purse.");
    add_act("emote frets about being behind on his deliveries.");

    set_all_hitloc_unarmed(50);

    set_stats(({70,70,70,70,70}));

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_WEP_POLEARM,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);

    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(OBJ_M_HAS_MONEY, ({ 0, random(10), }));

    set_alignment(0);
    set_knight_prestige(-1);

    set_mm_in("arrives.");
    
    add_ask(({"quest","task","help","job","delivery","deliveries"}),
	ask_quest, 1);
    add_ask(({"ziggurat","Ziggurat",}), ask_zig, 1);      
    add_ask(({"lyrelle", "Lyrelle"}), ask_lyrelle, 1);         
      
    add_ask(({"purse","purses","money-purse","money-purses"}),
      &order_help("purse"), 1);
    add_ask(({"material","materials",}),
	&order_help("material"), 1);
    add_ask(({"order","orders","ordering",}),
      &order_help("order"), 1);
    add_ask(({"price","prices","pricing",}),
      &order_help("price"), 1);
    add_ask(({"offer","upgrade","upgrading",}),
      &offer_help("offer"), 1);
}

/* Called by fix_keeper() in the shop. */
public void
arm_me(void)
{
    object cloak;

    setuid();
    seteuid(getuid());

    clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);

    cloak = clone_object(BAZAAR + "Obj/worn/mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    command("wear all");
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
public void
check_meet(object tp)
{
    string occ;
    int i = random(6);

    /* reset meet alarm */
    alarm = 0;

    if (busy || !present(tp, environment(TO)))
	return;

    if (tp->query_prop("_is_cat_"))
    {
	command("ack");
	command("shouts: NO CATS IN HERE!");
	command("emote says to his assistant: Get the butcher!");
	return;
    }

    occ = tp->query_guild_name_occ();

    if (occ == OUNION)
    {
	if (i == 2)
	    command("bow respect "+ tp->query_real_name());
	else if (i == 4)
	    command("say to "+ tp->query_real_name() +" I am "+
	      "honoured by your patronage!");
	else if (i == 5)
	    command("say to "+ tp->query_real_name() +" May I sell "+
	      "you a gem?");
    }
    else if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
	if (i == 0)
	    command("smile respect "+ tp->query_real_name());
	else if (i == 4)
	    command("bow "+ tp->query_real_name());
    }       
    else
    {
	if (i == 3)
	    command("say Welcome! Are you here to buy gems or sell them?");
    }
}

/*
 * The order command for the acquisition of the new
 * and highly improved coin/gem purses follows.
 */

/* Used to spit out stuff. */
private void
sequence(mixed *seq)
{
    int idx = 1;
    float delay = 2.0;

    busy = 0;

    if ((sizeof(seq) > 2) && floatp(seq[1]))
    {
	idx = 2;
	delay = seq[1];
    }

    if (sizeof(seq) > 1)
	busy = set_alarm(delay, 0.0, &sequence(seq[idx..]));

    if (stringp(seq[0]))
	command(seq[0]);
    else if (functionp(seq[0]))
	seq[0]();
}

private string
order_help(string str)
{
    if (!strlen(str))
	return "";

    switch(str)
    {
    case "help":
    case "purse":
    case "money-purse":
	/* Some help info... */
	sequence(({
	    "say I am rather proud to be able to present the newest "+
	    	"addition to my shop, money-purses!",
	    "say They can be ordered in a variety of materials, just "+
	    	"ask me about 'materials' for a listing.",
	    "say However, in an attempt to force good taste upon my "+
	    	"clientele, I limit everyone to a single gem type of choice.",
	    "say You may, of course, use as many of that type of gem "+
	    	"as you like.",
	    "say And the more you use, the more luxuriant and opulent "+
	    	"and larger your purse will be.",
	    "say Lastly, I do necessitate a minimum of 10 gems to make "+
	    	"the process at least worth my while.",
	    "say Ask me about 'ordering' if you think you are interested.",
	    "say Oh, and I'll even give you a deal if you 'offer' up an "+
	    	"existing purse for an upgrade.",
	    2.0,
	    "say That offer is only valid if the gems are the same though!",
	    2.0,
	    "smile helpfully",
	  }));
	break;

    case "material":
    case "materials":
	/* Some help info... */
	sequence(({
	    "say Admittedly, my selection is a touch limited since "+
	    	"I rely on Havec for my supplies, but I do have a "+
	    	"few options for you:",
	    "say The first and simplest material to choose from is felt, "+
	    	"which is a non-woven fibre made from the finest wool "+
	    	"of our own sybarun goats.",
	    "say Next, I can offer you a velvet material, which is woven "+
	    	"from our very own sybarun silks.",
	    2.0,
	    "say My velvet purses are soft, durable and water-repellant.",
	    "say Next up I have a leather material, which is from the "+
	    	"tiny deer upon the Holm of the Icondite.",
	    2.0,
	    "say The leather is tanned, which gives it a colour and "+
	    	"suppleness greater than the more common sybarun goat "+
	    	"leather.",
	    "say My final offering is the sybarun exclusive material, "+
	    	"webcloth, which if you aren't already aware, is a much "+
	    	"finer, lighter and stronger material than silk.",
	    "say For now, those are all the choices I have to offer you.",
	    2.0,
	    "gesture apologetically",
	  }));
	break;

    case "order":
    case "orders":
    case "ordering":
	/* Some help info... */
	sequence(({
	    "say Ordering is actually quite simple and done through "+
	    	"the simple exchange of ideas within a single command.",
	    "say Issue a statement along these lines:",
	    2.0,
	    "say > order <material> <number of gems> <gem type>",
	    "say Make sure you have the appropriate amount of gems "+
	    	"of the type you desire at-hand when placing your order!",
	    "say And that amount should not include the amount being "+
	    	"credited on any offered purses.",
	    "say I also don't do this for free, so ask me about pricing "+
	    	"before you make any decisions.",
	    2.0,
	    "smile helpfully",
	  }));
	break;

    case "price":
    case "prices":
    case "pricing":
	/* Some help info... */
	sequence(({
	    "say My pricing isn't for the faint of heart, but you are "+
	    	"guranteed a good product.",
	    2.0,
	    "say The first tier is for under 100 gems, and that's 500 "+
	    	"platinum.",
	    2.0,
	    "say At 100, it's another 500 platinum, for 1000 total.",
	    "say And easily enough, each 100 gems adds another 500 "+
	    	"platinum to the cost.",
	    "say After 500 gems, however, you don't gain anything more "+
	    	"for your money, so be forewarned.",
	    2.0,
	    "gesture explanatorily",
	}));
	break;
    default:
	return "shrug helpless";
    }

    return "";
}

/* Attempt to safely transfer a purse to its new owner. */
private void
transfer_purse(object ob, object to)
{
    /* No purse! */
    if (!objectp(ob))
    {
	sequence(({
	    "say Oops, something happened to your new purse "+
	    	"and I don't know what.",
	    2.0,
	    "say You should report this.",
	}));

	return;
    }

    /* No buyer! */
    if (!objectp(to))
    {
	sequence(({
	    "peer thoughtfully",
	    2.0,
	    "shrug indifferently",
	}));

	ob->remove_object();
	return;
    }

    /* Force if necessary. */
    if (ob->move(to))
	ob->move(to, 1);

    if (present(to, ENV(TO)))
    {
	command("say All finished, and here is your new purse.");

	tell_object(to, TO->query_The_name(to) +" hands you "+
	    LANG_ADDART(ob->real_short()) +".\n");
	tell_room(ENV(to), QCTNAME(TO) +" hands "+
	    LANG_ADDART(ob->real_short()) +" to "+ QTNAME(to) +".\n",
	    ({ TO, to }), TO);
    }
    else
    {
	tell_object(to, "A panting urchin runs up to you and shoves "+
	    LANG_ADDART(ob->real_short()) +" into your hands "+
	    "then takes off.\n");
	tell_room(ENV(to), "A panting urching runs up to "+ QTNAME(to) +
	    " and shoves "+ LANG_ADDART(ob->real_short()) +" into "+
	    to->query_possessive() +" hands then takes off again.\n",
	    ({ to }), to);
    }

    logrotate("/d/Avenir/log/bazaar/purses",
	time2format(time(), "mmm dd yyyy tt: ") +
	to->query_cap_name() +" purchased: "+ ob->real_short() +"\n");
}

/*
 *       RMC PRICES       |        OUR Prices
 * -----------------------|-----------------------------
 *   200/200  == leather  |   500 == small     < 100
 *   400/600  == silver   |  1000 == medium    < 200
 *   800/1400 == gold     |  1500 == large     < 300
 *  1600/3000 == diamond  |  2000 == huge      < 400
 *  3200/6200 == ruby     |  2500 == enormous  < 500
 *                        |  3000 == exorbitant  >= 500
 */
public int
calc_price(int num)
{
    return (((num / 100) + 1) * 500);
}

/* Offers for purse upgrades.
 *
 * offers = ([ (object)Player : ({
 *      (object)Purse,
 * 	(string)Purse desc,
 * 	(string)Gem ID,
 * 	(string)Gem File,
 * 	(int)Amount of gems,
 * 	(int)Calculated value,
 *    }),
 * ])
 */
private static mapping offers = ([
]);

/* Supported material types for purses. */
private static string *mats = ({
	"felt", "velvet", "leather", "webcloth",
});

public int
f_order(string str)
{
    int num;
    string mat, gem;

    if (!strlen(str))
	return NF("What are you trying to order?\n");

    if (busy)
	return NF("They appear too busy to help you at the moment.\n");

    /* See if they want help. */
    if (!strlen(order_help(str)))
	return 1;

    /* Basic string check. */
    if (sscanf(str, "%s %d %s", mat, num, gem) != 3)
	return NF("Syntax: order <material> <number> <gem>\n");

    /* Not a material we offer. */
    if (!IN_ARRAY(mat, mats))
    {
	sequence(({
	    "say Unfortunately, I cannot fulfill that material "+
	    	"choice.",
	    2.0,
	    "say I can only offer the following:",
	    1.0,
	    "say "+ COMPOSITE_WORDS_WITH(mats, "or") +".",
	  }));

	return 1;
    }

    /* Look for gems to parse. */
    object *obs = filter(all_inventory(TP), &->query_gem());

    if (!sizeof(obs))
    {
	write("You don't even have any gems at the ready!\n");
	return 1;
    }

    /* Parse them for a match. */
    str = num +" "+ gem;
    if (!parse_command(str, obs, "%i", obs))
    {
	/* Convert singular to plural (we require plural). */
	str = num +" "+ LANG_PWORD(gem);
	if (!parse_command(str, obs, "%i", obs))
	{
	    return NF("Could not locate the gemstone specified.\n"+
	      "Syntax: order <material> <amount of> <gems>\n");
	}
    }

    /* Parse it further. */
    obs = NORMAL_ACCESS(obs, 0, 0);

    /* No matches? */
    if (!sizeof(obs))
    {
	return command("say You don't seem to have the gems "+
	  "to cover that order.");
    }

    /* We require a single type of gemstone. */
    if (sizeof(obs) > 1)
    {
	sequence(({
	    "say I will only sew a money-purse comprised of "+
	    	"ONE type of gem.",
	    2.0,
	    "say Be more specific on your choice of gemstone.",
	  }));

	return 1;
    }

    int val = obs[0]->num_heap();

    /* Minimum amount is [arbitrarily] set at 10. */
    if (val < 10)
    {
	sequence(({
	    "say You don't have enough "+ obs[0]->query_pname() +".",
	    2.0,
	    "say I require at least 10.",
	  }));

	return 1;
    }

    /* Make sure what they specified is what they actually have. */
    if (num != val)
    {
	sequence(({
	    "say You specified "+ num +" "+
	    	obs[0]->query_pname() +" but I am only "+
	    	"seeing "+ val +".",
	    2.0,
	    "say To limit confusion, try a more exact amount.",
	  }));

	return 1;
    }

    int upgrade;

    /* Check if they are trying to upgrade. */
    if (offers[TP])
    {
	mixed tmp = offers[TP][0];

	/* They lost the purse they offered. */
	if (!objectp(tmp) || !present(tmp, TP))
	{
	    sequence(({
		"say You seem to have lost the purse you put up "+
			"for a discount offer.",
		2.0,
		"say As such, I'm cancelling this order and your "+
			"upgrade credit.",
		"say If you still wish a purse, try ordering again.",
	    }));

	    m_delkey(offers, TP);
	    return 1;
	}

	tmp = obs[0]->query_prop(HEAP_S_UNIQUE_ID);
	/* Make sure gem id's match. */
	if (tmp != offers[TP][2])
	{
	    sequence(({
		"say As you recall, I was most explicit in that I'll "+
			"credit you for the same type of gemstone.",
		"say What you're ordering with and what you've offered "+
			"are not the same.",
		2.0,
		"say Either correct your error, or cancel the offer and "+
			"try ordering again.",
		1.0,
		"tap briefly",
	    }));

	    return 1;
	}

	tmp = offers[TP][4];
	/* Must increase the gem count by at least 50. */
	if ((num + tmp) < ((tmp * 3) + 50))
	{
	    sequence(({
		"say I did state that I require a minimum 50 gem increase "+
			"to satisfy my credit offer.",
		"say Return when you have achieved that, else cancel "+
			"your offering and try ordering again.",
		1.5,
		"twiddle",
	    }));

	    return 1;
	}

	/* Have stuff in their purse. */
	if (sizeof(all_inventory(offers[TP][0])))
	{
	    sequence(({
		"say Hmm, you seem to still have items in your "+
			"current purse.",
		2.0,
		"say Empty it out and try ordering again.",
		1.0,
		"smile politely",
	    }));

	    return 1;
	}

	upgrade = 1;
	/*
	 * Increase 'val' by credited gems
	 * to get the correct pricing.
	 */
	val += offers[TP][4];
    }

    /* Get the price (in platinum). */
    val = calc_price(val);
    command("say That is going to cost you "+ val +" platinum.");

    if (upgrade)
    {
	int tmp = offers[TP][5];

	val -= tmp;

	/* Shouldn't be possible... */
	if (val < 0)  val = 0;

	command("say Minus your credit of "+ tmp +
	    ", for a total cost of "+ val +" platinum.");
    }

    /* Convert the price to coppers. */
    val *= MONEY_VALUES[3];

    /* Remove the money. */
    if (!MONEY_ADD(TP, -val))
    {
	sequence(({
	    "say Your eyes seem to be bigger than your bank account.",
	    2.0,
	    "say Come back when you can afford my prices.",
	    2.0,
	    "smile haughtily",
	}));

	return 1;
    }

    /* Should never happen.. */
    if (obs[0]->move(ENV(TO)))
    {
	sequence(({
	    "say Your gems don't wish to leave your hands, how unfortunate.",
	    "say Come back when your hands come unglued.",
	}));

	/* Give back the money. */
	MONEY_ADD(TP, val);
	return 1;
    }

    /* Increase the heap size by credited gems. */
    if (upgrade)
    {
	int tmp = offers[TP][4];

	obs[0]->set_heap_size(num + tmp);
	command("say I'll be sure to add in your "+ tmp +" credited gems.");
	tmp += num;
	command("say Thus, your new purse will have a total of "+
	   tmp +" "+ obs[0]->plural_short() +".");
    }

    object purse;

    /* Shouldn't happen either... */
    if (catch(purse = clone_object(OBJ + "purse")) ||
	!purse->setup_purse(mat, obs[0]))
    {
	sequence(({
	    "say I seem to have misplaced my purse-making materials...",
	    2.0,
	    "say I bet one of the Hegemon's helpers would like to know "+
	    	"about this.",
	    2.0,
	    "grumble unhappily",
	}));

	/* Reset heap size. */
	if (upgrade)
	    obs[0]->set_heap_size(num);

	/* Give back the money and gems. */
	obs[0]->move(TP);
	MONEY_ADD(TP, val);
	return 1;
    }

    obs[0]->remove_object();

    write(TO->query_The_name(TP) +" takes your coins and gems.\n");
    say(QCTNAME(TO) +" takes some coins and gems from "+
	QTNAME(TP) +".\n", ({ TP, TO }));

    if (upgrade)
    {
	object ob = offers[TP][0];

	write(TO->query_The_name(TP) +" then removes the "+
	    ob->real_short() +" from your care.\n");
	say(QCTNAME(TO) +" then removes the "+ ob->real_short() +
	    " from "+ TP->query_possessive() +" care.\n",
	    ({ TP, TO }));

	/* Must handle all loose-ends relating to the old purse
	 * now while the pointers are valid.  If the player stupidly
	 * quits in the next 30 seconds or so and loses old and new,
	 * well that's just tough luck.
	 */

	/* Hide the old purse. */
	ob->set_no_show();

	/* Force move if needed. */
	if (ob->move(ENV(TO)))
	    ob->move(ENV(TO), 1);

	/* Try to dest it. */
	ob->remove_object();
	/* If desting fails, no biggie, it's untouchable now. */

	/* Clone up some gems from the old purse and resell them. */
	if (!catch(ob = clone_object(offers[TP][3])) && objectp(ob))
	{
	    ob->set_heap_size(offers[TP][4]);
	    ob->move(ENV(TO)->get_store_object());
	}

	/* Upgrade complete. */
	m_delkey(offers, TP);
    }

    sequence(({
	"emote smiles avariciously.",
	1.5,
	"say Excellent, let me step into the backroom and get to work!",
	1.5,
	"excuse hurriedly",
	1.0,
	"storeroom",
	10.0,
	"shout Still working on it, be patient.",
	10.0,
	"shout Soon now.",
	8.0,
	"shout Almost done.",
	6.0,
	"shop",
	2.0,
	&transfer_purse(purse, TP),
    }));

    return 1;
}

private string
offer_help(string str)
{
    sequence(({
	"emote clears his throat.",
	2.0,
	"say You can 'offer' me an older purse you've purchased "+
	   "and in return, I'll credit you some of the value and "+
	"gems spent.",
	"say I will only apply them towards the creation of a larger "+
	   "purse made from the same type of gemstone.",
	"say Also, to cover the effort, I expect you to increase "+
	   "the gem count by a minimum of 50.",
	"say Changing the material type I'll allow.",
	"say You may also 'offer cancel' if you change your mind "+
	   "as well as 'offer check' to refresh your memory.",
	"say I also reserve the right to void your offer at any time.",
	1.5,
	"smile patiently",
    }));

    return "";
}

public int
f_offer(string str)
{
    int done = 1;

    if (!strlen(str))
	return NF("What are you trying to offer?\n");

    if (busy)
	return NF("They appear too busy to help you at the moment.\n");

    switch(str)
    {
    case "help":
    case "offer":
    case "upgrade":
    case "upgrading":
	/* Some help info... */
        offer_help(str);
	return 1;

    case "cancel":
	/* Cancelling an offer... */
	if (offers[TP])
	{
	    m_delkey(offers, TP);
	    command("say Very well, the credit offer for your purse "+
		"has been rescinded.");
	}
	else
	{
	    sequence(({
		"peer skeptically at "+ OB_NAME(TP),
		1.0,
		"say I would, but you've no offers to cancel!",
	    }));
	}
	break;

    case "check":
	/* Checking if anything on offer... */
	if (offers[TP])
	{
	    sequence(({
		"say Yes, yes.. I do recall one.",
		2.0,
	       	"say Currently I have "+ LANG_ADDART(offers[TP][1]) +
			" offered by you.",
		"say I'm crediting you for "+ offers[TP][4] +" of the "+
			"gems and about "+ offers[TP][5] +
			" platinum towards a new purse.",
		"say If you've changed your mind, you can 'offer cancel'.",
		1.5,
		"smile thinly",
	    }));
	}
	else
	{
	    command("say I don't have any offers on record for you.");
	}
	break;

    default:
	if (offers[TP])
	{
	    sequence(({
		"say You've already offered me an older purse.",
		2.0,
		"say You'll need to 'offer cancel' your current offering "+
			"before I'll consider a new one.",
	    }));
	}
	else
	    done = 0;
	break;
    }

    if (done)
	return 1;

    /* Look for gems to parse. */
    object ob, *obs = filter(all_inventory(TP), &->avenir_money_purse());

    if (!sizeof(obs))
    {
	write("You don't have a sybarun money-purse to offer!\n");
	return 1;
    }

    /* Parse them for a match. */
    if (!parse_command(str, obs, "[the] / [a] / [an] %o", ob))
	return NF("That does not appear to be a valid money-purse.\n");

    offers[TP] = ({
	ob, ob->short(),
	ob->query_gem_id(),
	ob->query_gem_file(),
	ob->query_gem_amount() / 3,
	calc_price(ob->query_gem_amount()) / 3,
    });

    sequence(({
	"tap thoughtf",
	2.0,
	"say Very well, I'll accept your offer for now.",
	2.0,
	"say I'll credit you for "+ offers[TP][4] +" of the gems "+
		"and about "+ offers[TP][5] +" platinum towards a new purse.",
	"say You can 'offer cancel' if you change your mind.",
	2.0,
	"say Also, 'offer check' if you are forgetful about offers "+
		"you've made.",
	"say This offer will be valid for as long as you are awake.",
	"smile cordially",
    }));

    return 1;
}

public void
init_living(void)
{
    ::init_living();

    /* handled below. */
    add_action( f_order, "order" );
    add_action( f_offer, "offer" );

    if (alarm || busy)
	return;

    if (interactive(TP) && CAN_SEE(TO, TP))
	alarm = set_alarm(2.0, 0.0, &check_meet(TP));        
}  

public void
seq_heartbeat(int steps)
{
    if (busy)
	return;

    ::seq_heartbeat(steps);
}

