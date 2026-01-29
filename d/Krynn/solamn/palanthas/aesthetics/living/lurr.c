/* 
 * Mortis 04.2006
 *
 * Lurr Bramous, cobbler off Jems Court in the poor housing district
 * of the Aesthetics quarter in Palanthas.  Crafts custom shoes.
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

inherit CITIZEN;
inherit "/std/act/action";

#define MY_CLOTHING		NOBLE + "arms/parmour"
#define MY_SHOES		MONKS + "arms/lurr_shoes"

/* prototypes */
void arm_me();
int alrm; /* the alarm while tailoring an item */
int good = 0;
int enter_alrm = 0;
object kshoes;
mixed my_own = ({});
string prep_shoes(string sty1, string sty2, string sty3, string footw);

mapping stock = ([ ]);

string *footwear_desc = ({"custom", "colour", "material", "footwear"});

mapping boots_desc_values = (["custom":({"buckled", "dark", "formal",
	"glistening", "heavy", "laced", "light", "loose", "noble", "ornate", 
	"plain", "rugged", "short", "skin-tight", "steel-toed", "steel-tipped",
	"strapped", "sturdy", "supple", "thick", "thin", "tight"}),
	"colour":({"black", "white", "charcoal", "grey", "brown", "dark-brown", 
	"beige", "tan", "crimson", "maroon", "mottled-brown", "pink",
	"dark-orange", "orange", "pale-yellow", "yellow", "forest-green",
	"dark-green", "mottled-green", "olive-green", "blue",
	"pale-blue", "raven-blue", "indigo", "purple", "royal-purple", "coppery",
	"golden", "silvery"}),
	"material":({"alligator", "bear", "deer", "fox", "hard", "hide",
	"leather", "lizard", "sable", "snake", "soft", "studded", "suede"}),
	"footwear":({"boots"})]);

mapping heels_desc_values = (["custom":({"alluring", "buckled", "dark", 
	"delicate", "dainty", "elegant", "enchanting", "formal", "glistening", 
	"heavy", "hot", "laced", "light", "loose", "noble", "ornate", "open-toed", 
	"plain", "sensual", "sensuous", "shiny", "short", "skin-tight", 
	"sparkling", "strapped", "supple", "thin", "tight", "translucent"}),
	"colour":({"black", "white", "charcoal", "grey", "brown", "dark-brown", 
	"mottled-brown", "beige", "tan", "crimson", "maroon", "pink", "red",
	"ruby-red", "dark-orange", "orange", "pale-yellow", "yellow", 
	"forest-green", "dark-green", "emerald-green", "green", "mottled-green",
	"olive-green", "blue", "sapphire-blue", "pale-blue", "raven-blue", 
	"indigo", "purple", "royal-purple", "violet", "coppery", "golden",
	"silvery"}),
	"material":({"alligator", "hard", "leather", "lizard", "snake", "soft"}),
	"footwear":({"high-heels"})]);

mapping sandals_desc_values = (["custom":({"alluring", "buckled", "dark", 
	"elegant", "glistening", "heavy", "laced", "light", "loose", "ornate", 
	"open-toed", "plain", "rugged", "sensual", "sensuous", 	"strapped", 
	"sturdy", "supple", "thick", "thin", "tight"}),
	"colour":({"black", "white", "charcoal", "grey", "brown", "dark-brown", 
	"beige", "tan", "crimson", "maroon", "mottled-brown", "pink",
	"dark-orange", "orange", "pale-yellow", "yellow", "forest-green",
	"dark-green", "mottled-green", "olive-green", "blue",
	"pale-blue", "raven-blue", "indigo", "purple", "royal-purple", "coppery",
	"golden", "silvery"}),
	"material":({"alligator", "deer", "dupion", "elfwyr", "hard", "hemp", 
	"hide", "leather", "lizard", "snake", "silk", "soft", "suede", 
	"swansdown"}),
	"footwear":({"sandals"})]);

