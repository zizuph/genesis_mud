/* 
 * Base created by Aridor, 06/10/94, wep_smith
 * /d/Krynn/solamn/thief/theiwar/r20
 *
 * Adapted for use in Palanthas by Mortis 12.2005.
 *
 * Ask about a date, she says meet her out back, if you go there
 * and make out, the constable arrests you :)
 */

#include "../../local.h"
inherit CITIZEN;

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>

#define MY_DRINK		NOBLE + "obj/best_drink"

string *drink_desc = ({"flavour", "flavour2", "drink"});

string *flav = ({"aromatic", "black", "caramel", "chocolate", "cinnamon",
	"dark", "eggnog", "fresh", "hazelnut", "hot", "iced", "light", "mocha",
	"peppermint", "plain", "pumpkin", "steaming", "toffeenut", "vanilla"});
string *coffeevariety = ({"harad coffee", "mer-cafe coffee", "shoikan coffee",
	"tantallon-peaberry coffee", "tradewind coffee"});
string *teavariety = ({"black tea", "green tea", "herbal tea"});
string *drinkvariety = ({"apple-cider", "cafe-misto", "cappuccino",
	"espresso", "latte"});
string *pastryvariety = ({"apricot currant scone", "black and white cookie",
	"blueberry muffin", "butter croissant with apricot glaze",
	"caramel pecan sticky roll", "chocolate cream cheese muffin",
	"chocolate hazelnut biscotti", "cinnamon chip scone", "cinnamon roll",
	"cranberry orange muffin", "crumb cake", "dark chocolate graham cookie",
	"oatmeal raisin cookie", "raspberry cream cheese muffin",
	"raspberry scone", "shortbread cookie", "spice apple torte",
	"vanilla almond biscotti", "white chocolate macadamia nut cookie"});
string *customerv = ({"a noble lady", "a nobleman", "a page", "a messenger",
	"a merchant", "a bureaumancer", "a bureaucrat", "a politician",
	"a customer", "an old man and his wife each", "an elderly lady",
	"a pair of aesthetics", "a maroon-robed aesthetic", "a young man",
	"a young woman", "a boy", "a girl", "a city guardsman", "a constable",
	"a lampier", "a streetwasher", "a grey-cloaked male human",
	"a grey-cloaked female human", "a black-robed hooded male wraith",
	"a wolf-headed muscular male human", "a shadowy veiled female human",
	"[someone]", "[a black-haired swarthy male human]", "a citizen"});

mapping drink_desc_values = (["flavour":({"aromatic", "black",
	"caramel", "chocolate", "cinnamon", "dark", "eggnog",
	"fresh", "hazelnut", "hot", "iced", "light", "mocha", 
	"peppermint", "plain", "pumpkin", "steaming", "toffeenut", "vanilla"}),
	"flavour2":({"aromatic", "black", "caramel", "chocolate", "cinnamon",
	"dark", "eggnog", "fresh", "hazelnut", "hot", "iced", "light", "mocha", 
	"peppermint", "plain", "pumpkin", "steaming", "toffeenut", "vanilla"}),
	"drink":({"apple-cider", "cafe-misto", "cappuccino", "espresso", "latte",
	"harad", "mer-cafe", "shoikan", "tantallon-peaberry",
	"tradewind", "black", "green", "herbal"})]);

mapping drink_to_name = (["apple-cider":"apple-cider",
	"cafe-misto":"cafe-misto", "cappuccino":"cappuccino",
	"espresso":"espresso","latte":"latte", "harad":"coffee",
	"mer-cafe":"coffee", "shoikan":"coffee", "tantallon-peaberry":"coffee",
	"tradewind":"coffee", "black":"tea", "green":"tea",
	"herbal":"tea"]);

/*prototype*/
void arm_me();
void finished_drink(string for_who, string fla1, string fla2, string dri);
string m_f_see();
string serve_drink();
string serve_tea();
string serve_coffee();
string serve_pastry();
string serve_whom();
string tired_sigh();

mixed my_own = ({});

