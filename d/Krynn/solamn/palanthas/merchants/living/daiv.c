/* 
 * Mortis 04.2006
 *
 * Daiv Temasis, robe merchant and tailor of the Merchant
 * quarter of Palanthas.  Sells custom robes and can sew
 * in a liner insert from Daiv to provide hidden
 * robe inside.  Very suspicious.  He'll want proof of
 * trustworthiness before he'll sew in a liner.
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define MY_ROBE			MERCH + "arms/daiv_robe"
#define MY_AXE			MERCH + "arms/smith_axe"

inherit CITIZEN;
inherit "/std/act/action";

int attacked = 0;
string customize_robe(string sty, string col, string mat, string arm);
string exa_it();
string exa_it2();

string *robe_desc = ({"style", "colour", "material", "robe"});

mapping robe_desc_values = (["style":({"billowing", "buttoned", "dark",
	"formal", "heavy", "laced", "light", "long", "loose", "noble", "ornate",
	"plain", "short", "soft", "thick", "thin", "translucent", "unbuttoned",
	"unlaced"}),
	"colour":({"black", "white", "charcoal", "grey", "crimson", "maroon",
	"pink", "dark-orange", "orange", "pale-yellow", "yellow", "forest-green",
	"dark-green", "blue", "pale-blue", "raven-blue", "indigo", "purple",
	"royal-purple", "brown", "dark-brown", "beige", "tan", "coppery", 
	"silvery", "golden"}),
	"material":({"alligator", "arrasene", "cashmyr", "cotton", "dupion", 
	"elfwyr", "ermine", "fox", "linen", "lizard", "mink", "messaline", 
	"organdie", "rabbit", "sable", "silk", "snake", "suede", "swansdown",
	"wool"}),
	"robe":({"robe", "coat"})]);

/*prototype*/
void arm_me();

int alrm; /* the alarm while tailoring an item */
mapping stock = ([ ]);
int good = 0;
mixed my_own = ({});
int enter_alrm = 0;

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("daiv");
	set_living_name("daiv");
	add_name(({"human", "merchant", "tailor", "craftsman", "temasis"}));
	set_adj("red-haired");
	add_adj("cocoa-skinned");
	set_gender(G_MALE);
	set_short("red-haired cocoa-skinned male merchant");
	set_long("Set off by his dark, cocoa toned skin, this merchant's red, "
	+ "tightly-curled hair gleams in fiery hues and has been pulled into a "
	+ "knot atop his head.  His hands are well manicured with thin, dextrous "
	+ "fingers covered in gold and jewelled rings.  Flared nostrils are "
	+ "surrounded by furrowed wrinkles as the merchant eyes his surroundings "
	+ "cautiously.\n");
	set_race_name("human");
	set_title("Temasis, Robe Merchant and Tailor of Palanthas");
	
	set_size_descs("of normal length", "of normal width");
	set_appearance(5);
	
	set_skill(SS_DEFENCE,      60);
    set_skill(SS_PARRY,        30);
	set_skill(SS_AWARENESS,    70);
	set_skill(SS_RIDING,       30);
	set_skill(SS_WEP_AXE,      85);
    set_skill(SS_BLIND_COMBAT, 55);

	set_stats((({125, 125, 125, 180, 80, 160})), 5);
	set_all_attack_unarmed(20, 12);
	set_all_hitloc_unarmed(10);

	set_alignment(1110);
	set_knight_prestige(-100);
	set_introduce(1);


	set_act_time(18);
	add_act("@@my_add_acts");

	set_cact_time(14);
	add_cact("emote say:  I knew you were a miscreant.  I knew it!");

	add_ask(({"tregannin", "tre'gannin", "luesr"}), "say Tre'Gannin?  "
	+ "Tre'Gannin Luesr?!?  I don't know what he's told you, but whatever it "
	+ "is, it's a lie.  He may be a top cloth and materials importer, but I "
	+ "have sources high up that tell me otherwise.", 1);
	add_ask("liner", "say You are interested in adding a liner to one of my "
	+ "robes, eh?  Yes, I believe I can help you with that.  If you have a "
	+ "liner and the robe you want to line, you may <sew liner in robe>, "
	+ "and I will help you sew it in.", 1);
	add_ask("daronius", "say Yes, he is a quality man, a quality man, yes.  "
	+ "He sells liners tailored to be sewn into my robes for added "
	+ "protection on dangerous journies.", 1);
	add_ask("[about] [how] [to] [do] [i] 'robe' / 'robes' / 'item' / 'items' / 'order' / 'ordering' / 'arms'",
	  "say I sell the best robes in the city.  Look at the marble sign "
	+ "upon the east wall.  You may also <check> anything on it.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0, 0.0, "arm_me");

}

