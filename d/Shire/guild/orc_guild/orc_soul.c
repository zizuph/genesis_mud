 /* 
	*orc_soul.c
	*contains emotes for the Middle Earth orc race guild
	*Altrus, May 2005

        *Added leftover add_name to orip
        *Arman, September 2020
 */

#pragma save_binary
//#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Shire/lib/inn";
//inherit "/std/leftover";

#include <macros.h>
#include <formulas.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include <files.h>
#include <time.h>
#include <std.h>
#include <wa_types.h>
#include <options.h>
#include <adverbs.h>
#include <cmdparse.h>
#include <options.h>


#include "/d/Shire/sys/defs.h"
#include "orc.h"
#include "olist.h"
//#include "oidea.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define MORE(x)   this_player()->more(read_file(x,2))
#define PLANTED "_standard_is_planted"
#define IS_STANDARD "_standard_for_orcs"
#define IS_LASHED "_standard_is_lashed"
#define IS_PAINTED "_standard_is_painted"

void prep_wep(object player, int stage);
void prep_cloak(object player, int stage);

string get_soul_id()
{
    return "Orcs of Middle Earth";
}

int
query_cmd_soul()
{
    return 1;
}

mapping query_cmdlist()
{

    setuid();
    seteuid(getuid());

    return ([
	"help"			: "do_help",
	"olist"         : "list_active_orcs",
	//"oidea"		: "orc_idea",
	"orclist"      	: "list_active_orcs",
	"ogreet"		: "orc_greet",
	"oeat"  		: "orc_eat",
	"ocrave"        : "orc_crave",
	"oscratch"		: "orc_scratch",
	"onotice"	 	: "orc_notice",
	"ogrunt"        : "orc_grunt",
	"ogrin"			: "orc_grin",
	"olaugh"		: "orc_laugh",
	"oassert"       : "orc_assert",
	"osniff"        : "orc_sniff",
	"ostance"    	: "orc_stance",
	"ogreed"        : "orc_greed",
	"omalice"       : "orc_malice",
	"oseethe"		: "orc_seethe",
	"olust"			: "orc_bloodlust",
	"ohowl"         : "orc_howl",
	"obattle"      	: "orc_battlecry",
	"ohate"         : "orc_hatred",
	"ocurse"   		: "orc_curse",
	"owhimper"   	: "orc_whimper",
	"ospeak"		: "orc_speak",
	"osp"			: "orc_speak",
	"oshow"			: "toggle_title",
	"ohide"			: "toggle_title",
	"oprep"			: "prep_pole",
	"omake"			: "make_pole",
	"orip"			: "rip_corpse",
	"ohead"			: "cap_head",
	"oplant"		: "plant_standard",
	"opaint"		: "paint_standard",
	//"olash"		: "lash_standard",
	//"oremove"		: "remove_standard",
	]);
}
/*
* 	toggle_title: Will allow orcs to obscure their titles.
*/
int
toggle_title(string str)
{

	notify_fail(CAP(query_verb()) + " what?\n");
    if(!str)
        return 0;

    notify_fail(CAP(query_verb()) + " what?\n");
    if (!parse_command(str, ({ }), " [the] 'title' / 'titles' "))
        return 0; 

	if (!this_player()->query_hide_title())
	{
		write("You chose to hide your orcish heritage.\n");
		this_player()->set_hide_title(1);
		return 1;
	}

	if (this_player()->query_hide_title())
	{
		write("You proudly display your orcish heritage.\n");
		this_player()->set_hide_title(0);
		return 1;
	}
}

int
do_help(string str)
{
	setuid(); 
	seteuid(getuid());
	switch (str)
	{
		case "orc":
			MORE(ORC_HELP + "general");
			TP->catch_tell("Please report any problems you may encounter "+
			"with the "+ ORC_RACE_GUILD_NAME +" to "+
			COMPOSITE_WORDS(map(ORC_RACE_GUILD_MASTER, capitalize)) + ".\n");
			break;
		
		case "orc emotions":
			MORE(ORC_HELP + "emotes");
			break;
		
		case "orc news":
			MORE(ORC_HELP + "news");
			break;
		
		case "orc standard":
			MORE(ORC_HELP + "standard");
			break;
		
		default:
		return 0;
	}
    return 1;
}

