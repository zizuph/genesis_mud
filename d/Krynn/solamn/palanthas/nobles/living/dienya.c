/* 
 * Base created by Aridor, 06/10/94, wep_smith
 * /d/Krynn/solamn/thief/theiwar/r20
 *
 * Adapted for use in Palanthas by Mortis 12.2005.
 *
 * Major props to Tapakah for spending all day (night over here)
 * teaching me loops and arrays... very complicated arrays...
 * that made my head swell 10%.
 *
 *   Elven mother from ____, merchant capt. from Palanthas.
 * Raised surrogately in city.  Possible quest to find mother.
 *
 * Elfwyr from noble estate, swansdown from merchant house, cashmyr
 * from mt. estate.  Arrasene, dupion, suede, silk,	and messaline
 * finecloth dealer.
 *
 * Possible addition of stories when asked the names of other lands.
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

string she_does2();
string she_tailors();
string she_tailors2(string cloth, string article);
string she_tailors3(string cloth, string colour);
string she_tailors4(string cloth, string article);
string she_tailors5(string custom, string colour, string cloth, string article);

string *armour_desc = ({"custom", "colour", "material", "article"});

mapping armour_desc_values = (["custom":({"alluring", "billowing",
	"buttoned", "checkered", "cuffed", "custom-fitted", "debonair",
	"enchanting", "formal", "fur-trimmed", "gleaming", "heavy", "jaunty", 
	"knitted", "laced", "light", "long", "loose", "low-cut", "noble", "plain",
	"pleated", "rugged", "soft", "shaded", "sharp", "short", "striped",
	"tailored", "tassled", "thick", "thin", "tight", "translucent",
	"unbuttoned", "unlaced"}),
	"colour":({"black", "white", "crimson", "maroon", "pink", "dark-orange",
	"orange", "pale-yellow", "yellow", "forest-green", "dark-green",
	"blue", "pale-blue", "raven-blue", "indigo", "purple", "royal-purple",
	"charcoal", "grey", "brown", "dark-brown", "beige", "tan", "coppery",
	"silvery", "golden"}),
	"material":({"arrasene", "burlap", "cashmyr", "cotton", "dupion",
	"elfwyr", "hemp", "linen", "organdie", "messaline", "sackcloth",
	"silk", "suede", "swansdown", "wool"}),
	"article":({"bathrobe", "vest", "dress", "frock", "gown", "muumuu",
	"shift", "baggy-pants", "capris", "kilt", "lederhosen", "pantaloons",
	"pants", "skirt", "slacks", "stockings", "bodice", "blouse",
	"puffy-shirt", "pullover", "shirt", "sleeveless-shirt", "sweater",
	"gloves", "long-gloves", "scarf"})]);

mapping name_to_class = (["bathrobe":A_ROBE, "vest":A_ROBE,
	"dress":A_BODY | A_ARMS | A_LEGS, "frock":A_BODY | A_ARMS | A_LEGS,
	"gown":A_BODY | A_ARMS | A_LEGS, "muumuu":A_BODY | A_ARMS | A_LEGS,
	"shift":A_BODY | A_ARMS | A_LEGS, "baggy-pants":A_LEGS,
	"capris":A_LEGS, "kilt":A_LEGS, "lederhosen":A_LEGS,
	"pantaloons":A_LEGS, "pants":A_LEGS, "skirt":A_LEGS,
	"slacks":A_LEGS, "stockings":A_LEGS, "bodice":A_BODY,
	"blouse":A_BODY, "puffy-shirt":A_BODY, "pullover":A_BODY,
	"shirt":A_BODY,"sleeveless-shirt":A_BODY, "sweater":A_BODY,
	"gloves":A_HANDS, "long-gloves":A_HANDS | A_ARMS,
	"scarf":A_NECK]);

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
	set_name("dienya");
	set_living_name("dienya");
	add_name(({"half-elf", "tailor"}));
	set_adj("delicate-featured");
	add_adj("almond-eyed");
	set_gender(G_FEMALE);
	set_short("delicate-featured almond-eyed female tailor");
	set_long("The woman before you has pale, smooth skin, delicate features, "
	+ "almond shaped eyes of gold speckled green, and very light, golden "
	+ "brown hair with blond highlights hanging past her shoulders.\n");
	set_race_name("half-elf");
	set_title("Prokleritas, tailor of the finest clothing in Palanthas");
	
	set_size_descs("short", "lean");
	set_appearance(9);
	
	set_skill(SS_DEFENCE,      15);
	set_skill(SS_UNARM_COMBAT, 10);
	set_skill(SS_AWARENESS,    35);
	set_skill(SS_RIDING, 30);

	set_stats(({25, 90, 45, 90, 40, 80}));
	set_all_attack_unarmed(20, 60);
	set_all_hitloc_unarmed(40);

	set_alignment(450);
	set_knight_prestige(-70);
	set_introduce(1);


	set_act_time(10);
	add_act("emote smiles to herself as she straightens "
	+ "@@she_does@@" + " on the counter.");
	add_act("say If I may be of service, you need only ask.");
	add_act("say Good day.  May I be of some service?");
	add_act("say Welcome, is there a specific article of clothing I may "
	+ "help you find?");
	add_act("emote gazes down off to her " + "@@she_does2@@" + " as she "
	+ "arranges " + "@@she_does@@" + " behind the counter.");
	add_act("say For prices try using <inquire> or <enquire> instead of "
	+ "<order>.");
	add_act("say Dress well, live well.  Why not reward yourself with the "
	+ "finest materials and clothing?");

	add_ask(" [about] [how] [to] [do] [i] 'order' / 'ordering' / 'clothes' / 'clothing' / 'tailor' / 'tailoring' ",
	  "say Please have a look at the marble sign behind me. You may also "
	+ "ask me about the materials I have available at the moment and examine "
	+ "the sample rack to check samples of materials and each type of "
	+ "article of clothing I tailor of course.", 1);
	add_ask("service", "say I provide tailoring services.  Please have a "
	+ "at the marble sign behind me.  I can tailor nearly anything for you "
	+ "and have it ready quickly.  If you need to leave while I am "
	+ "tailoring, you may <collect> your item upon return.", 1);
	add_ask(({"price", "prices", "cost", "costs"}), "say Prices vary "
	+ "depending on the article ordered and material from which you'd "
	+ "like it made.  Customized tailoring is my pleasure.  I do not "
	+ "charge extra for it or for dyeing it the colour of your choice.", 1);
	add_ask(({"material", "materials"}), "say Currently, all materials "
	+ "are in stock.", 1); /* This will change if I can manage to set it up
	so you have to do a service to unlock cashmyr, dupion, elfwyr, and
	swansdown. */
	add_ask(({"palanthas", "city"}), "say Palanthas is a city of beauty and "
	+ "very safe.  It has been my home since I was a baby, and the citizens "
	+ "of the district have been very good to me.", 1);
	add_ask("home", "say Palanthas will always be my home.  It's so "
	+ "beautiful here.", 1);
	add_ask("baby", "@@she_does3@@");
	add_ask(({"story", "life"}), "@@she_does4@@");
	add_ask(({"parents", "father"}), "@@she_does6@@");
	add_ask(({"mother", "mom"}), "@@she_does7@@");
	add_ask(({"nanna"}), "@@she_does8@@");
	add_ask(({"tale", "tales"}), "@@she_does9@@");
	add_ask("ending", "@@she_does13@@");
	add_ask("khalakhor", "yawn");
	add_ask("illness", "@@she_does14@@");
	add_ask(({"hagbad", "hagbads", "hagbad's"}), "say Don't eat there!  It "
	+ "will leave a lasting impression on your ummm... insides.", 1);


    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");

}