string
def_answer()
{
    command("say Why do you want to know?  Who told you to ask me?");
    return "";
}

string
my_add_acts()
{
	string myact;
	string exa1 = exa_it();
	string exa2 = exa_it2();

	myact = one_of_list(({"emote peers warily about the area with his "
	+ "furtive, dark brown eyes.",
	"smell",
	"time",
	"say I hate that Tre'Gannin.  I don't trust anything he says.",
	"emote furrows his brow and nostrils as he examines " + exa1 + " that "
	+ "just came in.",
	"peruse robes",
	"peer susp",
	"peer paran",
	"emote arranges some robes on the racks.",
	"emote says:  Welcome.  Please come in.",
	"emote delivers " + exa1 + " to " + exa2 + "."}));

	return myact;
}

void
arm_me()
{
	string dcus = one_of_list(({"buttoned", "cuffed", "debonair", "formal",
								"noble"}));
	string dcol = "black";
	string dmat = "silk";

	// Daiv's custom shirt.
	object dshirt = clone_object(NOBLE + "arms/parmour");
    dshirt->set_armour_data("Daiv" + "&&"
						  + dcus + "&&"
						  + dcol + "&&"
						  + dmat + "&&"
						  + "shirt");
	dshirt->move(TO);

	// Daiv's custom legwear.
	dcus = one_of_list(({"cuffed", "debonair", "formal", "noble"}));
	object dpants = clone_object(NOBLE + "arms/parmour");
    dpants->set_armour_data("Daiv" + "&&"
						    + dcus + "&&"
							+ dcol + "&&"
							+ dmat + "&&"
							+ "slacks");
	dpants->move(TO);

	// Daiv's custom boots.
	dcus = one_of_list(({"fur-trimmed", "noble", "ornate"}));

	object dboots = clone_object(MERCH + "arms/larmour");
    dboots->set_armour_data("glistening" + "&&"
							+ dcol + "&&"
							+ "hard" + "&&"
							+ "boots");
	dboots->move(TO);

	// Daiv's custom body robe.
	dcus = one_of_list(({"noble", "formal", "buttoned"}));
	dmat = one_of_list(({"organdie", "alligator", "cashmyr", "fox"}));
	object drobe = clone_object(MY_ROBE);
	drobe->set_armour_data(dcus + "&&"
						   + "black" + "&&"
						   + dmat + "&&"
						   + "robe" + "&&"
						   + "off" + "&&"
						   + "1" + "&&"
						   + "2" + "&&"
						   + "3" + "&&");
	drobe->move(TO);

	command("wear all");
}

void
arm_weapon()
{
	int wep1;
	string wepshort;
	object mywep;

	command("say What is this?  You must be an agent of Tre'Gannin!  I hate "
	+ "him!");
	command("shout HAGEN!  It's Tre'Gannin again!");

	if (attacked == 0)
	{
		mywep = clone_object(MY_AXE);
		mywep->set_weapon_data("spiked" + "&&"
							   + "grensh" + "&&"
							   + "cleaver");
		mywep->move(TO);
		wepshort = mywep->short();
		command("emote pulls a " + wepshort + " out from beneath his "
		+ "robes and grasps it fiercely.");
		command("wield weapon");
	}
		attacked = 1;
}

void
attacked_by(object ob)
{
	arm_weapon();

    ::attacked_by(ob);
}

void
init_living()
{
    ADA("order");
    ADA("collect");
	ADA("enquire");
	ADD("enquire", "inquire");
    ::init_living();
}

int
collect(string str)
{
    object robe;
	if (alrm)
	{
		command("say I'm preparing a robe.  I will attend to you shortly.");
		return 1;
	}
    command("say Ah, Your order.");
    command("emote removes your robe from a nearby rack.");
    command("emote smiles saying:  Your robe.");
    robe = stock[TP->query_real_name()];
    alrm = set_alarm(2.0, 0.0, "give_out_robe", TP->query_real_name(),
             robe, 1);
    return 1;
}
/*
 * returns an array: ({ style, colour, material, robe })
 */