mapping shoes_desc_values = (["custom":({"alluring", "buckled", "common", 
	"dark", "delicate", "dainty", "elegant", "enchanting", "formal", 
	"glistening", "heavy", "hot", "jaunty", "laced", "light", "loose", 
	"noble", "ornate", "open-toed", "plain", "rugged", "sensual", "sensuous", 
	"shiny", "short", "skin-tight", "soft", "steel-toed", "steel-tipped", 
	"sparkling", "strapped", "sturdy", "supple", "thick", "thin", "tight"}),
	"colour":({"black", "white", "charcoal", "grey", "brown", "dark-brown", 
	"beige", "tan", "crimson", "maroon", "mottled-brown", "pink",
	"dark-orange", "orange", "pale-yellow", "yellow", "forest-green",
	"dark-green", "mottled-green", "olive-green", "blue",
	"pale-blue", "raven-blue", "indigo", "purple", "royal-purple", "coppery",
	"golden", "silvery"}),
	"material":({"alligator", "bear", "canvas", "deer", "fox", "hard", "hemp",
	"hide", "leather", "linen", "lizard", "sable", "silk", "snake", "soft",
	"studded", "suede", "wool"}),
	"footwear":({"shoes"})]);

mapping slippers_desc_values = (["custom":({"alluring", "comfortable", 
	"dark", "delicate", "dainty", "elegant", "enchanting", "formal", 
	"glistening", "heavy", "jaunty", "laced", "light", "loose", "noble", 
	"ornate", "padded", "plain", "quiet", "rugged", "sensual", "sensuous", 
	"shiny", "short", "silent", "skin-tight", "soft", "sparkling", "strapped", 
	"supple", "thin", "tight"}),
	"colour":({"black", "white", "charcoal", "grey", "brown", "dark-brown", 
	"mottled-brown", "beige", "tan", "crimson", "maroon", "pink", "red",
	"ruby-red", "dark-orange", "orange", "pale-yellow", "yellow", 
	"forest-green", "dark-green", "emerald-green", "green", "mottled-green",
	"olive-green", "blue", "sapphire-blue", "pale-blue", "raven-blue", 
	"indigo", "purple", "royal-purple", "violet", "coppery", "golden",
	"silvery"}),
	"material":({"alligator", "arrasene", "bear", "cashmyr", "cotton",
	"dupion", "deer", "elfwyr", "ermine", "fox", "hard", "hide", "leather", 
	"lizard",  "messaline", "mink", "organdie", "rabbit", "sable", "silk", 
	"snake", "soft", "studded", "suede", "swansdown", "terrycloth", "wool"}),
	"footwear":({"slippers"})]);


void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("lurr");
	set_living_name("lurr");
	add_name(({"human", "cobbler", "craftsman", "bramous"}));
	set_adj("old");
	add_adj("bushy-moustached");
	set_gender(G_MALE);
	set_short("old bushy-moustached male cobbler");
	set_long("The cobbler is a wrinkled man with long, stringy gray and "
	+ "white hair pulled back behind his ears and a bushy, white "
	+ "moustache that almost completely covers his mouth.\nHe is wearing a "
	+ "dirty, leather apron.\n");
	set_race_name("human");
	set_title("Bramous, humble Cobbler of Jems Court");
	
	set_size_descs("short", "of normal width");
	set_appearance(4);
	
	set_skill(SS_DEFENCE,        22);
	set_skill(SS_AWARENESS,      20);
	set_skill(SS_UNARM_COMBAT,   10);

	set_stats((({45, 65, 55, 80, 85, 55})), 4);
	set_all_hitloc_unarmed(10);

	set_alignment(650);
	set_knight_prestige(-75);
	set_introduce(1);


	set_act_time(34);
	add_act("@@_my_add_acts");

	set_cact_time(11);
	add_cact("emote ponders what his protection money is going towards.");

	add_ask("[about] [how] [to] [do] [i] 'order' / 'ordering' / 'footwear' / 'footwears' / 'shoes' / 'boots' / 'slippers' / 'sandals'",
	  "say If you'd like me to cobble some footwear for you, have a look at "
	+ "the sign upon the south wall. You may also <check> anything on the "
	+ "five smaller signs beneath it, but you should <read sign> first.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");

}

string
my_add_acts()
{
	string myact;

	myact = one_of_list(({"emote mushes his moustache over from one side to "
	+ "the other with his upper lip as he concentrates on "
	+ one_of_list(({"cutting a piece of leather", "shaping a piece of leather",
		"tacking a shoe sole in place", "lacing a boot"})) + ".",
	"emote nods and smiles wearily.",
	"smell",
	"time",
	"emote mops his brow with an old handkerchief.",
	"check boots",
	"check heels",
	"check sandals",
	"check shoes",
	"check slippers",
	"emote arranges his tools haphazardly on his table beside the stairs.",
	"emote peers up as he says:  Hello, come in.",
	"emote motions with his hand, directing a journeyman smith to "
	+ "deliver " + "@@exa_it@@" + " to " + "@@exa_it2@@" + "."}));

	return myact;
}