/*
	*orc_greet, greets the target in typical orcish rudeness
*/
int orc_greet(string str)
{
	object *oblist;
	if(!strlen(str)) /* no string supplied */
	{
		write("Greet who in orcish fashion?\n");
		return 1;
	}
	
	oblist = parse_this(str, "[the] %l");
	
	if(!sizeof(oblist))
	{
		write("There is no one to greet.\n");
		return 1;
	}
	
	actor("You growl a blunt greeting at", oblist,".");
	target(" growls a blunt greeting at you.", oblist);
	all2act(" growls a blunt greeting at", oblist, ".");
	return 1;
}

/*
	*orc_crave, orc craves some meat to eat
*/
int orc_crave()
{
	write("You are seriously craving some blood-dripping flesh!\n");
	say(QCTNAME(TP) + " looks like " + HE_SHE(TP) + " is really craving some meat!\n");
	return 1;
}

/*
	*orc_crave, orc craves some meat to eat
*/
int orc_scratch()
{
	write("You scratch yourself all over, causing filth to fall to the ground.\n");
	say("As " + QCTNAME(TP) + " scratches " + HIM_HER(TP) + "self vigorously, bits of filth fall to the ground.\n");
	return 1;
}

/*
	*orc_notice, acknowledge someone's presence, but letting them know how the predator is
*/
int orc_notice(string str)
{
	object *oblist;
	if(!strlen(str)) /* no string supplied */
	{
		write("Take notice of who as lower on the food-chain?\n");
		return 1;
	}
	
	oblist = parse_this(str, "[the] %l");
	
	if(!sizeof(oblist))
	{
		write("There is no one here of whom take notice.\n");
		return 1;
	}
	
	actor("You take notice of", oblist,", who looks quite tasty.");
	target(" seems to notice you standing there, looking at you rather hungrily.", oblist);
	all2act(" looks hungrily at", oblist, ".");
	return 1;
}

/*
	*orc_grunt, an affirmative answer
*/
int orc_grunt()
{
	write("You grunt in affirmation.\n");
	say(QCTNAME(TP) + " nods " + HIS_HER(TP) + " head and grunts quietly.\n");
	return 1;
}

/*
	*orc_grin, grin with all your teeth
*/
orc_grin(string str)
{
	object *oblist;
	if(!strlen(str)) /* no string supplied */
	{
		write("You show your sharp teeth in a broad grin.\n");
		say(QCTNAME(TP) + " bares " + HIS_HER(TP) + " sharp teeth in a poor attempt at a grin.\n");
		return 1;
	}
	
	oblist = parse_this(str, "[the] %l");
	
	if(!sizeof(oblist)|| str=="all")
	{
		write("Grin at whom?\n");
		return 1;
	}
	
	actor("You show your sharp teeth to",oblist," in a broad grin.");
	target(" bares " + HIS_HER(TP) + " sharp teeth at you in a poor attempt at a grin.", oblist);
	all2act(" bares " + HIS_HER(TP) + " sharp teeth at", oblist," in a poor attempt at a grin.");
	return 1;
}

/*
	*orc_laugh, laugh loud, showing teeth
*/
int orc_laugh()
{
	write("You bare your sharp teeth in cruel laugher.\n");
	say(QCTNAME(TP) + " bares " + HIS_HER(TP) + " sharp teeth in cruel laughter.\n");
	return 1;
}

/*
	*orc_assert, asserts pack dominance
*/
int orc_assert(string str)
{
	object *oblist;
	if(!strlen(str)) /* no string supplied */
	{
		write("Assert your dominance over whom?\n");
		return 1;
	}
	
	oblist = parse_this(str, "[the] %l");
	
	if(!sizeof(oblist))
	{
		write("There is no one here to dominate.\n");
		return 1;
	}
	
	actor("You stare down", oblist,", attempting to assert dominance.");
	target(" stares at you with ferocity in " + HIS_HER(TP) + " eyes, asserting dominance.", oblist);
	all2act(" stares at", oblist, " with ferocity, asserting " + HIS_HER(TP) + " dominance.");
	return 1;
}

