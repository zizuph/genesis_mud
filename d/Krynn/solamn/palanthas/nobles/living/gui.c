/* Mortis 12.2005
 * 
 * Old, lesser noble with a modest estate off the
 * Court d'Plaisiri.  Wants a cup of coffee (strong morne
 * if it's morning/day, evening vanilla if evening/night),
 * choc biscotti, and a glass of imported wine from
 * anywhere as a second task.  Reward is enchanted bottle
 * of wine that pours its own glasses filled with wine.
 *
 * Quests (er, tasks) can eventually be given an evil
 * equivalent where someone evil in the sewers wants
 * to see Gui stolen from.  Gives them something to
 * distract him with (costs ~same as casks) that allows
 * them to steal a cask from the shelf.  2nd task can
 * be to sneak upstairs through a window outside and
 * steal bottle.
 *
 * Navarre Jan 12th 2008. (Problems Identified by Mercade, THANKS!).
 * needs_help function changed to return string instead of int.
 * Removed third argument '1', from all add_ask.
 * 
 */

#include "../../local.h"
#include CLOCKH
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"


inherit CITIZEN;

#define MY_CLOTHING		NOBLE + "arms/parmour"


void
create_krynn_monster()
{
    set_name("gui");
    set_living_name("gui");
    set_race_name("human");
    set_adj("white-haired");
    add_adj("bushy-sideburned");
    add_name(({"gui", "bursus", "vintner", "human", "lord"}));
    set_title("Bursus, Lord of House Bursus");
    set_long("This elderly gentleman is short, his bushy hair has gone stark " +
	     "white, and he has grown rotund and plump.  Tiny spectacles sit on the " +
	     "end of his nose, and he carries a knobby, wooden cane.\n");
    set_gender(G_MALE);
    set_stats(({50, 45, 80, 170, 160, 85}));
    set_all_hitloc_unarmed(35);
    
    set_skill(SS_AWARENESS, 55);

    set_size_descs("short", "plump");
    set_appearance(2);
    
    set_alignment(400);
    set_knight_prestige(-100);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    
    set_introduce(1);
    set_act_time(12);
    add_act("say Welcome, welcome.  Yes, do come in.");
    add_act("emote smiles frumpily.");
    add_act("smell");
    add_act("emote ponders what wine to acquire next.");
    add_act("@@sip_cof");
    
    add_ask(({"pricelist", "prices", "price", "list", "wine", "wines",
              "cask", "casks", "rack", "racks"}), "say Greetings, yes, interested "
	    + "in wine, are you?  Well though I have amassed quite a collection, I "
	    + "am at present not of a mind to part with any of it except the few "
	    + "casks I traffic as a favour to friends.  I've placed them in the "
	    + "store room section of the cellar, I like to call it.  You may peruse "
	    + "them if you like.", 1);
    add_ask(({"city", "palanthas"}), "say Hmm, Palanthas is an exceptional "
	    + "port of trade for a connoisseur of wines and the finer things.", 1);
    add_ask(({"court", "court d'plaisiri", "plaisir district", "plaisiri"}),
	    "say House Bursus' modest estate has been located off the court for "
	    + "longer than this part of the quarter has been known as the \" "
	    + "pleasure\" district or whatever it is they call it these days.  "
	    + "Still, not an altogether unpleasant place, the court.", 1);
    add_ask(({"service", "services"}), "say I sell a few casks of wine here "
	    + "and there, but the real business in the Court d'Plaisiri "
	    + "is Dienya's fine clothing store, the Mer-Cantile cafe, the "
	    + "Laethorian dayspa, and Jordesse Parfumerie.", 1);
    add_ask(({"dienya", "dienya's", "clothes", "clothing", "clothing store",
		  "fine clothing"}), "say Ahh, Dienya, lovely lady, and her "
	    + "clothes are superb.", 1);
    add_ask(({"mer-cantile", "cafe", "mer-cantile cafe"}), "say The "
	    + "Mer-cantile cafe serves the widest variety of coffees and teas "
	    + "anywhere.  Ask for Lani.  She's very... how to say... friendly.", 1);
    add_ask(({"lani", "barista"}), "say Lani, ahh that fiesty little vixen.  "
	    + "She is the barista at the Mer-Cantile, her father's cafe.  Sent a "
	    + "fellow or two to the stocks for their dalliances.  She's a young one "
	    + "alright.", 1);
    add_ask(({"jordesse", "parfumerie", "jordesse parfumerie"}),
	    "say Vynesse Jordesse is the master behind the design of all the "
	    + "fragrances, but it is her brother Armil who is the face of the "
	    + "business.  I prefer a quaffable bouquet myself.", 1);
    add_ask(({"laethorian", "spa", "dayspa", "laethorian dayspa"}), "say "
	    + "The Laethorian dayspa is a relaxing place if baths, massages, and "
	    + "other pleasurable services are your vice.", 1);
    add_ask(({"task", "help", "quest", "job", "tasks", "quests", "jobs",
		  "favor", "favors", "favour", "favours"}),
	    "@@needs_help");
    add_ask("shirmiaz", "say A Shirmiaz is a specialty wine from an "
	    + "uncommonly dark, rich red grape grown afar.  The Shirmiaz grapes "
	    + "I use in a special wine I personally bottle are grown near "
	    + "pomegranate trees for a unique hint of fruity flavour!", 1);
    add_ask(({"biscotti", "biscottis"}), "say Ahh, yes.  The biscotti are "
	    + "so delicious.  I am partial to chocolate of course.");
    add_ask("coffee", "say My favorites are from the smaller cafes in the "
	    + "Palatial plaza.", 1);
    
    set_default_answer("@@def_answer");
    
    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    seteuid(getuid(TO));
    
    // Gui's custom vest.
    string cusvest = one_of_list(({"buttoned", "checkered", "formal",
				   "pleated", "striped", "paisley"}));
    string colvest = one_of_list(({"brown", "dark-brown", "silvery"}));
    string matvest = one_of_list(({"cotton", "dupion", "silk", "suede"}));
    
    object dvest = clone_object(MY_CLOTHING);
    dvest->set_armour_data("gui" + "&&"
			   + cusvest + "&&"
			   + colvest + "&&"
			   + matvest + "&&"
			   + "vest");
    dvest->move(TO);
    
    // Gui's custom shirt.
    object dshirt = clone_object(MY_CLOTHING);
    dshirt->set_armour_data("gui" + "&&"
			    + "noble" + "&&"
			    + "white" + "&&"
			    + "linen" + "&&"
			    + "shirt");
    dshirt->move(TO);

    // Gui's custom legwear.
    string cuspants = one_of_list(({"pleated", "formal", "cuffed"}));
    string matpants = one_of_list(({"linen", "cotton", "dupion"}));
    
    object dpants = clone_object(MY_CLOTHING);
    dpants->set_armour_data("gui" + "&&"
			    + cuspants + "&&"
			    + "black" + "&&"
			    + matpants + "&&"
			    + "pants");
    dpants->move(TO);
    
    command("wear all");
    MONEY_MAKE_GC(10 + random(15))->move(TO);
    MONEY_MAKE_PC(1 + random(3))->move(TO);
}