string
def_answer()
{
    command("say I don't know much.  I'm just a cobbler.");
    return "";
}

void
arm_me()
{
	// Lurr's custom shirt.
	object kshirt = clone_object(MY_CLOTHING);
    kshirt->set_armour_data("Lurr" + "&&"
							+ "striped" + "&&"
							+ "brown" + "&&"
							+ "linen" + "&&"
							+ "shirt");
	kshirt->move(TO);

	// Lurr's custom legwear.
	object kpants = clone_object(MY_CLOTHING);
    kpants->set_armour_data("Lurr" + "&&"
							+ "thin" + "&&"
							+ "dark-brown" + "&&"
							+ "wool" + "&&"
							+ "pants");
	kpants->move(TO);

	// Lurr's custom boots.
	kshoes = clone_object(MY_SHOES);
    kshoes->set_footwear_data("buckled" + "&&"
							+ "brown" + "&&"
							+ "leather" + "&&"
							+ "shoes");
	kshoes->move(TO);

	command("wear all");
}

void
attacked_by(object ob)
{
	command("say Darn.");

    ::attacked_by(ob);
}

void
init_living()
{
    add_action("order","order");
    add_action("collect","collect");
    add_action("enquire","enquire");
	add_action("enquire","inquire");
    ::init_living();
}

int
collect(string str)
{
    object footwear;
	if (alrm)
	{
		command("say Just finishing a pair... one sec.");
		return 1;
	}
    command("say Your order.  Ok.");
    command("emote removes your footwear from a nearby rack.");
    command("emote smiles saying:  Your footwear.");
    footwear = stock[TP->query_real_name()];
    alrm = set_alarm(2.0,0.0,"give_out_footwear",TP->query_real_name(),
             footwear, 1);
    return 1;
}
/*
 * returns an array: ({ custom, colour, footwear })
 */
mapping compute_all_necessary_footwear_data(string *argdata)
{
	int i, j, k, k1, s1, p1, c1, a1;
	string wepcomp = argdata[3];
	mapping order;
	order = (["type":0,"custom":"","colour":"","material":"","footwear":""]);
	k1 = IN_ARRAY(wepcomp, boots_desc_values["footwear"]);
	s1 = IN_ARRAY(wepcomp, heels_desc_values["footwear"]);
	p1 = IN_ARRAY(wepcomp, sandals_desc_values["footwear"]);
	c1 = IN_ARRAY(wepcomp, shoes_desc_values["footwear"]);
	a1 = IN_ARRAY(wepcomp, slippers_desc_values["footwear"]);

	if (k1)
	{
		for(i=0,j=sizeof(footwear_desc);i<j;i++)
		{
			k = member_array(argdata[i],boots_desc_values[footwear_desc[i]]);
			if (k == -1)
			{
				command("say I'm sorry, but " + argdata[i] + " is not an "
				+ "available " + footwear_desc[i] + " choice for a pair of "
				+ wepcomp + ".");
				return (["type":0]); // invalid footwear
			}
			order[footwear_desc[i]] = boots_desc_values[footwear_desc[i]][k];
		}
		order["type"] = 1;
	}

	if (s1)
	{
		for(i=0,j=sizeof(footwear_desc);i<j;i++)
		{
			k = member_array(argdata[i],heels_desc_values[footwear_desc[i]]);
			if (k == -1)
			{
				command("say I'm sorry, but " + argdata[i] + " is not an "
				+ "available " + footwear_desc[i] + " choice for a pair of "
				+ wepcomp + ".");
				return (["type":0]); // invalid footwear
			}
			order[footwear_desc[i]] = heels_desc_values[footwear_desc[i]][k];
		}
		order["type"] = 1;
	}

	if (p1)
	{
		for(i=0,j=sizeof(footwear_desc);i<j;i++)
		{
			k = member_array(argdata[i],sandals_desc_values[footwear_desc[i]]);
			if (k == -1)
			{
				command("say I'm sorry, but " + argdata[i] + " is not an "
				+ "available " + footwear_desc[i] + " choice for a pair of "
				+ wepcomp + ".");
				return (["type":0]); // invalid footwear
			}
			order[footwear_desc[i]] = sandals_desc_values[footwear_desc[i]][k];
		}
		order["type"] = 1;
	}

	if (c1)
	{
		for(i=0,j=sizeof(footwear_desc);i<j;i++)
		{
			k = member_array(argdata[i],shoes_desc_values[footwear_desc[i]]);
			if (k == -1)
			{
				command("say I'm sorry, but " + argdata[i] + " is not an "
				+ "available " + footwear_desc[i] + " choice for a pair of "
				+ wepcomp + ".");
				return (["type":0]); // invalid footwear
			}
			order[footwear_desc[i]] = shoes_desc_values[footwear_desc[i]][k];
		}
		order["type"] = 1;
	}

	if (a1)
	{
		for(i=0,j=sizeof(footwear_desc);i<j;i++)
		{
			k = member_array(argdata[i],slippers_desc_values[footwear_desc[i]]);
			if (k == -1)
			{
				command("say I'm sorry, but " + argdata[i] + " is not an "
				+ "available " + footwear_desc[i] + " choice for a pair of "
				+ wepcomp + ".");
				return (["type":0]); // invalid footwear
			}
			order[footwear_desc[i]] = slippers_desc_values[footwear_desc[i]][k];
		}
		order["type"] = 1;
	}

	return order;
}

