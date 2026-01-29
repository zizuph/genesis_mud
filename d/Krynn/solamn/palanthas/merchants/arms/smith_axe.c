/* Mortis 01.2006
 *
 * This is the weapon base for the axes forged at the
 * smithy in the Arms district of Palanthas.
 *
 */
inherit "/d/Krynn/solamn/palanthas/obj/crafted_weapon";
inherit "/lib/commands";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include "../../local.h"
//#include "smith_emotes.h"

/* Prototypes */
int set_dtdata();
string long_desc();
string *command_array;
string adjsty1, adjsty2, namedri;
string make_shortwep(string dri, string wfull);
string make_shortsty(string sty1, string sty2);

int i_impale = 0;
string sty1;
string sty2;
string wep;
string wfull;
string shortwep;
string shortsty;

mapping wep_to_realname = (["axe":"axe", "battleaxe":"battleaxe",
	"cleaver":"cleaver", "handaxe":"handaxe"]);

mapping wep_to_pluralname = (["axe":"axes", "battleaxe":"battleaxes",
	"cleaver":"cleavers", "handaxe":"handaxes"]);

mapping wep_to_long = (["axe":"A curved half-circle blade is sealed and "
	+ "bound to a haft of smooth oak ending in a steel pommel.  The axe", 
	"battleaxe":"This battleaxe has a smooth, solid steel haft and pommel "
	+ "topped with a razor-edged, arcing crescent head that",
	"cleaver":"Shorter than a normal axe, this cleaver's handle is two "
	+ "lengths of smooth oak riveted to the cleaver's tang.  The blade "
	+ "itself is a slightly curved, thick backed, hacking edge traditionally "
	+ "used by butchers to hack through meet and bone.  It",
	"handaxe":"With its modern forging techniques, this axe is smaller and "
	+ "lighter than its predecessors and can be easily slipped within a "
	+ "belt.  Its smooth, oak handle curves back to its angled, chopping "
	+ "head giving it a deadly slashing arc with minimal size.  The head"]);

mapping sty_to_long = (["blackened":"blackened with coal soot from the forge "
	+ "to eliminate flashy reflections of light giving it a shadowed "
	+ "appearance",
	"double-bladed":"double bladed with two opposing axe heads",
	"folded-steel":"remarkable due to the folded steel in its blade",
	"grensh":"sharpened down into a wavy almost serrated edge for shredding "
	+ "flesh",
	"heavy":"reinforced with extra folded steel for hacking",
	"hooked":"hooked at its end for tripping and snagging",
	"large":"fairly large",
	"light":"amazingly light",
	"long":"particularly long for its type",
	"polished":"polished to a gleaming shine and very reflective",
	"shining":"shining with reflected light as if it just came from the "
	+ "master smith moments ago",
	"short":"of a rather short and discreet length",
	"spiked":"has a piercing spike at its tip for stabbing"]);

void
create_weapon()
{
    seteuid(getuid());
	
	set_adj("folded-steel");
	add_name("axe");

	set_hit(35);
	set_pen(35); // Small bonus for folded steel technique, sharper edge.
    set_wt(W_AXE);
    set_hands(W_ANYH);
	set_likely_dull(12); /* Increased chance to dull.  Folded-steel needs lots
						 * of attention. */
	set_likely_break(9); // Folded-steel has a slightly lower chance to break.

    add_prop(OBJ_I_WEIGHT, 3150);
    add_prop(OBJ_I_VOLUME, 3300);
	set_keep(1);
}

void
set_weapon_data(string data)
{
	string* txt = explode(data,"&&");
	sty1 = txt[0];
	sty2 = txt[1];
	wep = txt[2];
	wfull = wep_to_realname[wep];
	shortwep = make_shortwep(wep, wfull);
	shortsty = make_shortsty(sty1, sty2);

	recover_string = data;

    set_name(wep);
	set_pname(wep_to_pluralname[wep]);
	add_name(wfull);
	add_adj(sty1);
    add_adj(sty2);
	set_short(shortsty + " " + shortwep);
    set_long("@@long_desc");

	set_dtdata();

	command_array = TO->query_names();
}

