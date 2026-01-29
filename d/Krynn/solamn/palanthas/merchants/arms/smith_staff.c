/* Mortis 01.2006
 *
 * This is the weapon base for the staves forged at the
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


/* Prototypes */
int set_dtdata();
string long_desc();
string *command_array;
string adjsty1, adjsty2, namedri;
string make_shortwep(string dri, string wfull);
string make_shortsty(string sty1, string sty2);

int i_only_bludge = 1;
string sty1;
string sty2;
string wep;
string wfull;
string shortwep;
string shortsty;

mapping wep_to_realname = (["staff":"staff", "quarterstaff":"quarterstaff"]);

mapping wep_to_pluralname = (["staff":"staves", "quarterstaff":"quarterstaves"]);

mapping wep_to_long = (["staff":"This wooden staff", 
	"quarterstaff":"This wooden quarterstaff"]);

mapping sty_to_long = (["blackthorn":"crafted from spiky blackthorn",
	"blackened":"blackened with forge fire giving it a shadowed appearance",
	"heavy":"reinforced with extra folded steel for bludgeoning",
	"studded":"studded with spikes of steel on each end",
	"light":"amazingly light",
	"long":"fairly long",
	"thick":"fairly thick",
	"polished":"polished to a gleaming shine"]);

void
create_weapon()
{
	add_name("staff");

	set_hit(40);
	set_pen(40); // Small bonus for folded steel technique, sharper edge.
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
	set_likely_dull(12); /* Increased chance to dull.  Folded-steel needs lots
						 * of attention. */
	set_likely_break(9); // Folded-steel has a slightly lower chance to break.

    add_prop(OBJ_I_WEIGHT, 3900);
    add_prop(OBJ_I_VOLUME, 5100);
	set_keep(1);

    seteuid(getuid());
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
	string ldesc = wep_to_long[wep] + " has been banded with high quality steel "
	+ "giving it exceptional strength while remaining durable and well balanced. "
        + "It is ";

	if (sty1 == sty2)
		ldesc += sty_to_long[sty1];
	
	else
		ldesc += sty_to_long[sty1] + " and " + sty_to_long[sty2];
	
	ldesc += ".  The " + wep + "'s shaft bears a circular stamp.\n";

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
	if (parse_command(sty1, ({}), "'studded' / 'blackthorn'") || parse_command(sty2, ({}), "'studded' / 'blackthorn'"))
	{
	    set_dt(W_BLUDGEON | W_IMPALE);
		i_only_bludge = 0;
		return 1;
	}

	else
	    set_dt(W_BLUDGEON);
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
	if (strlen(arg) && !parse_command(arg, ({}), "[the] [circular] 'stamp' / 'shaft' "))
    {
        return 0; // The player used syntax with which we do not agree. 
    }
	
	write("The shaft of this " + wep + " has been stamped with a seal "
	+ "press.  Inside the indented circular seal is the symbol of an "
	+ "anvil underneath \"Palanthas\" in the old style.\n");
	return 1;
}