/*
	*orc_sniff, try to pick up a scent
*/
int orc_sniff()
{
	write("You sniff the ground momentarily, trying to catch a scent.\n");
	say(QCTNAME(TP) + " sniffs the ground for a moment, attempting to pick up a scent.\n");
	return 1;
}


/*
	*orc_stance, take a fighting stance
*/
int orc_stance()
{
	write("You crouch low, ready to fight.\n");
	say(QCTNAME(TP) + " crouches low, bareing fangs. " + CAP(HE_SHE(TP)) + " looks ready for a fight.\n");
	return 1;
}

/*
	*orc_greed, look at someone with greed in your eyes, or just look with greed in general
*/
orc_greed(string str)
{
	object *oblist;
	if(!strlen(str)) /* no string supplied */
	{
		write("You get a greedy look in your eyes.\n");
		say(QCTNAME(TP) + "'s eyes widen with greed.\n");
		return 1;
	}
	
	oblist = parse_this(str, "[the] %l");
	
	if(!sizeof(oblist)|| str=="all")
	{
		write("Look at who with greed?\n");
		return 1;
	}
	
	actor("You stare at",oblist," with absolute greed.");
	target(" stares at you with absolute greed.", oblist);
	all2act(" stares at", oblist," with absolute greed.");
	return 1;
}

/*
	*orc_malice, look at someone with malice in your eyes, or just look with malice in general
*/
orc_malice(string str)
{
	object *oblist;
	if(!strlen(str)) /* no string supplied */
	{
		write("You narrow your eyes, feeling nothing but malice.\n");
		say(QCTNAME(TP) + "'s eyes narrow in malice.\n");
		return 1;
	}
	
	oblist = parse_this(str, "[the] %l");
	
	if(!sizeof(oblist)|| str=="all")
	{
		write("Look at who with malice?\n");
		return 1;
	}
	
	actor("You stare at",oblist," with malice.");
	target(" stares at you with malice in " + HIS_HER(TP) + " eyes.", oblist);
	all2act(" stares at", oblist," with malice in " + HIS_HER(TP) + " eyes.");
	return 1;
}

/*
	*orc_seethe, seethe with hatred towards someone
*/
int orc_seethe(string str)
{
	object *oblist;
	if(!strlen(str)) /* no string supplied */
	{
		write("Seethe with hatred at whom?\n");
		return 1;
	}
	
	oblist = parse_this(str, "[the] %l");
	
	if(!sizeof(oblist))
	{
		write("There is no one here to hate.\n");
		return 1;
	}
	
	actor("You seethe with hatred towards", oblist,".");
	target(" seethes with hatred towards you.", oblist);
	all2act(" seethes with hatred towards", oblist, ".");
	return 1;
}

/*
	*orc_bloodlust, be overcome with bloodlust
*/
int orc_bloodlust()
{
	write("You are overcome with the lust for battle and blood!\n");
	say(QCTNAME(TP) + "'s eyes redden as " + HE_SHE(TP) + " is overcome with bloodlust!\n");
	return 1;
}

/*
	*orc_howl, howl in rage
*/
int orc_howl()
{
	write("You howl loudly in rage!\n");
	say(QCTNAME(TP) + " howls loudly in rage!\n");
	return 1;
}

/*
	*orc_battlecry, the orcish battlecry
*/
int orc_battlecry()
{
	write("You roar in orcish fury!\n");
	say(QCTNAME(TP) + " roars in mindless fury!\n");
	return 1;
}

/*
	*orc_hatred, the orc's long standing hatred of elves
*/
int orc_hatred()
{
	write("You tell everyone about your hatred for the elves.\n");
	say(QCTNAME(TP) + " expresses " + HIS_HER(TP) + " hatred for elves.\n");
	return 1;
}