string
def_answer()
{
    command("emote goes hmmmmm as he scratches his bushy, white sideburns.");
    command("say I don't believe I know about that.");
    return "";
}

string
needs_help()
{
    if (TP->query_prop("_has_helped_gui2") != 1)
    {
	if (TP->query_prop("_has_helped_gui") !=1)
	{
	    command("say Say there, if you're interested in wine by the cask, "
		    + "perhaps you could do me a small favour.  You see, I am grown "
		    + "feeble in my old age and prefer the cool, wine tempered air of "
		    + "my cellar to the harsh outside world.");
	    command("emote pats his rotund belly and scratches his bushy, white "
		    + "sideburns.");
	    
	    if (GET_TIMEOFDAY == TOD_DAWN || GET_TIMEOFDAY == TOD_DAY)
	    {
		command("say At this hour, a chocolate biscotti with a cup of "
			+ "strong morne coffee to accompany it would be perfect.");
		return "";
	    }
	    command("say At this hour, a chocolate biscotti with a cup of "
		    + "evening vanilla coffee to accompany it would be perfect!");
	    return "";
	}
	write("Gui says:  You did well with my biscotti and coffee, but "
	      + "there is one vice of mine I can never sate.  If you could "
	      + "bring me a new bottle of wine from some far off land, it "
	      + "would so excite me!  Oh and of course, I might then share "
	      + "with you one of mine with a \"special touch\".\n");
	return "";
    }
    write("You have already helped Gui as much as is needed for now.\n");
    return "";
}

/*void
calculate_experience(object who)
{
    int xp_base = 1500;

    if (who->test_bit("ansalon", 0, 10))
    {
	who->catch_msg("Nice job, but no experience second time.\n");

	return;
    }

    who->catch_msg("You feel more experienced!\n");
    if (who->query_wiz_level())
    {
	who->catch_msg("xp: " + xp_base + "\n");
    }

    who->add_exp(xp_base, 0);
    who->set_bit(0, 10);

    return;
}*/