string long_desc()
{
	string ldesc = wep_to_long[wep] + " has been forged of folded steel "
	+ "giving it exceptional strength and an edge that can be sharpened to "
	+ "a razor point all while remaining strong and well balanced.  Its blade "
	+ "is ";

	if (sty1 == sty2)
		ldesc += sty_to_long[sty1];
	
	else
		ldesc += sty_to_long[sty1] + " and " + sty_to_long[sty2];
	
	ldesc += ".  The " + wep + "'s pommel bears a circular stamp.\n";

	return ldesc;
}

string make_shortwep(string wep, string wfull)
{
	if (wep == wfull)
	{
		return wep;
	}
	return wep + " " + wfull;
}

string make_shortsty(string sty1, string sty2)
{
	if (sty1 == sty2)
	{
		return sty1;
	}
	return sty1 + " " + sty2;
}

int
set_dtdata()
{
	if (sty1 == "spiked" || sty2 == "spiked" || sty1 == "hooked" || sty2 == "hooked")
	{
	    set_dt(W_SLASH | W_IMPALE);
		i_impale = 1;
		return 1;
	}
	
	else
	    set_dt(W_SLASH);
	return 1;
}

void
init()
{
    ::init();
	ADD("exa_pommel", "exa");
	ADD("exa_pommel", "examine");
}

int exa_pommel(string arg)
{
	if (strlen(arg) && !parse_command(arg, ({}), "[the] [circular] 'stamp' / 'pommel' "))
    {
        return 0; // the player used syntax we don't agree with 
    }
	
	write("The pommel of this " + wep + " has been stamped with a seal "
	+ "press.  Inside the indented circular seal is the symbol of an "
	+ "anvil underneath \"Palanthas\" in the old style.\n");
	return 1;
}