/*
	*orc_curse, curse the elves!
*/
int orc_curse()
{
	write("You loudly curse elven-kind!\n");
	say(QCTNAME(TP) + " loudly shouts, 'Curse the elves!'\n");
	return 1;
}

/*
	*orc_whimper, damn sun
*/
int orc_whimper()
{
	write("You whimper in pain at the sight of the sun.\n");
	say(QCTNAME(TP) + " whimpers in pain at the sight of the sun.\n");
	return 1;
}


/*
 * ospeak - borrowed from noldor speaking, added observation by third party
 */
int orc_speak(string str)
{
	object oActor = this_player ();
	int    iListener;
	object oListener;
	object *aoListeners;
	
	notify_fail ("What do you want to say?\n");
	
	if (!strlen (str)) return (0);
	
	write ("You utter in the black tongue: " + str + "\n");

	aoListeners = FILTER_LIVE (all_inventory (environment (oActor)) - ({ oActor }));
	for (iListener = 0 ; iListener < sizeof (aoListeners) ; iListener ++)
	{
		oListener = aoListeners [iListener];
		if(MAGE_MEMBER (oListener))
		{
			oListener->catch_tell (oActor->query_The_name (oListener) + " utters in the dialect of the slaves: " + str + "\n");
		}
		
		else if(IS_MEMBER (oListener))
		{
			oListener->catch_tell (oActor->query_The_name (oListener) + " utters in the black tongue: " + str + "\n");
		}
		
		else if(URUK_MEMBER (oListener))
		{
			oListener->catch_tell (oActor->query_The_name (oListener) + " utters in the black tongue: " + str + "\n");
		}
		
		else if(!TP->query_wiz_level())
		{
			oListener->catch_tell (oActor->query_The_name (oListener) + " utters in the black tongue: " + str + "\n");
		}
		
		else	
		{
			oListener->catch_tell (oActor->query_The_name (oListener) + " utters something unintelligible in the black tongue.\n");
		}
		
	}
	
	return (1);
}

void create_pole(object weapon)
{
	object pole;
	
	setuid();
	seteuid(getuid());
	
	pole = clone_object(ORCGLD_DIR + "obj/banner_pole");
	
	write("You begin work preparing the " + weapon->short() + ".\n");
	say(QCTNAME(TP)+ " starts working on " + HIS_HER(TP) + " " + weapon->short() + ".\n\n",TP);
	set_alarm(3.0,0.0, &prep_wep(TP, 1));
	
	pole->move(this_player());
	weapon->remove_object();
}

void create_cloth(object cloak)
{
	object cloth;
	
	setuid();
	seteuid(getuid());
	
	cloth = clone_object(ORCGLD_DIR + "obj/banner_cloth");
	
	write("You begin work preparing the " + cloak->short() + ".\n");
	say(QCTNAME(TP)+ " starts working on " + HIS_HER(TP) + " " + cloak->short() + ".\n\n",TP);
	set_alarm(3.0,0.0, &prep_cloak(TP, 1));
	
	cloth->move(this_player());
	cloak->remove_object();
}