void
create_krynn_monster()
{
	set_name("lani");
	set_living_name("lani");
	add_name(({"human", "barista"}));
	set_adj("rosy-cheeked");
	add_adj("young");
	set_gender(G_FEMALE);
	set_race_name("human");
	set_short("rosy-cheeked young female barista");
	set_long("@@my_long");
	set_title("Holsem, barista of the Mer-cantile");
	
	set_size_descs("very short", "lean");
	set_appearance(6);
	
	set_skill(SS_DEFENCE,       5);
	set_skill(SS_UNARM_COMBAT,  5);
	set_skill(SS_AWARENESS,    25);

	set_stats(({20, 50, 35, 65, 20, 50}));
	set_all_hitloc_unarmed(30);

	set_alignment(370);
	set_knight_prestige(-50);
	set_introduce(1);


	set_act_time(9);
	add_act("say Can I fix a drink for anyone?");
	add_act("say Hi, how are you doing?");
	add_act("emote greets " + "@@serve_whom@@" + " walking in the door.");
	add_act("emote comes out from behind the counter with a white cloth to "
	+ "polish the glass case and bends over, her tight, low-cut capris "
	+ "revealing a red satin hint of what they're worn over.\nThe "
	+ "rosy-cheeked young female barista finishes polishing the glass case "
	+ "and walks back behind the counter.");
	add_act("emote comes out from behind the counter with a white cloth to "
	+ "wipe down the tables and bends over one near you, her tight, V-necked "
	+ "white blouse affording you a view of the crests of her pert breasts.");
	add_act("emote leans back against the brewing counter behind the front "
	+ "counter to take a break and pulls her apron over her head pulling her "
	+ "blouse up with it to reveal the tight muscles of her lean midriff.\n"
	+ "She dabs at the sweat on her neck and bosom before pulling her apron "
	+ "back on and tying it back into place.");
	add_act("emote pulls down the handle on the brewing apparatus releasing a "
	+ "hiss as she goes about her work.");
	add_act("smile friend");
	add_act("emote serves " + "@@serve_whom@@" + " a cup of "
	+ "@@serve_drink@@" + ".");
	add_act("emote serves " + "@@serve_whom@@" + " a cup of "
	+ "@@serve_tea@@" + ".");
	add_act("emote serves " + "@@serve_whom@@" + " a cup of "
	+ "@@serve_coffee@@" + ".");
	add_act("emote serves " + "@@serve_whom@@" + " a cup of "
	+ "@@serve_drink@@" + ".");
	add_act("emote serves " + "@@serve_whom@@" + " a cup of "
	+ "@@serve_tea@@" + ".");
	add_act("emote serves " + "@@serve_whom@@" + " a cup of "
	+ "@@serve_coffee@@" + ".");
	add_act("smiles, her rosy-cheeks lighting up, as she opens the glass "
	+ "case from behind the counter and serves a " + "@@serve_pastry@@"
	+ "to a " + "@@serve_whom@@" + ".\n");

	add_ask(" [about] [how] [to] [do] [i] 'order' / 'ordering' / 'buy' / 'try' / 'acquire' ",
	  "say Please have a look at the blackboard sign behind me.  I drew it "
	+ "myself.  I can tell you a little about our drinks if you like.", 1);
	add_ask(({"drink", "drinks", "tea", "black tea", "green tea", "herbal tea",
		"coffee", "coffees", "flavour", "flavours", "flavourings", "latte",
		"cappuccino", "cafe-misto", "espresso", "apple-cider", "harad",
		"mer-cafe", "shoikan", "tradewind", "tantallon-peaberry"}),  "say "
	+ "Well, all our drinks are good.  You can't go wrong with anything!  Try a "
	+ "few?", 1);
	add_ask(({"service", "barista"}), "say I'm the barista here which means "
	+ "I know how to make all the drinks.  Have you taken a look at our sign "
	+ "yet?  I drew it myself.", 1);
	add_ask(({"price", "prices", "cost", "costs"}), "say Prices are "
	+ "pretty simple.  Just have a look at the sign.  Father likes to "
	+ "make things easy for customers.", 1);
	add_ask(({"cafe", "father's cafe", "mer-cantile", "mer-cantile cafe"}),
	  "say My father owns the Mer-cantile.  It's not bad work, and I meet "
	+ "lots of interesting people every day.", 1); 
	add_ask(({"palanthas", "city"}), "say Palanthas is a great city.  It's "
	+ "pretty safe, too.  Father's cafe is really popular.", 1);
	add_ask(({"hagbad", "hagbads", "hagbad's"}), "say I wouldn't eat there.  It "
	+ "will rot your bowels for sure.", 1);


    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");

}

string
m_f_see()
{
	if (TP->query_gender() == G_MALE)
	{
		return "She is wearing a low, green-trimmed, white apron over a "
		+ "tight, V-necked, white blouse pushing her pert breasts together "
		+ "to create a very aesthetically appealing bosom.";
	}
	return "She is wearing a low, green-trimmed, white apron over a "
	+ "tight, V-necked, white blouse that reveals a little too much, "
	+ "but is still cute.";
}

string
my_long()
{
	string m_f_see = "";

	if (TP->query_gender() == G_MALE)
	{
		m_f_see = "She is wearing a low, green-trimmed, white apron over a "
		+ "tight, V-necked, white blouse pushing her pert breasts together "
		+ "to create a very aesthetically appealing bosom.";
	}
	else
	{
		m_f_see = "She is wearing a low, green-trimmed, white apron over a "
		+ "tight, V-necked, white blouse that reveals a little too much, "
		+ "but is still cute.";
	}


	return "The girl behind the counter has rosy-cheeks, sparkling green "
	+ "eyes, and a friendly smile.  Her reddish-brown hair is up in a pony "
	+ "tail with a twist sending her locks spiraling up and over in the "
	+ "back.  "	+ m_f_see + "  She is serving drinks behind the "
	+ "counter.\n";
}