/* Special hit/miss msgs based on whether dt is W_SLASH or not (W_IMPALE) */
public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

	if (!objectp(wielder) || !objectp(enemy))
		return 0;

    switch(phurt)
    {
    case -1:
	case -2:
	if (!wielder->query_option(OPT_GAG_MISSES))
	{
		if (i_impale == 1 && random(2) == 1)
		{
			wielder->catch_msg(one_of_list(({"You stab at " + QTNAME(enemy)
			+ " with your " + short() + " missing barely.",
			  "You thrust your " + short() + " in a quick lunge at "
			+ QTNAME(enemy) + " but miss."})) + "\n");
		}
		else
		{
			wielder->catch_msg(one_of_list(({"You slash at " + QTNAME(enemy)
			+ " with your " + short() + " missing barely.",
			  "You swipe your " + short() + " in a wide arc at "
			+ QTNAME(enemy) + " but miss."})) + "\n");
		}
	}
	if (!enemy->query_option(OPT_GAG_MISSES))
	{
		if (i_impale == 1 && random(2) == 1)
		{
			enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" stabs at you "
			+ "with " + HIS(wielder) + " " + short() + " missing barely.",
			  " thrusts " + HIS(wielder) + " " + short() + " in a quick lunge "
			+ "at you but misses."})) + "\n");
		}
		else
		{
			enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" slashes at "
			+ "you with " + HIS(wielder) + " " + short() + " missing barely.",
			  " swipes " + HIS(wielder) + " " + short() + " in a wide arc at "
			+ "you but misses."})) + "\n");
		}
	}
	if (i_impale == 1 && random(2) == 1)
	{
		wielder->tell_watcher_miss(QCTNAME(wielder) + one_of_list(({" stabs "
	    + "at " + QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " missing barely.",
		  " thrusts " + HIS(wielder) + " " + short() + " in a quick lunge at "
		+ QTNAME(enemy) + " but misses."})) + ".\n", enemy);
	}
	else
	{
		wielder->tell_watcher_miss(QCTNAME(wielder) + one_of_list(({" slashes "
		+ "at " + QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " missing barely.",
		  " swipes " + HIS(wielder) + " " + short() + " in a wide arc at "
		+ QTNAME(enemy) + " but misses."})) + ".\n", enemy);
	}
	break;


    case 0..4:
	if (dt == W_SLASH)
	{
		wielder->catch_msg(one_of_list(({"You lightly slash " + QTNAME(enemy)
		+ "'s " + hdesc + " with your " + short() + " drawing a thin line of "
		+ "blood.",
		  "You lightly slash the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + short() + " drawing a dark line of blood."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" lightly slashes "
		+ "your " + hdesc + " with " + HIS(wielder) + " " + short()
		+ " drawing a thin line of blood.",
		  " lightly slashes your " + hdesc + " with " + HIS(wielder)
		+ short() + " drawing a dark line of blood."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" lightly "
		+ "slashes " + QTNAME(enemy) + "'s " + hdesc + " with " + HIS(wielder)
		+ " " + short() + " drawing a thin line of blood.",
		  " lightly slashes the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + short() + " drawing a dark line of blood."}))
		+ "\n", enemy);
	}
	else
	{
		wielder->catch_msg(one_of_list(({"You jab " + QTNAME(enemy)
		+ "'s " + hdesc + " with your " + short() + " drawing a thin trickle "
		+ "of blood.",
		  "You jab the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + short() + " drawing a dark trickle of blood."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" jabs your "
		+ hdesc + " with " + HIS(wielder) + " " + short()
		+ " drawing a thin trickle of blood.",
		  " jabs your " + hdesc + " with " + HIS(wielder)
		+ short() + " drawing a dark trickle of blood."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" jabs "
		+ QTNAME(enemy) + "'s " + hdesc + " with " + HIS(wielder)
		+ " " + short() + " drawing a thin trickle of blood.",
		  " jabs the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + short() + " drawing a dark trickle of blood."}))
		+ "\n", enemy);
	}
	break;

    case 5..10:
	if (dt == W_SLASH)
	{
		wielder->catch_msg(one_of_list(({"You slash " + QTNAME(enemy)
		+ " with your " + short() + " opening a thin wound in " + HIS(enemy)
		+ " " + hdesc + ".",
		  "You slash the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + short() + " opening a dark wound."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" slashes "
		+ "you with " + HIS(wielder) + " " + short() + " opening a thin "
		+ "wound in your " + hdesc + ".",
		  " slashes your " + hdesc + " with " + HIS(wielder) + short()
		+ " opening a dark wound."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" slashes "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " opening a thin wound in " + HIS(enemy) + " " + hdesc + ".",
		  " slashes the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + short() + " opening a dark wound."}))
		+ "\n", enemy);
	}
	else
	{
		wielder->catch_msg(one_of_list(({"You stick " + QTNAME(enemy)
		+ " with your " + short() + " opening a splitting wound in "
		+ HIS(enemy) + " " + hdesc + ".",
		  "You stick the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + short() + " opening a painful wound."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" sticks "
		+ "you with " + HIS(wielder) + " " + short() + " opening a splitting "
		+ "wound in your " + hdesc + ".",
		  " sticks your " + hdesc + " with " + HIS(wielder) + short()
		+ " opening a painful wound."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" sticks "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " opening a splitting wound in " + HIS(enemy) + " " + hdesc + ".",
		  " sticks the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder)+ " " + short() + " opening a painful wound."}))
		+ "\n", enemy);
	}
	break;

	case 11..18:
	if (dt == W_SLASH)
	{
		wielder->catch_msg(one_of_list(({"You slice " + QTNAME(enemy)
		+ " with your " + short() + " opening a long wound in " + HIS(enemy)
		+ " " + hdesc + ".",
		  "You slice the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + short() + " opening a nasty wound."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" slices "
		+ "you with " + HIS(wielder) + " " + short() + " opening a long "
		+ "wound in your " + hdesc + ".",
		  " slices your " + hdesc + " with " + HIS(wielder) + " " + short()
		+ " opening a nasty wound."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" slices "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " opening a long wound in " + HIS(enemy) + " " + hdesc + ".",
		  " slices the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder)+ " " + short() + " opening a nasty wound."}))
		+ "\n", enemy);
	}
	else
	{
		wielder->catch_msg(one_of_list(({"You pierce " + QTNAME(enemy)
		+ " with your " + short() + " viciously wounding "
		+ HIS(enemy) + " " + hdesc + ".",
		  "You pierce the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + short() + " inflicting a deep, painful wound."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" pierces "
		+ "you with " + HIS(wielder) + " " + short() + " viciously wounding "
		+ "your " + hdesc + ".",
		  " pierces your " + hdesc + " with " + HIS(wielder) + short()
		+ " inflicting a deep, painful wound."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" pierces "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " viciously wounding " + HIS(enemy) + " " + hdesc + ".",
		  " pierces the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + short() + " inflicting a deep, painful wound."}))
		+ "\n", enemy);
	}
	break;

	case 19..30:
	if (dt == W_SLASH)
	{
		wielder->catch_msg(one_of_list(({"Slipping a blow from "
		+ QTNAME(enemy) + ", you step in, deeply slicing " + HIM(enemy)
		+ " with your " + short() + " and leaving a deep, bleeding slash "
		+ "across " + HIS(enemy) + " " + hdesc + ".",
		  "Parrying aside a blow, you slice deeply into the " + hdesc
		+ " of " + QTNAME(enemy) + " with your " + short() + " leaving a "
		+ "deep, gory slash."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" slips a blow "
		+ "from you and steps in, deeply slicing you with " + HIS(wielder)
		+ short() + " leaving a deep, bleeding slash across your " + hdesc
		+ ".",
		  " parries your blow and slices deeply into your " + hdesc + " with "
		+ HIS(wielder) + " " + short() + " leaving a deep, gory slash."}))
		+ "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" slips a "
		+ "blow from " + QTNAME(enemy) + " and steps in, deeply slicing "
		+ HIM(enemy) + " with " + HIS(wielder) + " " + short() + " leaving "
		+ "a deep, bleeding slash across " + HIS(enemy) + " " + hdesc + ".",
		  " parries a blow and slices deeply into the " + hdesc + " of "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + short() + " leaving "
		+ "a deep, gory slash."})) + "\n", enemy);
	}
	else
	{
		wielder->catch_msg(one_of_list(({"Slipping a blow from "
		+ QTNAME(enemy) + ", you close the distance between you, deeply "
		+ "piercing " + HIM(enemy) + " with your " + short() + " and "
		+ "leaving a bleeding, hollow wound in " + HIS(enemy) + " "
		+ hdesc + ".",
		  "Parrying aside a blow, you deeply pierce the " + hdesc
		+ " of " + QTNAME(enemy) + " with your " + short() + " leaving a "
		+ "gory, hollow wound."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" slips a blow "
		+ "from you and steps in, deeply piercing you with " + HIS(wielder)
		+ short() + " leaving a bleeding, hollow wound across your " + hdesc
		+ ".",
		  " parries your blow and deeply pierces your " + hdesc + " with "
		+ HIS(wielder) + " " + short() + " leaving a gory, hollow wound."}))
		+ "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" slips a "
		+ "blow from " + QTNAME(enemy) + " and steps in, deeply slicing "
		+ HIM(enemy) + " with " + HIS(wielder) + " " + short() + " leaving "
		+ "a bleeding, hollow wound across " + HIS(enemy) + " " + hdesc + ".",
		  " parries a blow and pierces deeply into the " + hdesc + " of "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + short() + " leaving "
		+ "a gory, hollow wound."})) + "\n", enemy);
	}
	break;

	case 31..90:
	if (dt == W_SLASH)
	{
		wielder->catch_msg(one_of_list(({"You aim your " + short() + " in a "
		+ "deadly arc at " + QTNAME(enemy) + " delivering a gaping gash in "
		+ HIS(enemy) + " " + hdesc + ".",
		  "You open a gaping gash in the " + hdesc + " of " + QTNAME(enemy)
		+ " as your " + short() + " lands in a deadly arc."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" aims "
		+ HIS(wielder) + " " + short() + " at you in a deadly arc delivering "
		+ "a gaping gash in your " + hdesc + ".",
		  " opens a gaping gash in your " + hdesc + " with " + HIS(wielder)
		+ " " + short() + " as it lands in a deadly arc."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" aims "
		+ HIS(wielder) + " " + short() + " in a deadly arc at "
		+ QTNAME(enemy) + " delivering a gaping gash in " + HIS(enemy) + " "
		+ hdesc + ".",
		  " opens a gaping gash in the " + hdesc + " of " + QTNAME(enemy)
		+ " with " + HIS(wielder) + " " + short() + " as it lands in a "
		+ "deadly arc."})) + "\n", enemy);
	}
	else
	{
		wielder->catch_msg(one_of_list(({"You plunge your " + short() + " into "
		+ QTNAME(enemy) + " as you lunge forward opening a gaping wound in "
		+ HIS(enemy) + " " + hdesc + ".",
		  "You open a gaping wound in the " + hdesc + " of " + QTNAME(enemy)
		+ " as you lunge forward plunging your " + short() + " into "
		+ HIM(enemy) + "."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" plunges "
		+ HIS(wielder) + " " + short() + " into you as " + HE(wielder)
		+ "lunges opening a gaping wound in your " + hdesc + ".",
		  " opens a gaping wound in your " + hdesc + " as " + HE(wielder)
		+ " lunges forward plunging " + HIS(wielder) + " " + short()
		+ " into you."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" plunges "
		+ HIS(wielder) + " " + short() + " into " + QTNAME(enemy) + " as "
		+ HE(wielder) + " lunges opening a gaping wound in " + HIS(enemy)
		+ " " + hdesc + ".",
		  " opens a gaping wound in " + QTNAME(enemy) + "'s " + hdesc
		+ " as " + HE(wielder) + " lunges forward plunging " + HIS(wielder)
		+ " " + short() + " into " + HIM(enemy) + "."})) + "\n", enemy);
	}
	break;

    default:
	if (dt == W_SLASH)
	{
		wielder->catch_msg(one_of_list(({"You trench the folded-steel of "
		+ "your " + short() + " through " + QTNAME(enemy) + " as gore "
		+ "sprays forth from " + HIS(enemy) + " " + hdesc + ".",
		  "You trench the folded-steel of your " + short() + " through "
		+ QTNAME(enemy) + "'s " + hdesc + " sending gore spraying forth from "
		+ "the wound."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" trenches the "
		+ "folded-steel of " + HIS(wielder) + " " + short() + " through you as "
		+ "gore sprays forth from your " + hdesc + ".",
		  " trenches the folded-steel of " + HIS(wielder) + " " + short()
		+ " through your " + hdesc+ " sending gore spraying forth from "
		+ "the wound."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" trenches "
		+ "the folded-steel of " + HIS(wielder) + " " + short() + " through "
		+ QTNAME(enemy) + " as gore sprays forth from " + HIS(enemy) + " "
		+ hdesc + ".",
		  " trenches the folded-steel of " + HIS(wielder) + " " + short()
		+ " through " + QTNAME(enemy) + "'s " + hdesc+ " sending gore spraying "
		+ "forth from the wound."})) + "\n", enemy);
	}
	else
	{
		wielder->catch_msg(one_of_list(({"You gore the folded-steel of "
		+ "your " + short() + " through " + QTNAME(enemy) + " as ichor "
		+ "spurts forth from " + HIS(enemy) + " " + hdesc + ".",
		  "You gore the folded-steel of your " + short() + " through "
		+ QTNAME(enemy) + "'s " + hdesc + " sending ichor spurting forth "
		+ "from the wound."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" gores the "
		+ "folded-steel of " + HIS(wielder) + " " + short() + " through you as "
		+ "ichor spurts forth from your " + hdesc + ".",
		  " gores the folded-steel of " + HIS(wielder) + " " + short()
		+ " through your " + hdesc+ " sending ichor spurting forth from "
		+ "the wound."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" gores "
		+ "the folded-steel of " + HIS(wielder) + " " + short() + " through "
		+ QTNAME(enemy) + " as ichor spurts forth from " + HIS(enemy) + " "
		+ hdesc + ".",
		  " gores the folded-steel of " + HIS(wielder) + " " + short()
		+ " through " + QTNAME(enemy) + "'s " + hdesc + " sending ichor "
		+ "spurting forth from the wound."})) + "\n", enemy);
	break;

    }
    return 1;
	}
	return 1;
}