string
def_answer()
{
	string where;
	where = she_does2();

    command("say I'm sorry.  I'm afraid I don't know much about that.");
	command("emote gazes down off to her " + where
	+ " as if peering across a vast distance.");
    return "";
}

void
arm_me()
{
    seteuid(getuid(TO));

	// Dienya's custom blouse.
	string cusblouse = one_of_list(({"alluring", "low-cut", "unbuttoned",
		"unlaced"}));
	string colblouse = one_of_list(({"translucent-white", "pale-grey",
		"grey-green"}));
	string matblouse = one_of_list(({"elfwyr", "organdie", "messaline",
		"silk", "swansdown"}));

	object dblouse = clone_object(MY_CLOTHING);
    dblouse->set_armour_data("Dienya herself" + "&&"
							+ cusblouse + "&&"
							+ colblouse + "&&"
							+ matblouse + "&&"
							+ "blouse");
	dblouse->move(TO);

	// Dienya's custom legwear.
	string cuspants = one_of_list(({"tight", "low-cut", "jaunty",
		"soft", "shaded"}));
	string colpants = one_of_list(({"black", "pale-grey", "white",
		"grey-green"}));
	string matpants = one_of_list(({"elfwyr", "silk", "swansdown",
		"suede", "arrasene", "dupion"}));
	string artpants = one_of_list(({"skirt", "pants", "baggy-pants",
		"stockings"}));

	object dpants = clone_object(MY_CLOTHING);
    dpants->set_armour_data("Dienya herself" + "&&"
							+ cuspants + "&&"
							+ colpants + "&&"
							+ matpants + "&&"
							+ artpants);
	dpants->move(TO);

	// Dienya's custom gloves.
	string cusgloves = one_of_list(({"shaded", "custom-fitted", "thin",
		"laced", "fur-trimmed", "soft"}));
	string colgloves = one_of_list(({"black", "pale-grey", "white",
		"grey-green", "silvery"}));
	string matgloves = one_of_list(({"elfwyr", "silk", "suede", "dupion"}));
	string artgloves = one_of_list(({"gloves", "long-gloves"}));

	object dgloves = clone_object(MY_CLOTHING);
    dgloves->set_armour_data("Dienya herself" + "&&"
							+ cusgloves + "&&"
							+ colgloves + "&&"
							+ matgloves + "&&"
							+ artgloves);
	dgloves->move(TO);

	command("wear all");
	MONEY_MAKE_PC(random(2))->move(TO);
	MONEY_MAKE_GC(15 + random(25))->move(TO);

}

