/*
 * Non-magic war-chain used by Kirk the leader of the
 * Brix gang of Jems Court in the aesthetics quarter
 * of Palanthas.  Opposed acrobat/unarmed chance to
 * trip on a successful entanglement hit to the legs.
 *
 * Mortis 06.2006
 *
 * EDITED:  If an enemy died while entangled by the chains
 * the chain would be stuck in a state of assuming it was
 * "in use".  Added reset to this before its alarms could
 * fail from not having an enemy.
 *
 * Mortis 12.2007
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <macros.h>
#include <options.h>
#include <wa_types.h>
#include <ss_types.h>
#include "../../local.h"

// Prototypes
void get_back_up(object enem);
string query_inuse();

string inuse = "not in use";

create_weapon()
{
	set_name("war-chain");
	add_name(({"chain"}));
	set_adj(({"iron", "war"}));
	set_short("iron war-chain");
	set_long("With perfectly round, heavy iron rings, both ends of the "
	+ "war-chain end in iron bars one of which has been tightly wrapped "
	+ "with an interwoven strip of leather and hemp to serve as a handle.  "
	+ "Well-balanced, skillfully forged, and sturdily crafted, a war-chain "
	+ "of this calibre would have no problem wrapping around shields to "
	+ "deliver crushing blows or entangling legs to jerk opponents off "
	+ "their feet.\n");

	set_hit(35);
	set_pen(35);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_ANYH);

	set_likely_dull(9);   // Dulling less relevant to this weapon type.
	set_likely_break(12); // Entangle maneuvers increase breaking risk.
	
	set_keep(1);
	
    add_prop(OBJ_I_VALUE,  900 + random(500));
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

	if (!objectp(wielder) || !objectp(enemy))
		return 0;

	string myshort = short();

    switch(phurt)
    {
		case -2..0:
		if (!wielder->query_option(OPT_GAG_MISSES))
		{
			wielder->catch_msg(one_of_list(({"You swing at " + QTNAME(enemy)
			+ " with your " + myshort + " missing barely.",
			  "You swing your " + myshort + " in a wide arc at "
			+ QTNAME(enemy) + " but miss."})) + "\n");
		}
		if (!enemy->query_option(OPT_GAG_MISSES))
		{
			enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" swings at "
			+ "you with " + HIS(wielder) + " " + myshort + " missing barely.",
			  " swings " + HIS(wielder) + " " + myshort + " in a wide arc at "
			+ "you but misses."})) + "\n");
		}
		wielder->tell_watcher_miss(QCTNAME(wielder) + one_of_list(({" swings "
		+ "at " + QTNAME(enemy) + " with " + HIS(wielder) + " " + myshort
		+ " missing barely.",
		  " swings " + HIS(wielder) + " " + myshort + " in a wide arc at "
		+ QTNAME(enemy) + " but misses."})) + ".\n", enemy);
		break;


    case 1..4:
		wielder->catch_msg(one_of_list(({"You contuse " + QTNAME(enemy)
		+ "'s " + hdesc + " with your " + myshort + " leaving a bruise.",
		  "You contuse the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + myshort + " bruising " + HIM(enemy) + "."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" contuses "
		+ "your " + hdesc + " with " + HIS(wielder) + " " + myshort
		+ " leaving a bruise.",
		  " contuses your " + hdesc + " with " + HIS(wielder) + " "
		+ myshort + " bruising you."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" contuses "
		+ QTNAME(enemy) + "'s " + hdesc + " with " + HIS(wielder)
		+ " " + myshort + " leaving a bruise.",
		  " contuses the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + myshort + " bruising " + HIM(enemy) + "."}))
		+ "\n", enemy);
		break;

    case 5..10:
		wielder->catch_msg(one_of_list(({"You clud " + QTNAME(enemy)
		+ " with your " + myshort + " leaving a bloody bruise on "
		+ HIS(enemy) + " " + hdesc + ".",
		  "You clud the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + myshort + " bruising " + HIM(enemy) + " painfully."}))
		+ "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" cluds "
		+ "you with " + HIS(wielder) + " " + myshort + " leaving a bloody "
		+ "bruise on your " + hdesc + ".",
		  " cluds your " + hdesc + " with " + HIS(wielder) + " " + myshort
		+ " bruising it painfully."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" cluds "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + myshort
		+ " leaving a bloody bruise on " + HIS(enemy) + " " + hdesc + ".",
		  " cluds the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + myshort + " bruising " + HIM(enemy)
		+ " painfully."})) + "\n", enemy);
		break;

	case 11..18:
		wielder->catch_msg(one_of_list(({"You clobber " + QTNAME(enemy)
		+ " with your " + myshort + " impacting the bones of " + HIS(enemy)
		+ " " + hdesc + ".",
		  "You clobber the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ "your " + myshort + " impacting " + HIS(enemy) + " bones."}))
		+ "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" clobbers "
		+ "you with " + HIS(wielder) + " " + myshort + " sending sharp stabs "
		+ "of pain through your quickly numbing " + hdesc + ".",
		  " clobbers your " + hdesc + " with " + HIS(wielder) + " " + myshort
		+ " sending sharp stabs of pain down its nerves."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" clobbers "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + myshort
		+ " impacting the bones of " + HIS(enemy) + " " + hdesc + ".",
		  " clobbers the " + hdesc + " of " + QTNAME(enemy) + " with "
		+ HIS(wielder) + " " + myshort + " impacting " + HIS(enemy)
		+ " bones."})) + "\n", enemy);
		break;

	case 19..30:
		wielder->catch_msg(one_of_list(({"Slipping a blow from "
		+ QTNAME(enemy) + ", you step in, punishing " + HIM(enemy)
		+ " with your " + myshort + " and leaving smashed flesh beneath "
		+ HIS(enemy) + " " + hdesc + ".",
		  "Parrying aside a blow, you punish " + QTNAME(enemy) + "'s "
		+ hdesc + " with your " + myshort + " leaving smashed flesh "
		+ "beneath."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" slips a blow "
		+ "from you and steps in, punishing you with " + HIS(wielder)
		+ myshort + " leaving smashed flesh beneath your " + hdesc + ".",
		  " parries your blow and punishes your " + hdesc + " with "
		+ HIS(wielder) + " " + myshort + " leaving smashed flesh beneath."}))
		+ "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" slips a "
		+ "blow from " + QTNAME(enemy) + " and steps in, punishing "
		+ HIM(enemy) + " with " + HIS(wielder) + " " + myshort + " leaving "
		+ "smashed flesh beneath " + HIS(enemy) + " " + hdesc + ".",
		  " parries a blow and punishes " + QTNAME(enemy) + "'s " + hdesc
		+ " with " + HIS(wielder) + " " + myshort + " leaving "
		+ "smashed flesh beneath."})) + "\n", enemy);
		break;

	case 31..90:
		wielder->catch_msg(one_of_list(({"You aim your " + myshort + " in a "
		+ "deadly arc at " + QTNAME(enemy) + " thrashing "
		+ HIS(enemy) + " " + hdesc + " with a loud \"Thrack!\"",
		  "You thrash the " + hdesc + " of " + QTNAME(enemy)
		+ " as your " + myshort + " lands in a deadly arc with a loud "
		+ "\"Thwack!\""})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" aims "
		+ HIS(wielder) + " " + myshort + " at you in a deadly arc thrashing "
		+ "your " + hdesc + " with a loud \"Thrack!\"",
		  " thrashes your " + hdesc + " with " + HIS(wielder)
		+ " " + myshort + " as it lands in a deadly arc with a loud "
		+ "\"Thwack!\""})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" aims "
		+ HIS(wielder) + " " + myshort + " in a deadly arc at "
		+ QTNAME(enemy) + " thrashing " + HIS(enemy) + " "
		+ hdesc + " with a loud \"Thrack!\".",
		  " thrashes the " + hdesc + " of " + QTNAME(enemy)
		+ " with " + HIS(wielder) + " " + myshort + " as it lands in a "
		+ "deadly arc with a loud \"Thwack!\""})) + "\n", enemy);
		break;

    default:
		wielder->catch_msg(one_of_list(({"You wreck " + QTNAME(enemy)
		+ " with your " + myshort + " as bits of bone and gore spray forth "
		+ "from " + HIS(enemy) + " " + hdesc + ".",
		  "You wreck " + QTNAME(enemy) + "'s " + hdesc + " with your "
		+ myshort + " sending bits of bone and gore spraying forth from the "
		+ "impact."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" wrecks you "
		+ "with " + HIS(wielder) + " " + myshort + " as gore sprays forth "
		+ "from your " + hdesc + ".",
		  " wrecks your " + hdesc + " with " + HIS(wielder) + " " + myshort
		+ " sending gore spraying forth from the impact."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" wrecks "
		+ QTNAME(enemy) + " with " + HIS(wielder) + " " + myshort + " as gore "
		+ "sprays forth from " + HIS(enemy) + " " + hdesc + ".",
		  " wrecks " + QTNAME(enemy) + "'s " + hdesc + " with " + HIS(wielder)
		+ " " + myshort + " sending gore spraying forth from the impact."}))
		+ "\n", enemy);
		break;
	}

	if (hdesc == "legs")
	{
		int cskill = wielder->query_skill(SS_WEP_CLUB) / 3,
			strength = wielder->query_stat(SS_STR) / 10,
			askill = enemy->query_skill(SS_ACROBAT),
			dex = enemy->query_stat(SS_DEX) / 10,
			uaskill = enemy->query_skill(SS_UNARM_COMBAT),
			triptime = 3 + random(4);

		// If whip is already in use, we don't jerk them off feet again.
		if (inuse == "in use")
		{
			string howflail = one_of_list(({"helplessly", "impotently",
				"haphazardly", "and flail wildly", "frantically"}));

			enemy->catch_msg(QCTNAME(wielder) + " jerks " + HIS(wielder)
			+ " war-chain wrapped around your legs causing you to wriggle "
			+ howflail + " about.\n");
			wielder->catch_msg("You jerk your war-chain wrapped around "
			+ QTNAME(enemy) + "'s legs causing " + HIM(enemy) + " to wriggle "
			+ howflail + " about.\n");
			wielder->tell_watcher(QCTNAME(wielder) + " jerks "
			+ HIS(wielder) + " war-chain wrapped around " + QTNAME(enemy)
			+ "'s legs causing " + HIM(enemy) + " to wriggle " + howflail
			+ " about.\n", enemy);

			return 1;
		}

		// Victim's dex/acrobatics vs. Wielder's str/club skill.
		if (dex + askill + random(30) >= cskill + strength + random(30))
		{
			string everb = one_of_list(({" flips", " spins"})),
				   everb2 = " spin",
				   eadverb = "dextrously";

			if (everb == " flips")
			{
				everb2 = " flip";
				eadverb = "acrobatically";
			}

			enemy->catch_msg("The links of " + QTNAME(wielder) + "'s "
			+ myshort + " wrap around your legs, but you manage to" + everb2
			+ " away " + eadverb + " before " + HE(wielder) + " can pull "
			+ "you off your feet.\n");
			wielder->catch_msg("The links of your " + myshort + " wrap around "
			+ QTNAME(enemy) + "'s legs as you pull with all your might, but "
			+ QTNAME(enemy) + everb + " away " + eadverb + ".\n");
			wielder->tell_watcher("The links of " + QTNAME(wielder) + "'s "
			+ myshort + " wrap around the legs of " + QTNAME(enemy) + " who"
			+ everb + " away " + eadverb + " before " + HE(enemy) + " can be "
			+ "pulled off " + HIS(enemy) + " feet.\n", enemy);
			return 1;
		}

		// Sufficiently skilled unarmed fighters can fight from the ground.
		if (uaskill >= 40 + random(40))
		{
			enemy->catch_msg("The links of " + QTNAME(wielder) + "'s "
			+ myshort + " wrap around your legs as " + HE(wielder)
			+ " jerks your legs out from under you, dropping you on your "
			+ "back!\nFortunately, your advanced fighting techniques allow "
			+ "you to continue fighting without missing a beat.\n");
			wielder->catch_msg("The links of your " + myshort + " wrap around "
			+ QTNAME(enemy) + "'s legs as you jerk with all your might, "
			+ "pulling " + HIM(enemy) + " off his feet!\nSomehow " + HE(enemy)
			+ " continues to fight from " + HIS(enemy) + " back.\n");
			wielder->tell_watcher("The links of " + QTNAME(wielder) + "'s "
			+ myshort + " wrap around the legs of " + QTNAME(enemy)
			+ " jerking " + HIM(enemy) + " off " + HIS(enemy) + " feet!\n"
			+ "Somehow " + HE(enemy) + " continues to fight from " + HIS(enemy)
			+ " back.\n", enemy);
			set_alarm(5.0, 0.0, "get_back_up", enemy);
			inuse = "in use";
			return 1;
		}

		// Enemy jerked off his feet for 3-6 seconds.
		enemy->catch_msg("The links of " + QTNAME(wielder) + "'s " + myshort
		+ " wrap around your legs as " + HE(wielder) + " jerks your legs "
		+ "out from under you, dropping you on your back!\n");
		wielder->catch_msg("The links of your " + myshort + " wrap around "
		+ QTNAME(enemy) + "'s legs as you jerk with all your might, pulling "
		+ HIM(enemy) + " off his feet!\n");
		wielder->tell_watcher("The links of " + QTNAME(wielder) + "'s "
		+ myshort + " wrap around the legs of " + QTNAME(enemy) + " jerking "
		+ HIM(enemy) + " off " + HIS(enemy) + " feet!\n", enemy);
		enemy->add_attack_delay(triptime);
		set_alarm(5.0, 0.0, "get_back_up", enemy);
		inuse = "in use";
		return 1;
	}

	return 1;
}

void
get_back_up(object enem)
{
	inuse = "not in use";

	if (!objectp(enem))
		return;

	else
	{
		enem->catch_msg("You leap back to your feet!\n");
		enem->tell_watcher(QCTNAME(enem) + " leaps back to " + HIS(enem)
		+ " feet!\n");
	}
}

string
query_inuse()
{
	return inuse;
}