mapping compute_all_necessary_robe_data(string *argdata)
{
	int i, j, k, k1, s1, p1, c1, a1;
	string armcomp = argdata[3];
	mapping order;
	order = (["type":0,"style":"", "colour":"", "material":"", "robe":""]);
	k1 = IN_ARRAY(armcomp, robe_desc_values["robe"]);

	if (k1)
	{
		for(i=0,j=sizeof(robe_desc);i<j;i++)
		{
			k = member_array(argdata[i],robe_desc_values[robe_desc[i]]);
			if (k == -1)
			{
				command("say I'm sorry, but " + argdata[i] + " is not an "
				+ "available " + robe_desc[i] + " choice for a " + armcomp
				+ ".");
				return (["type":0]); // invalid robe
			}
			order[robe_desc[i]] = robe_desc_values[robe_desc[i]][k];
		}
		order["type"] = 1;
	}
	return order;
}

int
calculate_price(mixed ob, object for_who, int reduce)
{
    int price, mfactor, afactor;
	string af = "";
	string mf = "";

	/* This if ob is an object from give_out_robe */
    if (objectp(ob))
	{
		string *adjmat;
		adjmat = ob->query_adjs();

		af = (ob->query_name());
		mf = adjmat[3];
	}

	/* This is if ob is an array.  We want to use ob[0] material 
	 * and ob[1] article? */
    else
	{
		af = (ob[1]);
		mf = (ob[0]);
	}

	if (IN_ARRAY(af, ({"robe"})))
	{ afactor = 4; }

	if (IN_ARRAY(af, ({"coat"})))
	{ afactor = 3; }

	if (IN_ARRAY(mf, ({"cotton", "linen", "organdie", "wool"})))
	{ mfactor = 3; }

	if (IN_ARRAY(mf, ({"arrasene", "dupion", "suede", "silk",
		"messaline", "snake", "lizard", "alligator", "rabbit"})))
	{ mfactor = 5; }

	if (IN_ARRAY(mf, ({"cashmyr", "swansdown"})))
	{ mfactor = 9; }

	if (IN_ARRAY(mf, ({"fox", "sable", "mink", "ermine"})))
	{ mfactor = 12; }

	if (IN_ARRAY(mf, ({"elfwyr"})))
	{ mfactor = 18; }

	price = 1 + afactor * mfactor;
    price = price * (135 - (for_who->query_skill(SS_TRADING) / 2));
	// reduce can be used for discounts for groups
    return price * (100 - reduce) / 100 - 10 + random(20); 
}