void
init_living()
{
    add_action("order","order");
    add_action("enquire","enquire");
	add_action("enquire","inquire");
    add_action("collect","collect");
    ::init_living();
}

int
collect(string str) //eliminate query_reduce_pay() here?
{
    object clothing;
    if (alrm)
      {
      command("say I am already tailoring an article for a customer.  If you "
	  + "could wait a few minutes, I will be right with you.");
      return 1;
      }
    command("say Yes, of course.  You have returned for your order.");
    command("emote turns around and starts searching a rack full of clothes.");
    command("say Here it is.  I do hope you are pleased.");
    clothing = stock[TP->query_real_name()];
    alrm = set_alarm(2.0,0.0,"give_out_clothing",TP->query_real_name(),
             clothing, 1, clothing->query_reduce_pay());
    return 1;
}
/*
 * returns an array: ({ armour type, armour ac, time to make })
 */
mapping compute_all_necessary_armour_data(string *argdata)
{
	int typ1, i, j, k;
	mapping order;
	order = (["type":0,"colour":"","custom":"","colour":"","material":"","article":""]);

	for(i=0,j=sizeof(armour_desc);i<j;i++)
	{
		k = member_array(argdata[i],armour_desc_values[armour_desc[i]]);
		if (k == -1)
			{
			command("say I'm sorry, but " + argdata[i] + " is not an "
			+ "available " + armour_desc[i] + " choice.");
			return (["type":0]); /*invalid armour*/
			}
		order[armour_desc[i]] = armour_desc_values[armour_desc[i]][k];
	}

	order["type"] = name_to_class[order["article"]];

	return order;
}