string
def_answer()
{
    command("say Sorry.  I don't know about that.");
	command("smile friend");
    return "";
}

void
arm_me()
{
    seteuid(getuid(TO));

	MONEY_MAKE_SC(5 + random(50))->move(TO);
	MONEY_MAKE_GC(5 + random(15))->move(TO);

}

void
init_living()
{
	ADD("order_drink", "try");
    ADD("order_drink", "order");
    ::init_living();
}

string serve_tea()
{
	string flav1 = one_of_list(flav);
	string flav2 = one_of_list(flav);
	string srvtea = one_of_list(teavariety);
	return flav1 + " " + flav2 + " " + srvtea;
}

string serve_coffee()
{
	string flav1 = one_of_list(flav);
	string flav2 = one_of_list(flav);
	string srvcof = one_of_list(coffeevariety);
	return flav1 + " " + flav2 + " " + srvcof;
}

string serve_drink()
{
	string flav1 = one_of_list(flav);
	string flav2 = one_of_list(flav);
	string srvdrink = one_of_list(drinkvariety);
	return flav1 + " " + flav2 + " " + srvdrink;
}

string serve_pastry()
{
	string flav1 = one_of_list(flav);
	string flav2 = one_of_list(flav);
	string srvpastry = one_of_list(pastryvariety);
	return flav1 + " " + flav2 + " " + srvpastry;
}

string serve_whom()
{
	string cwhom = one_of_list(customerv);
	return cwhom;
}


/*
 * returns an array: ({ flavour1, flavour2, drink })
 */
mapping compute_all_necessary_drink_data(string *argdata)
{
	int typ1, i, j, k;
	mapping order;
	order = (["type":0,"flavour":"","flavour2":"","drink":""]);

	for(i=0,j=sizeof(drink_desc);i<j;i++)
	{
		k = member_array(argdata[i],drink_desc_values[drink_desc[i]]);
		if (k == -1)
			{
			command("say I'm sorry, but " + argdata[i] + " is not an "
			+ "available " + drink_desc[i] + " choice.");
			return (["type":0]); /*invalid drink*/
			}
		order[drink_desc[i]] = drink_desc_values[drink_desc[i]][k];
	}

	order["type"] = drink_to_name[order["drink"]];

	return order;
}

void
give_out_drink(string who_name, object merdrink, int flag, int reduce)
{
	int price = 288;
	object who;
	string what_is_it = merdrink->short();
	string tsigh = tired_sigh();

	if (who_name)
		who = find_player(who_name);
    /*pay in here!*/
	if (!MONEY_ADD(who, -price))
	{
		command("say Hey, you can't afford a " + what_is_it + ".");
		command("emote rolls her green eyes frustratedly.");
		command("sip " + what_is_it);
		command("emote sighs tiredly, " + tsigh + ", as she dumps "
		+ "the " + what_is_it + " in the trash.");
		merdrink->remove_object();
		command("say Why are people always ordering drinks they can't "
		+ "afford?\n");
		return;
	}
    who->catch_msg("You pay the barista twenty-four silver coins.\n");

    merdrink->remove_shadow();

    if (!command("give " + merdrink->query_name() + " to " + who_name))
      command("drop " + merdrink->query_name());
}

int
order_drink(string str) 
{
	string cus, col, mat, art;
	string *argdata;
	mapping my_order;

    NF(C(query_verb()) + " what?\n");
    if (!str)
      return 0;

    /* syntax is: 'try <flavour1> <flavour2> <drink>' */
	argdata = explode(str," ");
    NF(C(query_verb()) + " <flavour1> <flavour2> <name>.\n");
    if(sizeof(argdata) != 3)
	{ return 0; }

	my_order = compute_all_necessary_drink_data(argdata);

    if (my_order["type"])
	{
		write("You place your order.\n");
		say(QCTNAME(TP) + " orders a drink.\n");
		
		command("emote says, \"Ok, just a sec,\" and starts fixing a "
		+ "drink.");

		finished_drink(TP->query_real_name(),
			my_order["flavour"], my_order["flavour2"], my_order["drink"]);
      return 1;
	}
    NF("You failed to order a drink.\n");
    return 0;
}

void
finished_drink(string for_who, string fla1, string fla2, string dri)
{

	object merdrink = clone_object(MY_DRINK);
    merdrink->set_drink_data(fla1 + "&&"
							+ fla2 + "&&"
							+ dri);
	merdrink->move(TO);

    give_out_drink(for_who, merdrink, 0, 0);
}

string tired_sigh()
{
	string tsigh = one_of_list(({"the nipples of her pert breasts pushing out "
	+ "against the fabric of her tight, V-necked, white blouse", "a drop of "
	+ "sweat rolling down her neck between her pert breasts pushed together "
	+ "by the tight fabric of her V-necked, white blouse", "turning around "
	+ "to reveal the tight fabric of her low-cut, tan capris riding up "
	+ "between her firm buttocks", "her rosy-cheeks flushed and pert breasts "
	+ "heaving"}));
	return tsigh;
}