void
give_out_robe(string who_name, object robe, int flag)
{
	int price, k1, reduce = 0;
	object who;
	string what_is_it = robe->short();
	string robeprice = robe->query_name();

	k1 = IN_ARRAY(robeprice, robe_desc_values["robe"]);

	if (what_is_it == 0)
	{
		what_is_it = "robe";
	}

	if (who_name)
		who = find_player(who_name);

	if (!who || E(TO) != E(who))
	{
		if (flag)
			command("say I see my last customer was too impatient to wait "
			+ "for their " + what_is_it + ".");
		else
			command("say I see my last customer was too impatient to wait "
			+ "for the completion of their " + what_is_it + ".");

		command("emote scratches his chin as he goes:  Hmph.");

		if (robe)
        {
			if (flag)
				command("emote places " + what_is_it + " on a nearby rack "
				+ "to be collected later.");
			else
			{
				command("emote places " + what_is_it + " on a nearby rack "
				+ "to be collected later.");
				stock += ([ who_name:robe ]);
			}
        }
		command("say That's business for you.");
		alrm = 0;
		return;
	}

	if (!robe)
	{
		if (flag)
			command("say I have no recollection of an order for a " + what_is_it
			+ " placed by you.");
		else
			command("say Apologies.  Something went wrong with your "
			+ "order.");

		command("shrug");
		alrm = 0;
		return;
	}
	robe->move(TO);
	command("say Your " + what_is_it + ".  Lovely, isn't it?");
    alrm = 0;

	price = calculate_price(robe, who, reduce);

	if (!MONEY_ADD(who, -price))
	{
		command("say You bear insufficient funds.  There are no discounts.");
		command("say Your " + what_is_it + " will be here for you to collect "
		+ "when you can pay.");
		command("emote places " + what_is_it + " on a rack upon the south "
		+ "wall.");
		robe->move(VOID);
		stock += ([ who_name:robe ]);
		return;
	}
    who->catch_msg("You pay the leather worker " + price + " copper coins.\n");

    robe->remove_shadow();

	if (!command("give " + robe->query_name() + " to " + who_name))
		command("drop " + robe->query_name());

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
		command("say I'm crafting an item.  If you can wait a few more "
		+ "moments, I'll be right with you.");
		return 1;
	}

    NF(C(query_verb()) + " what?\n");

	if (!str)
		return 0;

	if (stock[TP->query_real_name()])
	{
		  NF("There is already a robe in stock for you.  Please tender "
		  + "payment for it with <collect> before ordering another.\n");
		  return 0;
	}

    /* syntax is: 'order <style> <colour> <material> <robe>' */
	argdata = explode(str," ");

    NF(C(query_verb()) + " <style> <colour> <material> <robe>.\n");

    if(sizeof(argdata) != 4)
	{ return 0; }

	my_order = compute_all_necessary_robe_data(argdata);

    if (my_order["type"])
	{
		alrm = set_alarm(7.0, 0.0, "finished_robe",
		TP->query_real_name(), my_order["style"],
		my_order["colour"], my_order["material"], my_order["robe"]);
		write("You place your order.\n");
		say(QCTNAME(TP) + " orders an robe.\n");

		command("say Certainly.  Let me begin.  If you are not here when "
		+ "I finish, you may return later to <collect> it.");

		add_prop(TSIT, 1);
		add_prop(LIVE_S_EXTRA_SHORT," is preparing a sharp looking "
		+ argdata[0] + " " + argdata[1] + " " + argdata[2] + " "
		+ argdata[3] + " for sale.");

		set_alarm(5.0, 0.0, "customize_robe", argdata[0], argdata[1],
			argdata[2], argdata[3]);

      return 1;
	}
    NF("You failed to order a valid robe type.  Read the sign again for "
	+ "valid robe choices.\n");
    return 0;
}

void
finished_robe(string for_who, string sty, string col, string mat, string arm)
{
	int k1;
	string gentype;

	k1 = IN_ARRAY(arm, robe_desc_values["robe"]);

	if (k1)
		gentype = MY_ROBE;

	object robe = clone_object(gentype);
    robe->set_armour_data(sty + "&&"
							+ col + "&&"
							+ mat + "&&"
							+ arm + "&&"
							+ "off" + "&&"
							+ "1" + "&&"
							+ "2" + "&&"
							+ "3" + "&&");

    give_out_robe(for_who, robe, 0);
}

int
enquire(string str)
{
    int price;
    string cus, col, mat, art;
	string *argdata;
	mapping my_order;
    NF(C(query_verb()) + " about what?\n");
    if (!str)
      return 0;
    

    /* syntax is: 'enquire <custome'> <colour> <material> <article>' */
	argdata = explode(str," ");
    NF("Are you trying to " + query_verb() + " about <style> "
	   + "<colour> <material> <article>?\n");
    if(sizeof(argdata) != 4)
	{ return 0; }

	my_order = compute_all_necessary_robe_data(argdata);

    if (my_order["type"])
	{
		price = calculate_price(({argdata[2], argdata[3]}), TP, 0);
		command("say An article of that material would cost around "
		+ price + " coppers.");
		return 1;
	}
    return 0;
}

string
exa_it()
{
	return one_of_list(({"a robe", "a coat", "a pair of robes", "a parcel"}));
}

string
exa_it2()
{
	return one_of_list(({"a cloaked short figure", "a cloaked tall figure",
	"a young constable", "a well-dressed squire", "an aging mercenary",
	"a leather robeed male elf", "an old, wide-hatted traveller",
	"a swarthy, stubble-chinned mercenary", "a white-robed woman",
	"a pair of short-cloaked, young noblemen", "a long-bearded dwarf"}));
}

int
react_bow(object actor)
{
	command("emote nods his head without taking his eyes off you for even "
	+ "an instant.");
	return 1;
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "bow")
        set_alarm(1.0, 0.0, &react_bow(actor));
}

string customize_robe(string sty, string col, string mat, string arm)
{
	command("emote searches briefly through the racks finding your "
	+ "order with ease before brushing it off and preparing it for "
	+ "sale.");

	remove_prop(TSIT);
	remove_prop(LIVE_S_EXTRA_SHORT);
	return "";
}