int
calculate_price(mixed ob, object for_who, int reduce)
{
    int price, mfactor, afactor;
	string af = "";
	string mf = "";

	/* This if ob is an object from give_out_clothing*/
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

	if (IN_ARRAY(af, ({"bathrobe", "dress", "frock", "gown", "muumuu",
		"shift"})))
	{ afactor = 3; }

	if (IN_ARRAY(af, ({"vest", "baggy-pants", "capris", "kilt",
		"lederhosen", "pantaloons", "pants", "skirt", "slacks",
		"stockings", "bodice", "blouse", "puffy-shirt", "pullover",
		"shirt", "sweater"})))
	{ afactor = 2; }

	if (IN_ARRAY(af, ({"sleeveless-shirt", "gloves", "long-gloves",
		"scarf"})))
	{ afactor = 1; }

	if (IN_ARRAY(mf, ({"burlap", "sackcloth", "hemp"})))
	{ mfactor = 2; }

	if (IN_ARRAY(mf, ({"cotton", "linen", "organdie", "wool"})))
	{ mfactor = 3; }

	if (IN_ARRAY(mf, ({"arrasene", "dupion", "suede", "silk",
		"messaline"})))
	{ mfactor = 5; }

	if (IN_ARRAY(mf, ({"cashmyr", "swansdown"})))
	{ mfactor = 9; }

	if (IN_ARRAY(mf, ({"elfwyr"})))
	{ mfactor = 18; }

	price = 1 + afactor * mfactor;
    price = price * (150 - (for_who->query_skill(SS_TRADING) / 2));
	// reduce can be used for discounts for groups
    return price * (100 - reduce) / 100 - 10 + random(20); 
}

void
give_out_clothing(string who_name, object clothing, int flag, int reduce)
{
	int price;
	object who;
	string what_is_it = clothing->short();
	
	if (what_is_it == 0)
	{
		what_is_it = "article of clothing";
	}

	if (who_name)
		who = find_player(who_name);
	if (!who || E(TO) != E(who))
	{
		if (flag)
		command("say I suppose my last customer was too busy to pick up "
		+ "their " + what_is_it + ".");
		else
		command("say I suppose my last customer was too busy to see the "
		+ "completion of their " + what_is_it + ".");
		command("emote smiles demurely as she gazes down.");
		if (clothing)
        {
			if (flag)
			command("emote hangs " + what_is_it + " on a clothing rack "
			+ "behind the counter to be collected later.");
			else
			{
			command("emote hangs " + what_is_it + " on a clothing rack "
			+ "behind the counter to be collected later.");
			stock += ([ who_name:clothing ]);
			}
        }
		command("say Oh well.");
		alrm = 0;
		return;
	}
	if (!clothing)
	{
		if (flag)
		command("say Actually... I'm sorry, but I cannot find an order for "
		+ "any " + what_is_it + " placed by you.");
		else
		command("say I'm sorry.  Something went terribly wrong with your "
		+ "order.");
		command("emote gives you a gentle half-smile.");
		alrm = 0;
		return;
	}
	clothing->move(TO);
	command("say There you are.  May your " + what_is_it + " be all you "
	+ "were looking for.");
    alrm = 0;

    /*pay in here!*/
	price = calculate_price(clothing, who, reduce);
	if (!MONEY_ADD(who, -price))
	{
		command("say I'm sorry, but you're short a few coins.");
		command("say I'll keep the " + what_is_it + " here for you in stock.");
		command("emote smiles politely as she gazes down, her cheeks "
		+ "reddening for a moment.");
		clothing->move(VOID);
		stock += ([ who_name:clothing ]);
		return;
	}
    who->catch_msg("You pay the tailor " + price + " copper coins.\n");

    clothing->remove_shadow();

    if (!command("give " + clothing->query_name() + " to " + who_name))
      command("drop " + clothing->query_name());
    stock = m_delete(stock, who_name);
    if (enter_alrm)
      {
      remove_alarm(enter_alrm);
      enter_alrm = 0;
      }
}