/* Special hit/miss msgs based on whether dt is W_BLUDGEON or not (W_IMPALE) */
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
		if (i_only_bludge == 0 && random(2) == 1)
		{
			wielder->catch_msg(one_of_list(({"You stab at " + QTNAME(enemy)
			+ " with your " + short() + " missing barely.",
			  "You thrust your " + short() + " in a quick lunge at "
			+ QTNAME(enemy) + " but miss."})) + "\n");
		}
		else
		{
			wielder->catch_msg(one_of_list(({"You swing at " + QTNAME(enemy)
			+ " with your " + short() + " missing barely.",
			  "You swing your " + short() + " in a wide arc at "
			+ QTNAME(enemy) + " but miss."})) + "\n");
		}
	}
	if (!enemy->query_option(OPT_GAG_MISSES))
	{
		if (i_only_bludge == 0 && random(2) == 1)
		{
			enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" stabs at you "
			+ "with " + HIS(wielder) + " " + short() + " missing barely.",
			  " thrusts " + HIS(wielder) + " " + short() + " in a quick lunge "
			+ "at you but misses."})) + "\n");
		}
		else
		{
			enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" swings at "
			+ "you with " + HIS(wielder) + " " + short() + " missing barely.",
			  " swings " + HIS(wielder) + " " + short() + " in a wide arc at "
			+ "you but misses."})) + "\n");
		}
	}
	if (i_only_bludge == 0 && random(2) == 1)
	{
		wielder->tell_watcher_miss(QCTNAME(wielder) + one_of_list(({" stabs "
	    + "at " + QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " missing barely.",
		  " thrusts " + HIS(wielder) + " " + short() + " in a quick lunge at "
		+ QTNAME(enemy) + " but misses."})) + ".\n", enemy);
	}
	else
	{
		wielder->tell_watcher_miss(QCTNAME(wielder) + one_of_list(({" swings "
		+ "at " + QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " missing barely.",
		  " swings " + HIS(wielder) + " " + short() + " in a wide arc at "
		+ QTNAME(enemy) + " but misses."})) + ".\n", enemy);
	}
	break;


    case 0..4:
	if (dt == W_BLUDGEON)
	{
		wielder->catch_msg(one_of_list(({"You contuse " + QTNAME(enemy)
		+ "'s " + hdesc + " with your " + short() + " leaving a bruise.",
		  "You contuse the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + short() + " bruising " + HIM(enemy) + "."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" contuses "
		+ "your " + hdesc + " with " + HIS(wielder) + " " + short()
		+ " leaving a bruise.",
		  " contuses your " + hdesc + " with " + HIS(wielder)
		+ short() + " bruising you."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" contuses "
		+ QTNAME(enemy) + "'s " + hdesc + " with " + HIS(wielder)
		+ " " + short() + " leaving a bruise.",
		  " contuses the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + short() + " bruising " + HIM(enemy) + "."}))
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
	if (dt == W_BLUDGEON)
	{
		wielder->catch_msg(one_of_list(({"You clud " + QTNAME(enemy)
		+ " with your " + short() + " leaving a bloody bruise on " + HIS(enemy)
		+ " " + hdesc + ".",
		  "You clud the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + short() + " bruising " + HIM(enemy) + " painfully."}))
		+ "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" cluds "
		+ "you with " + HIS(wielder) + " " + short() + " leaving a bloody "
		+ "bruise on your " + hdesc + ".",
		  " cluds your " + hdesc + " with " + HIS(wielder) + " " + short()
		+ " bruising it painfully."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" cluds "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " leaving a bloody bruise on " + HIS(enemy) + " " + hdesc + ".",
		  " cluds the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + short() + " bruising " + HIM(enemy)
		+ " painfully."})) + "\n", enemy);
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
		  " sticks your " + hdesc + " with " + HIS(wielder) + " " + short()
		+ " opening a painful wound."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" sticks "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " opening a splitting wound in " + HIS(enemy) + " " + hdesc + ".",
		  " sticks the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + short() + " opening a painful wound."}))
		+ "\n", enemy);
	}
	break;

	case 11..18:
	if (dt == W_BLUDGEON)
	{
		wielder->catch_msg(one_of_list(({"You clobber " + QTNAME(enemy)
		+ " with your " + short() + " impacting the bones of " + HIS(enemy)
		+ " " + hdesc + ".",
		  "You clobber the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + short() + " impacting " + HIS(enemy) + " bones."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" clobbers "
		+ "you with " + HIS(wielder) + " " + short() + " sending sharp stabs "
		+ "of pain through your quickly numbing " + hdesc + ".",
		  " clobbers your " + hdesc + " with " + HIS(wielder) + " " + short()
		+ " sending sharp stabs of pain down its nerves."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" clobbers "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " impacting the bones of " + HIS(enemy) + " " + hdesc + ".",
		  " clobbers the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + short() + " impacting " + HIS(enemy) + " bones."}))
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
		  " pierces your " + hdesc + " with " + HIS(wielder) + " " + short()
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
	if (dt == W_BLUDGEON)
	{
		wielder->catch_msg(one_of_list(({"Slipping a blow from "
		+ QTNAME(enemy) + ", you step in, punishing " + HIM(enemy)
		+ " with your " + short() + " and leaving smashed flesh beneath "
		+ HIS(enemy) + " " + hdesc + ".",
		  "Parrying aside a blow, you punish " + QTNAME(enemy) + "'s "
		+ hdesc + " with your " + short() + " leaving smashed flesh "
		+ "beneath."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" slips a blow "
		+ "from you and steps in, punishing you with " + HIS(wielder)
		+ short() + " leaving smashed flesh beneath your " + hdesc + ".",
		  " parries your blow and punishes your " + hdesc + " with "
		+ HIS(wielder) + " " + short() + " leaving smashed flesh beneath."}))
		+ "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" slips a "
		+ "blow from " + QTNAME(enemy) + " and steps in, punishing "
		+ HIM(enemy) + " with " + HIS(wielder) + " " + short() + " leaving "
		+ "smashed flesh beneath " + HIS(enemy) + " " + hdesc + ".",
		  " parries a blow and punishes " + QTNAME(enemy) + "'s " + hdesc
		+ " with " + HIS(wielder) + " " + short() + " leaving "
		+ "smashed flesh beneath."})) + "\n", enemy);
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
	if (dt == W_BLUDGEON)
	{
		wielder->catch_msg(one_of_list(({"You aim your " + short() + " in a "
		+ "deadly arc at " + QTNAME(enemy) + " thrashing "
		+ HIS(enemy) + " " + hdesc + " with a loud \"Thrack!\"",
		  "You thrash the " + hdesc + " of " + QTNAME(enemy)
		+ " as your " + short() + " lands in a deadly arc with a loud "
		+ "\"Thwack!\""})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" aims "
		+ HIS(wielder) + " " + short() + " at you in a deadly arc thrashing "
		+ "your " + hdesc + " with a loud \"Thrack!\"",
		  " thrashes your " + hdesc + " with " + HIS(wielder)
		+ " " + short() + " as it lands in a deadly arc with a loud "
		+ "\"Thwack!\""})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" aims "
		+ HIS(wielder) + " " + short() + " in a deadly arc at "
		+ QTNAME(enemy) + " thrashing " + HIS(enemy) + " "
		+ hdesc + " with a loud \"Thrack!\".",
		  " thrashes the " + hdesc + " of " + QTNAME(enemy)
		+ " with " + HIS(wielder) + " " + short() + " as it lands in a "
		+ "deadly arc with a loud \"Thwack!\""})) + "\n", enemy);
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
		wielder->catch_msg(one_of_list(({"You wreck " + QTNAME(enemy)
		+ " with your " + short() + " as bits of bone and gore spray forth "
		+ "from " + HIS(enemy) + " " + hdesc + ".",
		  "You wreck " + QTNAME(enemy) + "'s " + hdesc + " with your "
		+ short() + " sending bits of bone and gore spraying forth from the "
		+ "impact."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" wrecks you "
		+ "with " + HIS(wielder) + " " + short() + " as gore sprays forth from "
		+ "your " + hdesc + ".",
		  " wrecks your " + hdesc + " with " + HIS(wielder) + " " + short()
		+ " sending gore spraying forth from the impact."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" wrecks "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + short() + " as gore "
		+ "sprays forth from " + HIS(enemy) + " " + hdesc + ".",
		  " wrecks " + QTNAME(enemy) + "'s " + hdesc + " with " + HIS(wielder)
		+ " " + short() + " sending gore spraying forth from the impact."}))
		+ "\n", enemy);
	}
	else
	{
		wielder->catch_msg(one_of_list(({"You gore the steel of "
		+ "your " + short() + " through " + QTNAME(enemy) + " as ichor "
		+ "spurts forth from " + HIS(enemy) + " " + hdesc + ".",
		  "You gore the steel of your " + short() + " through "
		+ QTNAME(enemy) + "'s " + hdesc + " sending ichor spurting forth "
		+ "from the wound."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" gores the "
		+ "steel of " + HIS(wielder) + " " + short() + " through you as "
		+ "ichor spurts forth from your " + hdesc + ".",
		  " gores the steel of " + HIS(wielder) + " " + short()
		+ " through your " + hdesc+ " sending ichor spurting forth from "
		+ "the wound."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" gores "
		+ "the steel of " + HIS(wielder) + " " + short() + " through "
		+ QTNAME(enemy) + " as ichor spurts forth from " + HIS(enemy) + " "
		+ hdesc + ".",
		  " gores the steelof " + HIS(wielder) + " " + short()
		+ " through " + QTNAME(enemy) + "'s " + hdesc + " sending ichor "
		+ "spurting forth from the wound."})) + "\n", enemy);
	break;

    }
    return 1;
	}
	return 1;
}
