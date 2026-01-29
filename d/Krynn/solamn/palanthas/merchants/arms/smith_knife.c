/* Mortis 01.2006
 *
 * This is the weapon base for the knives forged at the
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
string long_desc();
string *command_array;
string adjsty1, adjsty2, namedri;
string make_shortwep(string dri, string wfull);
string make_shortsty(string sty1, string sty2);

string sty1;
string sty2;
string wep;
string wfull;
string shortwep;
string shortsty;

mapping wep_to_realname = (["dagger":"dagger", "flatknife":"flatknife",
	"knife":"knife", "kukri":"kukri", "machete":"machete", "shank":"shank",
	"shiv":"shiv", "stiletto":"stiletto"]);

mapping wep_to_pluralname = (["dagger":"daggers", "flatknife":"flatknives",
	"knife":"knives", "kukri":"kukris", "machete":"machetes", "shiv":"shivs", 
	"stiletto":"stilettos"]);

mapping wep_to_long = (["dagger":"With a tight, leather bound handle and "
	+ "counter balanced pommel, this classic styled dagger", 
	"flatknife":"Single edged like a knife but with a thinner blade, the "
	+ "flatknife has a slim profile such that its hilt, handle, and pommel "
	+ "are hardly any thicker than its blade allowing it to lay almost "
	+ "perfectly flat against surfaces.  It",
	"knife":"A classically styled knife with a single edge and tight, "
	+ "leather bound handle, its small hilt is more to keep it in place "
	+ "in a sheath than catch blows.  It is utilitous and functional and", 
	"kukri":"The kukri is a large, reverse curved knife used for hacking, "
	+ "slicing, and in skilled hands throwing.  Its forward curving blade",
	"machete":"The machete is almost large enough to be a short sword and "
	+ "is commonly used for hacking through thick underbrush, although it "
	+ "is fairly intimidating as well.  It", 
	"shiv":"Simple but effective, this shiv has no hilt, just tight leather "
	+ "bound about its tang.  The blade is sharpened to a point and", 
	"stiletto":"The stiletto is a thin length of razor coming to a needle "
	+ "point at its end.  It has no hilt and a thin, arrasene wrapped "
	+ "tang for a handle best held in the fingers or thrown.  It"]);

mapping sty_to_long = (["blackened":"blackened with coal soot from the forge "
	+ "to eliminate flashy reflections of light giving it a shadowed "
	+ "appearance",
	"curved":"curved for ease in slicing",
	"folded-steel":"remarkable due to the folded steel in its blade",
	"heavy":"reinforced with extra folded steel for hacking",
	"light":"amazingly light",
	"long":"particularly long for its type",
	"polished":"polished to a gleaming shine and very reflective",
	"serrated":"serrated along its edge for cutting through flesh",
	"shining":"shining with reflected light as if it just came from the "
	+ "master smith moments ago",
	"short":"of a rather short and discreet length",
	"thin":"especially thin for easy concealment",
	"throwing":"balanced specifically for throwing",
	"wide":"wide in the blade for that impressive large weapon look"]);

void
create_weapon()
{
	
	set_adj("folded-steel");
	add_name("knife");

	set_hit(20);
	set_pen(20); // Small bonus for folded steel technique, sharper edge.
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);
	set_likely_dull(12); /* Increased chance to dull.  Folded-steel needs lots
						 * of attention. */
	set_likely_break(9); // Folded-steel has a slightly lower chance to break.

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 300);
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

	command_array = TO->query_names();
}

string long_desc()
{
	string ldesc = wep_to_long[wep] + " has been forged of folded steel "
	+ "giving it exceptional strength and an edge that can be sharpened to "
	+ "a razor point all while remaining light and well balanced.  Its blade "
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
        return 0; // The player used syntax with which we do not agree. 
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
		if (random(2) == 0)
		{
			wielder->catch_msg(one_of_list(({"You slash at " + QTNAME(enemy)
			+ " with your " + short() + " missing barely.",
			  "You slice your " + short() + " in a wide arc at "
			+ QTNAME(enemy) + " but miss."})) + "\n");
		}
		else
		{
			wielder->catch_msg(one_of_list(({"You stab at " + QTNAME(enemy)
			+ " with your " + short() + " missing barely.",
			  "You thrust your " + short() + " in a quick lunge at "
			+ QTNAME(enemy) + " but miss."})) + "\n");
		}
	}
	if (!enemy->query_option(OPT_GAG_MISSES))
	{
		if (random(2) == 1)
		{
			enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" slashes at "
			+ "you with " + HIS(wielder) + " " + short() + " missing barely.",
			  " slices " + HIS(wielder) + " " + short() + " in a wide arc at "
			+ "you but misses."})) + "\n");
		}
		else
		{
			enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" stabs at you "
			+ "with " + HIS(wielder) + " " + short() + " missing barely.",
			  " thrusts " + HIS(wielder) + " " + short() + " in a quick lunge "
			+ "at you but misses."})) + "\n");
		}
	}
	if (random(2) == 1)
	{
		wielder->tell_watcher_miss(QCTNAME(wielder) + one_of_list(({" slashes "
		+ "at " + QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " missing barely.",
		  " slices " + HIS(wielder) + " " + short() + " in a wide arc at "
		+ QTNAME(enemy) + " but misses."})) + ".\n", enemy);
	}
	else
	{
		wielder->tell_watcher_miss(QCTNAME(wielder) + one_of_list(({" stabs "
	    + "at " + QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " missing barely.",
		  " thrusts " + HIS(wielder) + " " + short() + " in a quick lunge at "
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
		  " lightly slashes your " + hdesc + " with " + HIS(wielder) + " "
		+ short() + " drawing a dark line of blood."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" lightly "
		+ "slashes " + QTNAME(enemy) + "'s " + hdesc + " with " + HIS(wielder)
		+ " " + short() + " drawing a thin line of blood.",
		  " lightly slashes the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " "  + short() + " drawing a dark line of blood."}))
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
		  " jabs your " + hdesc + " with " + HIS(wielder) + " "
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
		  " slashes your " + hdesc + " with " + HIS(wielder) + " " + short()
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
		+ HIS(wielder) + " " + short() + " opening a nasty wound."}))
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
		+ HIS(wielder) + " " + short() + " inflicting a deep, painful "
		+ "wound."})) + "\n", enemy);
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
		+ "folded-steel of " + HIS(wielder) + " " + short() + " through you "
		+ "as gore sprays forth from your " + hdesc + ".",
		  " trenches the folded-steel of " + HIS(wielder) + " " + short()
		+ " through your " + hdesc+ " sending gore spraying forth from "
		+ "the wound."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" trenches "
		+ "the folded-steel of " + HIS(wielder) + " " + short() + " through "
		+ QTNAME(enemy) + " as gore sprays forth from " + HIS(enemy) + " "
		+ hdesc + ".",
		  " trenches the folded-steel of " + HIS(wielder) + " " + short()
		+ " through " + QTNAME(enemy) + "'s " + hdesc+ " sending gore "
		+ "spraying forth from the wound."})) + "\n", enemy);
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
		+ "folded-steel of " + HIS(wielder) + " " + short() + " through you "
		+ "as ichor spurts forth from your " + hdesc + ".",
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