int
order(string str) //set to 25 seconds until finished_armour
{
	string cus, col, mat, art;
	string *argdata;
	mapping my_order;

    if (alrm)
      {
      command("say I am already tailoring an article for a customer.  If you "
	  + "could wait a minute, I will be right with you.");
      return 1;
      }
    NF(C(query_verb()) + " what?\n");
    if (!str)
      return 0;
    if (stock[TP->query_real_name()])
      {
      NF("There is already an article of clothing in stock for you.  "
	  + "Would you collect it first?\n");
      return 0;
      }
    /* syntax is: 'order <custome'> <colour> <material> <article>' */
	argdata = explode(str," ");
    NF(C(query_verb()) + " <custome'> <colour> <material> <article>.\n");
    if(sizeof(argdata) != 4)
	{ return 0; }

	my_order = compute_all_necessary_armour_data(argdata);

    if (my_order["type"])
	{
		alrm = set_alarm(24.5, 0.0, "finished_armour",
		TP->query_real_name(),my_order["type"], my_order["custom"],
			my_order["colour"], my_order["material"], my_order["article"]);
		write("You place your order.\n");
		say(QCTNAME(TP) + " orders an article of clothing.\n");

		command("say This will only take a moment, but you are welcome to "
		+ "return later to <collect> it.");

		add_prop(TSIT, 1);
		add_prop(LIVE_S_EXTRA_SHORT," is sitting behind the counter "
		+ "tailoring a high quality " + argdata[0] + " " + argdata[1] + " "
		+ argdata[2] + " " + argdata[3]);

		set_alarm(2.0, 0.0, "she_tailors");
		set_alarm(6.0, 0.0, "she_tailors2", argdata[2], argdata[3]);
		set_alarm(11.0, 0.0, "she_tailors3", argdata[2], argdata[1]);
		set_alarm(17.0, 0.0, "she_tailors4", argdata[2], argdata[3]);
		set_alarm(23.0, 0.0, "she_tailors5", argdata[0], argdata[1],
			argdata[2], argdata[3]);

      return 1;
	}
    NF("You failed to order an article of clothing.\n");
    return 0;
}

void
finished_armour(string for_who, int typ1, string cus, string col,
				string mat, string art)
{

	object clothing = clone_object(MY_CLOTHING);
    clothing->set_armour_data(for_who + "&&"
//							+ typ1 + "&&"
							+ cus + "&&"
							+ col + "&&"
							+ mat + "&&"
							+ art);
//	clothing->set_at(typ1);

    give_out_clothing(for_who, clothing, 0, 0);
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
    NF("Are you trying to " + query_verb() + " about <custome'> "
	   + "<colour> <material> <article>?\n");
    if(sizeof(argdata) != 4)
	{ return 0; }

	my_order = compute_all_necessary_armour_data(argdata);

    if (my_order["type"])
	{
		price = calculate_price(({argdata[2], argdata[3]}),TP,0);
//		price = calculate_price(({mat, art}),TP,0);
		command("say An article of that material would cost around "
		+ price + " coppers.");
		return 1;
	}
    return 0;
}

string
she_does()
{
	return one_of_list(({"a spindle of thread", "a stack of patterns",
	  "a bolt of cloth", "a set of incredibly fine needles"}));
}

string
she_does2()
{
	return one_of_list(({"left", "right"}));
}

string
she_does3()
{
	string where = "";
	where = she_does2();

	command("say I was raised here since I was a baby, but you don't "
	+ "want to hear the story of my life.");
	command("emote gazes down to her " + where + " as she smiles "
	+ "demurely.");
	return "";
}

string
she_does4()
{
	string where = "";
	where = she_does2();

	command("emote looks up blinking in puzzlement as she cocks her head "
	+ "to the " + where + ", narrowing her almond shaped eyes "
	+ "of gold speckled green in thought.");
	command("say Most people do not stop to ask.");
	command("smile thoughtfully");
	set_alarm(2.5, 0.0, "she_does5");
	return "";
}