void
give_it_back(object ob, object from)
{
    
    string what, who, whatshort;

    if (!ob || !from)
    {
	return;
    }

    
    what = L(ob->query_name());
    whatshort = L(ob->query_short());
    who = from->query_real_name();
    
    if (!stringp(whatshort) || whatshort[..1] == "@@")
    {
	whatshort = "one";
    }
    
    if (!stringp(what))
    {
	what = "eigblar9";  // Nonsense he'll never give.
    }

    // This prevents runtime errors from command()
    
    if (!who || !stringp(who))
    {
	who = "lars";
    }
    
    if (TP->query_prop("_has_helped_gui") != 1)
    {
	command("say A nice " + whatshort + ", but not what I am looking "
		+ "for at this hour.");
	
	command("give " + what + " to " + who);
	return;
    }
    command("say If you could acquire a wine from far away, I would be "
	    + "grateful.");
    
    command("give " + what + " to " + who);
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

	object rwine;
	string giver = from->query_real_name();

	string obfile = MASTER_OB(ob);
	obfile = obfile[..7];

	if (ob->query_prop("_gui_likes_this_biscotti") == 1)
	{
		if (from->query_prop("_has_given_gui_biscotti") == 1)
		{
			command("say Although I thoroughly enjoy these biscotti, it "
			+ "really is too sweet of you to keep fetching them for me.");
			command("chuckle");
		}
		
		else
		{
			command("say These biscotti are so nice with coffee.");
			from->add_prop("_has_given_gui_biscotti", 1);
		}

		if (from->query_prop("_has_given_gui_coffee") == 1)
		{
			command("sip coffee");
			command("eat biscotti");
			command("say Many thanks!  You may purchase what cask you "
			+ "will from the store room area.");
			from->add_prop("_has_helped_gui", 1);
			return;
		}
		return;
	}

	if (GET_TIMEOFDAY == TOD_DAWN || GET_TIMEOFDAY == TOD_DAY)
	{
		if(ob->short() == "strong morne coffee")
		{
			if (from->query_prop("_has_given_gui_coffee") == 1)
			{
				command("say I do like a good, strong coffee at this time "
				+ "of day, but it really is too good of you to keep fetching "
				+ "it for me.");
				command("smile");
			}
			
			else
			{
				command("say Just what I needed to start my day.");
				command("sip coffee");
				from->add_prop("_has_given_gui_coffee", 1);
			}

			if (from->query_prop("_has_given_gui_biscotti") == 1)
			{
				command("eat biscotti");
				command("say Many thanks!  You may purchase what cask you "
				+ "will from the store room area.");
				from->add_prop("_has_helped_gui", 1);
				return;
			}
			return;
		}
	}

	if (GET_TIMEOFDAY == TOD_TWILIGHT || GET_TIMEOFDAY == TOD_NIGHT)
	{
		if(ob->short() == "evening vanilla roast")
		{
			if (from->query_prop("_has_given_gui_coffee") == 1)
			{
				command("say I do like a good, vanilla coffee at this time "
				+ "of day, but it really is too good of you to keep fetching "
				+ "it for me.");
				command("smile");
				return;
			}

			else
			{
				command("say I do enjoy this roast in the evening.");
				command("sip coffee");
				from->add_prop("_has_given_gui_coffee", 1);
			}

			if (from->query_prop("_has_given_gui_biscotti") == 1)
			{
				command("eat biscotti");
				command("say Many thanks!  You may purchase what cask you "
				+ "will from the store room area.");
				from->add_prop("_has_helped_gui", 1);
				return;
			}
			return;
		}
	}

	if (TP->query_prop("_has_helped_gui") == 1)
	{
	    if (ob->query_name() == "wine" && obfile == "/d/Krynn")
	    {
		command("say Hmm, I've already tried that one.  It's not from "
			+ "very far away, you see.");
		set_alarm(1.0, 0.0, &give_it_back(ob, from));
		return;
	    }

	    if (ob->query_name() == "wine" && obfile == "/std/dri")
	    {
		command("say Eww, that \"wine\" is too simple for my tastes.");
		set_alarm(1.0, 0.0, &give_it_back(ob, from));
		return;
	    }
	    
	    if (ob->query_name() == "wine" && obfile != "/d/Krynn")
	    {
		command("say Wonderful!  I can't decide whether I should add it "
			+ "to my collection or try it right now.");
		command("drink wine");
		if (from->query_prop("_has_helped_gui2") == 0)
		{
		    command("say Unique that.  Well, for helping me yet again, "
			    + "I'd like to share with you this...");
		    from->add_prop("_has_helped_gui2", 1);
		    rwine = clone_object(NOBLE + "obj/shirmiaz_wine");
		    rwine->move(TP);
		    TP->catch_msg("Gui gives you a bottle of Shirmiaz.\n");
		    //				command("give shirmiaz to " + giver);
		    return;
		}
		command("say Hmm, a unique one.  Well, thanks for helping me yet "
			+ "again.");
		return;
	    }
	}
	
	if (ob->query_adj() == "unworn" || ob->query_name() == "coin" || ob->query_name() == "shirmiaz")
	{
		return;
	}
	set_alarm(1.0, 0.0, &give_it_back(ob, from));
	return;
}

void
sip_cof()
{
	if (command("sip coffee"))
	{
		command("sip coffee");
	}

	else
	{
		command("say A cup of coffee would hit the spot about now, yes.");
	}
}