void
give_out_footwear(string who_name, object footwear, int flag)
{
	int price;
	object who;
	string what_is_it = footwear->short();

	if (what_is_it == 0)
	{
		what_is_it = "footwear";
	}

	if (who_name)
		who = find_player(who_name);

	if (!who || E(TO) != E(who))
	{
		if (flag)
			command("say Well, my last customer was too impatient to pick up "
			+ "their " + what_is_it + ".");
		else
			command("say Well, my last customer was too impatient to see the "
			+ "completion of their " + what_is_it + ".");

		command("emote smiles half-heartedly.");

		if (footwear)
        {
			if (flag)
				command("emote places " + what_is_it + " on a nearby rack "
				+ "to be collected later.");
			else
			{
				command("emote places " + what_is_it + " on a nearby rack "
				+ "to be collected later.");
				stock += ([ who_name:footwear ]);
			}
        }
		command("say Ok then.");
		alrm = 0;
		return;
	}

	if (!footwear)
	{
		if (flag)
			command("say I don't remember an order for a pair of "
			+ what_is_it + " placed by you.");
		else
			command("say Sorry, I don't know what just happened.  I must be "
			+ "getting old.  Please don't gang bang me.");

		command("sigh confus");
		alrm = 0;
		return;
	}

	footwear->move(TO);
	command("say Your " + what_is_it + ".");
	command("emote licks his lips in well-meaning befuddlement.");
    alrm = 0;

	price = footwear->adjust_value();
	price = price * 2;
		
	if (!MONEY_ADD(who, -price))
	{
		command("say You ummm, need more funds.  No gang discounts.");
		command("say Your " + what_is_it + " will be here for you to collect "
		+ "when you can pay.");
		command("emote places " + what_is_it + " on a nearby rack.");
		footwear->move(VOID);
		stock += ([ who_name:footwear ]);
		return;
	}
    who->catch_msg("You pay the smith " + price + " copper coins.\n");

    footwear->remove_shadow();

	if (!command("give " + footwear->query_name() + " to " + who_name))
		command("drop " + footwear->query_name());

	stock = m_delete(stock, who_name);
    
	if (enter_alrm)
	{
		remove_alarm(enter_alrm);
		enter_alrm = 0;
	}
}

int
order(string str)
{
	string cus, col, mat, art;
	string *argdata;
	mapping my_order;

	if (alrm)
	{
		command("say I am prepping a pair of... one sec.");
		return 1;
	}

    NF(C(query_verb()) + " what?\n");

	if (!str)
		return 0;

	if (stock[TP->query_real_name()])
	{
		  NF("There is already some footwear in stock for you.  "
		  + "Would you collect it first?\n");
		  return 0;
	}

    /* syntax is: 'order <custom> <colour> <material> <footwear>' */
	argdata = explode(str," ");

    NF(C(query_verb()) + " <custom> <colour> <material> <footwear>.\n");

    if(sizeof(argdata) != 4)
	{ return 0; }

	my_order = compute_all_necessary_footwear_data(argdata);

    if (my_order["type"])
	{
		alrm = set_alarm(8.0, 0.0, "finished_footwear",
		TP->query_real_name(), my_order["custom"],
		my_order["colour"], my_order["material"], my_order["footwear"]);
		write("You place your order.\n");
		say(QCTNAME(TP) + " orders a footwear.\n");

		command("say I'll just prep those for you now.  If you are not "
		+ "here when I finish, you may return later to <collect> it.");

		add_prop(TSIT, 1);
		add_prop(LIVE_S_EXTRA_SHORT," is prepping a pair of "
		+ argdata[0] + " " + argdata[1] + " " + argdata[2] + " " + argdata[3]);

		set_alarm(6.0, 0.0, "prep_shoes", argdata[0], argdata[1], argdata[2],
			argdata[3]);

      return 1;
	}
    NF("You failed to order a valid type of footwear.  Read the signs "
	+ "again for valid footwear choices.\n");
    return 0;
}