string
she_does5()
{
	command("say My parents were not together long.  I was left in the "
	+ "city under the care of my nanna and well cared for though often "
	+ "lonely.");
	command("gesture at her slightly pointed ears");
	command("shrug briefly");
	return "";
}

string
she_does6()
{
	command("say My father was a man of Palanthas.  He spent his life on "
	+ "the sea, visiting only occasionally to see to our estate and visit "
	+ "me.  He was a great navigator and saw many far off lands.  He "
	+ "would tell me tales of them, but that was long ago, and he is "
	+ "gone now.");
	command("smile fond");
	return "";
}

string
she_does7()
{
	command("emote gazes down at the counter, her cheeks deflated and lips "
	+ "pursed.");
	command("say I never knew my mother.  I asked father many times, but he "
	+ "would never say.  His eyes would water whenever I brought her up, and "
	+ "he would go off to be alone so I stopped troubling him about her.  He "
	+ "must have loved her very much.  Some day I hope to hear of her though "
	+ "I have not the faith to believe we will ever see each other again.");
	return "";
}

string
she_does8()
{
	command("emote smiles softly and a light sparkles in her almond shaped "
	+ "eyes of gold speckled green.");
	command("say Nanna was a kind, little lady from Mt. Nevermind.  She "
	+ "cared for me and raised me from a little baby.  It was from her I "
	+ "learned all I know about tailoring.  She is gone now, but I will "
	+ "never forget her.");
	return "";
}

string
she_does9()
{
	command("say Father used to tell me tales of his voyages to foreign "
	+ "lands.  They were always exciting and fantastic.  Would you like "
	+ "to hear one?");
	set_alarm(3.0, 0.0, "she_does10");
	return "";
}

string
she_does10()
{
	command("hmm");
	command("emote tries to think of a good one.");
	command("say There was the time father sailed to Khalakhor, looked "
	+ "at some walls, and delivered some letters, but he never returned "
	+ "there and, come to think of it, it wasn't very exciting.");
	set_alarm(3.5, 0.0, "she_does11");
	return "";
}

string
she_does11()
{
	command("say Then there was the time he visited the subterranean land "
	+ "of Sybarus.  He said they had an exceptionally renowned school, but "
	+ "wouldn't give me any details of their city or its great bazaar.  He "
	+ "said it was too indecent.  I would like to see for myself, but my "
	+ "home is here.");
	set_alarm(3.0, 0.0, "she_does12");
	return "";
}

string
she_does12()
{
	command("emote twinkles her almond shaped eyes of gold speckled green "
	+ "brightly.");
	command("say Ahh, yes.  I was always fond of the tale of his visit to "
	+ "the Shire in Middle-Earth.  Long ago when father navigated the "
	+ "merchant ship \"The Spine Tingler\", they landed in the Grey Havens.  "
	+ "The captain was too sick with a mysterious illness to leave his cabin "
	+ "so he bid my father lead the caravan east to the Shire to fulfill "
	+ "a large order of swansdown cloth and clothing in a small hobbit "
	+ "community in the hills.");
	command("say He and the wagons arrived that evening and were very well "
	+ "received by the hobbitfolk.  As it was growing late and there were "
	+ "no inns for men nearby, he was invited to stay at the home of a "
	+ "prominent hobbit, a Mr. Bilbo Baggins if I recall correctly.  "
	+ "Concerned for the small hobbit's provisions, a concern which he "
	+ "later discovered most unwarranted, he offered to share what food "
	+ "the caravan had brought with them.  Well, Mr. Baggins was most "
	+ "excited about the cuisine from Palanthas and warily curious about "
	+ "the coffee, and they all sat down at his dinner table to eat.");
	command("fidget");
	command("say The ending is well... not for the faint of heart.");
	return "";
}