int prep_pole(string str)
{
	int s;
	mixed *item;

	if (!strlen(str))
	{
		write("Prepare what for use as a battle standard?\n");
		return 1;
	}

   
	str = lower_case(str);
    
	if (!parse_command(str, all_inventory(this_player()), "[the] %i", item))
	{
		write("Prepare what for use as a battle standard?\n");
		return 1;
	}

	item = NORMAL_ACCESS(item, 0, 0);
	s = sizeof(item);

	if (s > 1)
	{
		write("You can only work on one item at a time.\n");
		return 1;
	}

	if (!s)
	{
		write("Prepare what for use as a battle standard?\n");
		return 1;
	}

	if (item[0]->query_prop(OBJ_I_BROKEN))
	{
		write("It's broken, so it probably wont work well enough for a battle standard.\n");
		return 1;
	}
	
	if (item[0]->query_wt() != W_POLEARM && item[0]->query_name() != "cloak" && item[0]->query_name() != "robe" && item[0]->query_name() != "pelt")
	{
		write("You can only prepare your standard from cloaks and polearms.\n");
		return 1;
	}
	
	if(item[0]->query_prop(MAGIC_AM_MAGIC) || item[0]->query_prop(OBJ_I_IS_MAGIC_WEAPON) || item[0]->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
	{
		write("But it is obviously much too valuable for use as a battle standard.\n");
		return 1;
	}
	
	if (item[0]->query_wt() != W_POLEARM)
	{
		if(item[0]->query_worn() != 0)
		{
			write("But you're wearing it!\n");
			return 1;
		}
		
		create_cloth(item[0]);
		return 1;
	}
	
	if(item[0]->query_wielded() != 0)
	{
		write("But you're wielding it!\n");
		return 1;
	}
	
	create_pole(item[0]);
	return 1;
}

void prep_wep(object player, int stage)
{
	float time;
	
	set_this_player(player);
	switch (stage)
	{
		case 1:
		write("\nYou turn the weapon in your hands.\n");
		say(QCTNAME(TP)+ " does some work with " + HIS_HER(TP) + " hands.\n",TP);
		time = 2.5;
		break;
		case 2:
		write("\nYou shave off uneeded material.\n");
		say(QCTNAME(TP)+ " tosses away uneeded material.\n",TP);
		time = 1.5;
		break;
		case 3:
		write("\nYou sharpen up the butt-end.\n");
		say(QCTNAME(TP)+ " sharpens the pole " + HE_SHE(TP) + " is working on.\n",TP);
		time = 5.0;
		break;
		default:
		write("\nYou stop working, your pole is ready for a banner.\n\n");
		say("\n"+QCTNAME(TP)+" stops working.\n\n",TP);
		return;
	}
	set_alarm(time, 0.0, &prep_wep(player, ++stage));
}

void prep_cloak(object player, int stage)
{
	float time;
	
	set_this_player(player);
	switch (stage)
	{
		case 1:
		write("\nYou spread out the material.\n");
		say(QCTNAME(TP)+ " spreads out " + HIS_HER(TP) + " material.\n",TP);
		time = 3.5;
		break;
		case 2:
		write("\nYou cut off anything not needed.\n");
		say(QCTNAME(TP)+ " makes a few cuts and slices on " + HIS_HER(TP) + " material.\n",TP);
		time = 2.5;
		break;
		case 3:
		write("\nYou rip a few holes.\n");
		say(QCTNAME(TP)+ " rips some holes in the material.\n",TP);
		time = 3.0;
		break;
		default:
		write("\nYou stop working, your is banner is ready to be bound to a pole.\n\n");
		say("\n"+QCTNAME(TP)+" stops working.\n\n",TP);
		return;
	}
	set_alarm(time, 0.0, &prep_cloak(player, ++stage));
}

void attach_items(object pole, object cloth, object head)
{
	object standard;
	
	setuid();
	seteuid(getuid());
	standard = clone_object(ORCGLD_DIR + "obj/battle_standard");
	
	write("You tie the cloth to your sharpened pole to make a battle standard, then shove a " + head->short() + " onto the top of the pole.\n");
	say(QCTNAME(TP) + " ties a cloth to " + HIS_HER(TP) + " sharpened pole, then shoves a " + head->short() + " onto the top of it.\n");
	
	standard->set_adj(head->query_adj());
	standard->set_short("grisly battle standard with a " + head->short());
	standard->set_pshort("grisly battle standards with " + head->short() + "s");
	standard->set_long("This is a grisly battle standard, made by orcs. It has a " + head->short() + " hanging from the top.\n");
	standard->move(TP);
	head->remove_object();
	pole->remove_object();
	cloth->remove_object();
}

int make_pole()
{
	object pole, cloth, head;
	
	if(!present("_a_sharp_pole", TP))
	{
		write("But you don't even have a pole prepared.\n");
		return 1;
	}
	
	if(!present("_a_cut_cloth", TP))
	{
		write("But you don't even have a cloth prepared.\n");
		return 1;
	}
	
	if(!present("_head_for_standard", TP))
	{
		write("But you don't have a scalp!\n");
		return 1;
	}
	
	pole = present("_a_sharp_pole", TP);
	cloth = present("_a_cut_cloth", TP);
	head = present("_head_for_standard", TP);
	
	attach_items(pole, cloth, head);
	
	return 1;
}


void
move_to(object player, object ob)
{
    if (!ob->move(player)) 
        return;

    
    if (!environment(player) || ob->move(environment(player)))
    {
        ob->remove_object();
        return;
    }

    player->catch_msg("You can't carry " + LANG_ASHORT(ob) + ".\n");
    return;
}

void generate_parts(object body)
{
	object part_one;
	object part_two;
	object part_three;
	object part_four;
	string part1;
	string part2;
	string part3;
	string part4;
	
	part2 = ({"arm", "liver", "hand", "ear"})[random(3)];
	part3 = ({"arm", "heart", "leg", "nose"})[random(3)];
	part4 = ({"leg", "spleen", "foot", "stomach"})[random(3)];
	
	setuid();
	seteuid(getuid());
	part_one = clone_object(ORCGLD_DIR + "obj/severed_head");
	part_one->set_short("bloody " + body->query_race() + " scalp");
	part_one->set_pshort("bloody " + body->query_race() + " scalps");
	part_one->set_adj(body->query_race());
	part_one->add_name("leftover");
	part_one->set_long("This " + body->query_race() + 
            " scalp is the grisly leavings of a corpse.\n");
	
	setuid();
	seteuid(getuid());
	part_two = clone_object(ORCGLD_DIR + "obj/corpse_part");
	part_two->set_name(part2);
	part_two->set_pname(part2 + "s");
	part_two->set_short(body->query_race() + " " + part2);
	part_two->set_pshort(body->query_race() + " " + part2 + "s");
	part_two->set_adj(body->query_race());
	part_two->add_name("leftover");
	part_two->set_long("This " + body->query_race() + " " + part2 + 
            " is the grisly leavings of a corpse.\n");
	
	setuid();
	seteuid(getuid());
	part_three = clone_object(ORCGLD_DIR + "obj/corpse_part");
	part_three->set_name(part3);
	part_three->set_pname(part3 + "s");
	part_three->set_short(body->query_race() + " " + part3);
	part_three->set_pshort(body->query_race() + " " + part3 + "s");
	part_three->set_adj(body->query_race());
	part_three->add_name("leftover");
	part_three->set_long("This " + body->query_race() + " " + part3 + 
            " is the grisly leavings of a corpse.\n");
	
	setuid();
	seteuid(getuid());
	part_four = clone_object(ORCGLD_DIR + "obj/corpse_part");
	part_four->set_name(part4);
	part_four->set_pname(part4 + "s");
	part_four->set_short(body->query_race() + " " + part4);
	part_four->set_pshort(body->query_race() + " " + part4 + "s");
	part_four->set_adj(body->query_race());
	part_four->add_name("leftover");
	part_four->set_long("This " + body->query_race() + " " + part4 + 
            " is the grisly leavings of a corpse.\n");
	
	write("You savagely rip the corpse of the " + body->query_nonmet_name(TP) + 
            " to shreds and take a few of the remaining parts.\n");
	say(QCTNAME(TP) + " savagely rips the corpse of the " + 
            body->query_nonmet_name(all_inventory(environment(TP))) + 
            " to shreds!\n");
	
        map(({ part_one, part_two, part_three, part_four }), &move_to(TP, ));
	body->remove_object();
}

int rip_corpse(string str)
{
	int s;
	mixed *body;
	
	if (!present("corpse",ENV(TP)))
	{
		write("But there are no fallen enemies!\n");
		return 1;
	}	
	
	if(!strlen(str)) /* no string supplied */
	{
		write("Rip apart which corpse?\n");
		return 1;
	}
	
	str = lower_case(str);
    
	if (!parse_command(str, ENV(TP), "[the] %i", body))
	{
		write("Rip apart which corpse?\n");
		return 1;
	}
	
	body = NORMAL_ACCESS(body, 0, 0);
	s = sizeof(body);

	if (s > 1)
	{
		write("You can only rip apart one corpse at a time.\n");
		return 1;
	}
	
	if (!s)
	{
		write("Rip apart which corpse?\n");
		return 1;
	}
	
	generate_parts(body[0]);
	
	return 1;
}

void standard_planting(object standard)
{
	object room = environment(TP);
	standard->set_short(standard->short() + ", stuck in the ground");
	standard->move(room);
}

int plant_standard(string str)
{
	int s;
	object room = environment(TP);
	mixed *standard;
	
	if (!strlen(str))
	{
		write("Plant what in the ground?\n");
		return 1;
	}

   
	str = lower_case(str);
    
	if (!parse_command(str, all_inventory(this_player()), "[the] %i", standard))
	{
		write("Plant what in the ground?\n");
		return 1;
	}

	standard = NORMAL_ACCESS(standard, 0, 0);
	s = sizeof(standard);

	if (s > 1)
	{
		write("Plant one standard in the ground at a time.\n");
		return 1;
	}
	
	if (!s)
	{
		write("Plant what in the ground?\n");
		return 1;
	}
	
	if(!standard[0]->query_prop(IS_STANDARD))
	{
		write("That's not a battle standard!!\n");
		return 1;
	}
	
	if(standard[0]->query_prop(IS_LASHED))
	{
		write("But it is lashed to your back. Remove it first.\n");
		return 1;
	}
	
	if (room->query_prop(ROOM_I_INSIDE))
	{
		write("It would be better to display a battle standard outside.\n");
		return 1;
	}
	
	write("You hold the battle standard tightly, then thrust it into the ground, planting it firmly.\n");
	say(QCTNAME(TP) + " thrusts " + HIS_HER(TP) + " battle standard into the ground, planting it firmly.\n");
	standard->add_prop(OBJ_M_NO_GET, "The battle standard can not be taken, as it is stuck firmly in place. It would take a lot of effort to extract it.\n");
	standard->add_prop(PLANTED, 1);
	
	standard_planting(standard[0]);
	return 1;
}

int paint_standard(string str)
{
	string item;
	string existing;
	string message;
	mixed *standard;
	int s;
	
	if(!strlen(str))
	{
		write("Paint what?\n");
		return 1;
	}
	
	sscanf(str, "%s, %s", item, message);
	
	if (!item ||
	    !parse_command(item, all_inventory(this_player()), "[the] %i", standard))
	{
		write("Paint what?\n");
		return 1;
	}

	standard = NORMAL_ACCESS(standard, 0, 0);
	s = sizeof(standard);

	if(s > 1)
	{
		write("You can only paint one standard at a time.\n");
		return 1;
	}
	
	if (!s)
	{
		write("Paint what?\n");
		return 1;
	}
	
	if(!standard[0]->query_prop(IS_STANDARD))
	{
		write("You can only paint on battle standards!!\n");
		return 1;
	}
	
	
	if(standard[0]->query_prop(IS_PAINTED))
	{
		write("But it already has a message on it!\n");
		return 1;
	}
	
	if(!strlen(message))
	{
		write("You must paint a message.\n");
		return 1;
	}
	
	if(strlen(message) > 50)
	{
		write("Come on! That's just too long to fit on it!\n");
		return 1;
	}
	
	existing = standard[0]->query_long();
	
	write("Using blood from one of your recent kills, you paint a message on your battle standard.\n");
	say("Using blood from one of " + HIS_HER(TP) + " recent kills, " + QCTNAME(TP) +" paints something on " + HIS_HER(TP) + " battle standard.\n");
	
	standard[0]->set_long(existing + "A message is painted in blood on the standard: " + capitalize(message) + "\n");
	standard[0]->add_prop(IS_PAINTED, 1);
	
	return 1;
}