void
finished_footwear(string for_who, string cus, string col, string mat,
				  string footw)
{
	object footwear = clone_object(MY_SHOES);
    footwear->set_footwear_data(cus + "&&"
								+ col + "&&"
								+ mat + "&&"
								+ footw);

    give_out_footwear(for_who, footwear, 0);
}

int
enquire(string str)
{
    int price, mfactor, afactor;
    string cus, col, mat, art;
	string *argdata;
	mapping my_order;
    NF(C(query_verb()) + " about what?\n");
    if (!str)
      return 0;
    

    /* syntax is: 'enquire <custom> <colour> <material> <article>' */
	argdata = explode(str," ");
    NF("Are you trying to " + query_verb() + " about <custome'> "
	   + "<colour> <material> <article>?\n");
    if(sizeof(argdata) != 4)
	{ return 0; }

	my_order = compute_all_necessary_footwear_data(argdata);

    if (my_order["type"])
	{
		if (IN_ARRAY(argdata[3], ({"boots"})))
		{ afactor = 4; }

		if (IN_ARRAY(argdata[3], ({"shoes", "high-heels"})))
		{ afactor = 3; }

		if (IN_ARRAY(argdata[3], ({"sandals", "slippers"})))
		{ afactor = 2; }

		if (IN_ARRAY(argdata[2], ({"canvas", "cotton", "linen", "organdie", 
			"terrycloth", "wool"})))
		{ mfactor = 3; }

		if (IN_ARRAY(argdata[2], ({"hard", "hide", "leather", "soft", 
			"studded"})))
		{ mfactor = 4; }

		if (IN_ARRAY(argdata[2], ({"arrasene", "bear", "deer", "dupion", 
			"suede", "silk", "messaline", "snake", "lizard", "alligator", 
			"rabbit"})))
		{ mfactor = 5; }

		if (IN_ARRAY(argdata[2], ({"cashmyr", "swansdown"})))
		{ mfactor = 9; }

		if (IN_ARRAY(argdata[2], ({"fox", "sable", "mink", "ermine"})))
		{ mfactor = 12; }

		if (IN_ARRAY(argdata[2], ({"elfwyr"})))
		{ mfactor = 18; }

		price = 1 + afactor * mfactor * 40;

		command("say An article of that material would cost around "
		+ price + " coppers.");
		return 1;
	}
    return 0;
}

string
exa_it()
{
	return one_of_list(({"a pair of boots", "a pair of heels", 
	"a pair of sandals", "a pair of shoes", "a pair of slippers"}));
}

string
exa_it2()
{
	return one_of_list(({"a cloaked short figure", "a cloaked tall figure",
	"a young constable", "a well-dressed squire", "an aging mercenary",
	"a young boy", "a young girl", "an old, wide-hatted traveller",
	"a swarthy, stubble-chinned mercenary", "a white-robed woman",
	"a pair of dark-cloaked, young ruffians", "a long-bearded dwarf"}));
}

int
react_bow(object actor)
{
	command("emote bows in a weary fashion, one hand on his creaking "
	+ "back for support.");
	command("emote stares blankly as his back goes \"CRACK!\".");
	return 1;
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "bow")
        set_alarm(1.0, 0.0, &react_bow(actor));
}

string prep_shoes(string sty1, string sty2, string sty3, string footw)
{
	command("emote finishes prepping the " + footw + " before adding the "
	+ "final touches that will make the " + footw + " " + sty1 + ", " 
	+ sty2 + ", and " + sty3 + ".");
	command("say This " + sty1 + " " + sty2 + " " + sty3 + " pair of " 
	+ footw + " will last a while.");

	remove_prop(TSIT);
	remove_prop(LIVE_S_EXTRA_SHORT);
	return "";
}