string
she_does13()
{
	string where = "";
	where = she_does2();

	command("emote gazes down off to her " + where + " as she "
	+ "smiles deviously to herself.");
	command("say Father recalled hearing and paying little mind to a fair "
	+ "deal of rumbling throughout the meal but brushed it off as an "
	+ "oddity of local weather.  Anyway, midway through the meal Bilbo, "
	+ "who had skillfully consumed a good deal of all the varieties of "
	+ "food they had brought, stood up in his stylish, new swansdown "
	+ "pants and proposed a toast to the good men of Palanthas.");
	command("say \"For "
	+ "their soft swansdown, good vittles, and their coffee, which is almost "
	+ "but not entirely quite unlike a good Shire tea, as well as their "
	+ "splendid fellowship, I propo-... \" began Mr. Baggins stopping "
	+ "abruptly as he dropped his glass of wine onto the table and "
	+ "clutched vehemently at his bowels.  \"Noooo!  Valar, why?!?\" he "
	+ "cried out, his free hand raised to the sky as he backed away from "
	+ "the table, knocking his chair over, and stumbling dangerously close "
	+ "to the fireplace.  A thundering \"Boom!\" shook the room as Mr. "
	+ "Baggins doubled over and a massive fart ruptured out of the seat "
	+ "of his new, swansdown pants, ignited in the fireplace, and sent "
	+ "him flying across the table and out the window like one of the "
	+ "grey traveller's fireworks rockets!");
	command("laugh");
	command("emote wipes the tears from her eyes still giggling.");
	command("say As it turns out, \"The Spine Tingler's\" normal order "
	+ "of sausages had fallen through and replacements were procured from "
	+ "Hagbad's instead and well, I don't recommend eating there and nor "
	+ "will the hobbits now.  But it all turned out well as Mr. Baggins "
	+ "found the trip a joyous surprise, although he did turn down any "
	+ "further offerings from the men.");
	command("gesture how much she liked that tale");
	return "";
}

string
she_does14()
{
	command("emote laughs with the twitter of a nightingale singing.");
	command("say Bowel rot from eating at Hagbad's.");
	return "";
}

int
react_bow(object actor)
{
	string who = QTNAME(actor);

    if (actor)
    {
        if(actor->query_gender() == 0)
        {
			command("say Oh!  A gentleman.");
            command("blush");
			set_alarm(1.5,0.0,"reward_bow", who);
			return 1;
        }
		command("curtsey");
		command("say Well met, " + who + ".  You are welcome here.");
		command("gesture with a welcoming wave");
        return 1;
    }
}

void
reward_bow(string who)
{
    command("bow");
	command("say You are welcome here, " + who + ".");
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "bow")
        set_alarm(1.0, 0.0, &react_bow(actor));
}

string she_tailors()
{
	command("emote picks out a few sewing needles, takes a stack of "
	+ "patterns out from beneath the counter, and sits down to her work.");
	return "";
}

string she_tailors2(string cloth, string article)
{
	command("emote measures and cuts a length of " + cloth + " from a bolt "
	+ "behind the counter and begins to cut it into the patterns that will "
	+ "become the " + article + ".");
	return "";
}

string she_tailors3(string cloth, string colour)
{
	command("emote takes great care as she places the patterns of " + cloth 
	+ " in the dye press behind the counter and pulls the handle releasing "
	+ "the " + colour + " dye with a brief hissing noise.");
}

string she_tailors4(string cloth, string article)
{
	command("emote removes the now dry " + cloth + " cloth from the dye "
	+ "press and sets to sewing the patterns together into what is "
	+ "beginning to resemble the " + article + " now.");
	command("emote softly sings a lilting, wordless melody to herself.");
}

string she_tailors5(string custom, string colour, string cloth, string article)
{
	command("emote smiles warmly to herself as her fine needle and thread "
	+ "apply the finishing touches to the " + colour + " " + cloth + " "
	+ article + " that will make it " + custom + ".");
	command("emote dabs at her forehead with a white, silk handkerchief as "
	+ "she declares:  There, finished.");

	remove_prop(TSIT);
	remove_prop(LIVE_S_EXTRA_SHORT);
	return "";
}
