/*
 * Enchanted polearm used by Kirk the leader of the
 * Brix gang of Jems Court in the aesthetics
 * quarter of Palanthas.  Drains mana on special from
 * enemy and transfers a little to wielder based on
 * spellcraft.
 *
 * If the chance to break is ever successful, it will
 * drain health from its wielder to attempt to resist
 * breaking even at the expense of its wielder's life.
 *
 * Find out prop set in weapon after narusse so it can
 * be removed.
 *
 * <research topic> function in library or shop?
 *
 * Mortis 06.2006
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include "../../local.h"
#include <macros.h>
#include <options.h>
#include <wa_types.h>
#include <ss_types.h>

// Prototypes
void wield_msg(object mwield);
void unwield_msg(object munwield);
string read_runes();

create_weapon()
{
	set_name("blade-spear");
	add_name(({"spear"}));
	set_adj("short");
	add_adj(({"iron-hafted", "iron", "hafted", "blade"}));
	set_short("short iron-hafted blade-spear");
	set_long("Forged into one single length of solid iron, this dark "
	+ "burnished spear has a shortened haft of four feet ending in two "
	+ "feet of blade curved back slightly for ease in slicing through "
	+ "foes.  Thick, blocky runes indented into the haft band its entire "
	+ "length.\n");

	set_hit(45);
	set_pen(40);
	set_wt(W_POLEARM);
	set_dt(W_SLASH);
	set_hands(W_BOTH);
	set_wf(TO);

	set_likely_dull(8);   // Decr. chance to dull due to protective magicks.
	set_likely_corr(8);	  // Decr. chance to corrode due to magicks.
	set_likely_break(8);  /* Decr. chance to break due to its desire to
	                       * survive at any cost. */
	
	set_keep(1);

	ITEM(({"runes", "thick runes", "blocky runes", "thick blocky runes"}),
	  "Thick, blocky runes indented into the haft of the blade-spear band "
	+ "its entire length.  " + "@@read_runes");
	
	add_prop(OBJ_M_NO_SELL, "The shopkeeper cannot afford to buy " +
      "magical weapons.  You will have to find another market.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({37, "death"}));
    add_prop(MAGIC_AM_ID_INFO, ({"Your arcane prowess reveals this weapon "
	+ "harnesses a power to drain energy from foes for the benefit of its "
	+ "wielder, but there's something greater deep within.\n", 20,
	  "A life force is trapped within the spear.  You suddenly realize "
	+ "this weapon harnesses the power of death.\n", 50,
	  "As you probe the blocky runes with your senses, they reveal their "
	+ "meaning:\n\n"
	+ "  Vriz in the days before the Highlords swept and the winged ones "
	+ "foul felled the Stormcloud horizon.  Akrameur early of the black "
	+ "order under cover of the unseen moon felt its shine draw him deep "
	+ "to the broken table in the chasm beneath the vale of the Tower to "
	+ "discover the chrosic runes revealed within the crack.\n\n"
	+ "  Ksordch now the drive from life to persist is unrivaled among "
	+ "desires.  With not energy from the other side here to the golden "
	+ "barrier and bind my apprentice eternal in blood rich iron that "
	+ "his drive will guide the flow from blade to mind.\n\n"
	+ "Prison eternal.  To never release.  Zynsis within and the flow "
	+ "ceaseless.\n\n"
	+ "                         _____________________\n"
	+ "		        |                     |\n"
	+ "		        | Senotil Denunciarus |\n"
	+ "			|_____________________|\n\n", 75}));

	add_prop(OBJ_S_WIZINFO, "Drains health from enemy and transfers a small "
	+ "amount of mana to wielder based on spellcraft.  Resists being broken "
	+ "by draining health from wielder (can be lethal).  Resists damage from "
	+ "Narusse spell.  Can be broken to release imprisoned mage.\n");

    add_prop(OBJ_I_WEIGHT, 4800 + random(700));
    add_prop(OBJ_I_VOLUME, 2600 + random(500));
    add_prop(OBJ_I_VALUE,  1400 + random(300));
}

int
swing(string str)
{
	object amiwielded;

	NF("Swing what through the air?  Your " + short() + "?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] [my] [short] [iron] [iron-hafted] [hafted] [blade] 'blade-spear' / 'spear' [through] [the] [air]"))
		return 0;
	
	NF("You must be wielding your " + short() + " in order to swing it.\n");
	if (!(amiwielded = query_wielded()))
		return 0;

	write("You swing your " + short() + " in a measured swath through the "
	+ "air.  Heavy as the iron is, the blade feels guided and "
	+ "preturnaturally balanced.\n");
	say(QCTNAME(TP) + " guides " + HIS(TP) + " " + short() + " through the "
	+ "air with measured ease and seemingly unnatural control.\n");
	return 1;
}

void
init()
{
    ::init();

	ADA("swing");
}

string
read_runes()
{
	string rrunes = "You have never seen their like before and can only "
	+ "guess at their meaning.\n";

	if (TP->query_skill(SS_LANGUAGE) >= 55)
	{
		rrunes = "You cannot make out any of them, but you suspect they "
		+ "could be chrosic runes.  However, those are just a myth.\n";
	}

	if (TP->query_skill(SS_LANGUAGE) >= 95)
	{	
		rrunes = "They are chrosic runes, supposedly a myth.  They read:\n\n"
		+ "  Vriz in the days before the Highlords swept and the "
		+ "winged ones foul felled the Stormcloud horizon.  Akrameur early of "
		+ "the black order under cover of the unseen moon felt its shine draw "
		+ "him deep to the broken table in the chasm beneath the vale of the "
		+ "Tower to discover the chrosic runes revealed within the crack.\n\n"
		+ "  Ksordch now the drive from life to persist is unrivaled among "
		+ "desires.  With not energy from the other side here to the golden "
		+ "barrier and bind my apprentice eternal in blood rich iron that "
		+ "his drive will guide the flow from blade to mind.\n\n"
		+ "Prison eternal.  To never release.  Zynsis within and the flow "
		+ "ceaseless.\n\n"
		+ "                     _____________________\n"
		+ "		    |                     |\n"
		+ "		    | Senotil Denunciarus |\n"
		+ "		    |_____________________|\n\n";
	}
	return rrunes;
}

mixed
wield(object what)
{
	set_alarm(1.0, 0.0, &wield_msg(wielder));

	return 0;
}

mixed
unwield(object what)
{
	set_alarm(1.0, 0.0, &unwield_msg(wielder));

    return 0;
}

void
wield_msg(object mwield)
{
	int	spower = mwield->query_skill(SS_SPELLCRAFT),
		dpower = mwield->query_skill(SS_ELEMENT_DEATH);

	string sp_msg = "",
		   dp_msg = "";

	switch (spower)
	{
		case 45..55:
			sp_msg = " and feel a thrum of power from within";
			break;
		case 56..100:
			sp_msg = " and feel a thrum of power from the thick, blocky "
			+ "runes banding its haft as they briefly pulse with a pale, "
			+ "rust-red light";
			break;
		default:
			break;
	}

	switch (dpower)
	{
		case 35..45:
			dp_msg = ".  You sense a deathly power from within";
			break;
		case 46..100:
			dp_msg = ".  You sense an arcane power trapped within between "
			+ "life and death";
			break;
		default:
			break;
	}

	mwield->catch_msg("You grasp the iron haft of the " + short()
	+ sp_msg + dp_msg + ".\n");

	if (spower > 55)
		say("The thick, blocky runes banding the haft of " + QTNAME(mwield)
		+ "'s " + short() + " briefly pulse with a pale, rust-red light.\n",
		mwield);

	if (mwield->query_align() > 0)
	{
		string gmsg = one_of_list(({"The evil within... so powerful...",
		"So evil... Can't take the...", "Evil... death... nooooo!",
		"So evil... I don't feel so goo...", "Oh, frung..."}));

		mwield->command("emote groans:  " + gmsg + "\n");
		mwield->command("puke");
	}
}

void
unwield_msg(object munwield)
{
	if (munwield->query_align() > 0)
	{
		string gmsg = one_of_list(({"Praise the gods it's over!",
		"Evil, begone!", "My soul feels tinged by the evil within.",
		"Why must the evil persist?", "I cry for the soul within.",
		"There are tears in my soul for the life within."}));

		munwield->command("emote sighs in relief:  " + gmsg + "\n");
	}
}

/*
 * Function name: remove_broken
 * Description  : The spear has had a successful check to be broken.
 *                Now it resists the break by draining health from its
 *                wielder.
 * Arguments    : int silent - true if no message is to be generated
 *                             about the fact that the weapon broke.
 */
varargs void
remove_broken(int silent = 0)
{
	object mywielder = TO->query_wielded();

    if (calling_function() == "item_expiration_break") 
        ::remove_broken(silent);

    /* If the weapon is not wielded, we only adjust the broken information
     * by adding the adjective and the property. We do this within the
     * if-statement since we do not want to screw the message that may
     * be displayed later. When the property is added, the adjective is
     * added automatically.
     */
    if (mywielder == 0)
    {
		object my_env = E(TO);

		if (living(my_env))
		{
			write("Your " + short() + " thrumms reverberantly sending "
			+ "shockwaves of resistance through you.\nYou sense great "
			+ "resistance within the spear.\n");
			say(QCTNAME(my_env) + " shudders in surprise as the " + short()
			+ " " + HE(my_env) + " is holding thrumms reverberantly "
			+ "sending shockwaves through the room.\n");
			return;
		}

		tell_room(my_env, "The " + short() + " thrumms reverberantly "
		+ "sending shockwaves of resistance throughout the room.\n");

        /* add_prop(OBJ_I_BROKEN, 1); Not ready to have this broken
		 * unwielded.  Eventually may allow it when Zynsis is coded.
		 */
        return;
    }

	/* If the weapon is wielded, it will drain health from its wielder to
	 * help it resist being broken.
	 */
	int mydull = query_dull(),
		rfactor = 25 + random(26),
		wdmg = 500 + mydull * rfactor;
	
	if (!mywielder->query_npc())
		mywielder->heal_hp(-wdmg);

	if (TP->query_hp() <= 0)
	{
		mywielder->catch_msg("The thick, blocky runes indented in bands "
		+ "around your " + short() + " erupt in pale, rust-red light as it "
		+ "threatens to break.\n\nUnable to release your grip, you feel your "
		+ "life's energy drained completely into the dark iron of the "
		+ "spear!\n\nThe spear emanates defiance and a sense of relief as "
		+ "you feel the last of your life force ebbing away...\n");
		tell_room(E(mywielder), "The thick, blocky runes indented in bands "
		+ "around the " + short() + " of " + QTNAME(mywielder) + " erupt in "
		+ "pale, rust-red light.\n\n" + QCTNAME(mywielder) + "'s eyes blaze "
		+ "beams of rust-red light that slowly ebb as " + HE(mywielder)
		+ " crumples into a heap.\n", mywielder);

		set_weapon_hits(0);

		TP->do_die(TO);
		return;
	}

	mywielder->catch_msg("The thick, blocky runes indented in bands around "
	+ "your " + short() + " erupt in pale, rust-red light as it threatens "
	+ "to break.\n\nUnable to release your grip, you feel your life's energy "
	+ "drained drastically into the dark iron of the spear!\n"
	+ "You cry out:  Betrayor apprentice!  I will not cross the barrier "
	+ "without my vengeance!\n");
	tell_room(E(mywielder), "The thick, blocky runes indented in bands "
	+ "around the " + short() + " of " + QTNAME(mywielder) + " erupt in "
	+ "pale, rust-red light draining " + HIM(mywielder) + " of energy.\n"
	+ QCTNAME(mywielder) + " cries out:  Betrayor apprentice!  I will "
	+ "not cross the barrier without my vengeance!", mywielder);

	return;
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    switch(phurt)
    {
	case -2..-1:
		if (!wielder->query_option(OPT_GAG_MISSES))
		{
			wielder->catch_msg(one_of_list(({"You slash at " + QTNAME(enemy)
			+ " with your " + short() + " missing barely.",
			  "You slice your " + short() + " in a wide arc at "
			+ QTNAME(enemy) + " but miss."})) + "\n");
		}
	
		if (!enemy->query_option(OPT_GAG_MISSES))
		{
			enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" slashes at "
			+ "you with " + HIS(wielder) + " " + short() + " missing barely.",
			  " slices " + HIS(wielder) + " " + short() + " in a wide arc at "
			+ "you but misses."})) + "\n");
		}

		wielder->tell_watcher_miss(QCTNAME(wielder) + one_of_list(({" slashes "
		+ "at " + QTNAME(enemy) + " with " + HIS(wielder) + " " + short()
		+ " missing barely.",
		  " slices " + HIS(wielder) + " " + short() + " in a wide arc at "
		+ QTNAME(enemy) + " but misses."})) + ".\n", enemy);
		break;

    case 0..4:
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
		+ HIS(wielder) + " " + short() + " drawing a dark line of blood."}))
		+ "\n", enemy);
		break;

    case 5..10:
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
		break;

	case 11..18:
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
		break;

	case 19..30:
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
		break;

	case 31..90:
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
		+ " with " + HIS(wielder) + " " + " " + short() + " as it lands in a "
		+ "deadly arc."})) + "\n", enemy);
		break;

    default:
		wielder->catch_msg(one_of_list(({"You trench the dark burnished iron "
		+ "of your " + short() + " through " + QTNAME(enemy) + " as gore "
		+ "sprays forth from " + HIS(enemy) + " " + hdesc + ".",
		  "You trench the dark burnished iron of your " + short() + " through "
		+ QTNAME(enemy) + "'s " + hdesc + " sending gore spraying forth from "
		+ "the wound."})) + "\n");
		enemy->catch_msg(QCTNAME(wielder) + one_of_list(({" trenches the "
		+ "dark burnished iron of " + HIS(wielder) + " " + short()
		+ " through you as gore sprays forth from your " + hdesc + ".",
		  " trenches the dark burnished iron of " + HIS(wielder) + " "
		+ short() + " through your " + hdesc+ " sending gore spraying forth "
		+ "from the wound."})) + "\n");
		wielder->tell_watcher(QCTNAME(wielder) + one_of_list(({" trenches "
		+ "the dark burnished iron of " + HIS(wielder) + " " + short()
		+ " through " + QTNAME(enemy) + " as gore sprays forth from "
		+ HIS(enemy) + " " + hdesc + ".",
		  " trenches the dark burnished iron of " + HIS(wielder) + " "
		+ short() + " through " + QTNAME(enemy) + "'s " + hdesc+ " sending "
		+ "gore spraying forth from the wound."})) + "\n", enemy);
		break;
    }

	// Check % special first to minimize processing, x = wielder's spellcraft
	if (random(130) >= wielder->query_skill(SS_SPELLCRAFT))
		return 1;

	int dmana,
		dmana_back,
		res = enemy->query_magic_res(MAGIC_I_RES_DEATH),
		dpower = wielder->query_skill(SS_ELEMENT_DEATH);
	string wshort = short();
	object wroom = E(wielder);

	dmana = dam * dpower / 100;
	dmana = dmana - (dmana * res/100);

	switch (dmana)
	{
		case -2..5:
			enemy->catch_msg("Your heart nearly skips a beat as you "
			+ one_of_list(({"barely", "nearly fail to ", "narrowly"}))
			+ " resist a force within the " + wshort + ".\n");
			wielder->catch_msg("Your " + wshort + " thrumms reverberantly in "
			+ "your hands as " + QTNAME(enemy) + " resists its forces.\n");
			dmana_back = 0;
			break;
		case 6..35:
			enemy->catch_msg("Your heart skips a beat in shock as a force "
			+ "from within the " + wshort + " feeds on your lost energy.\n");
			wielder->catch_msg("A pale, rust-red light flashes briefly from "
			+ "the blocky runes of your " + wshort + " rejuvenating your "
			+ "mind.\n");
			dmana_back = 1;
			break;
		case 36..60:
			enemy->catch_msg("Your heart skips a beat in shock as a force "
			+ "from within the " + wshort + " sates itself on your lost "
			+ "energy.\n");
			wielder->catch_msg("A pale, rust-red light throbs from deep "
			+ "within the blocky runes of your " + wshort + " rejuvenating "
			+ "your mind.\n");
			dmana_back = 2;
			break;
		default:
			enemy->catch_msg("A pale, rust-red light throbs from deep within "
			+ "the blocky runes banding the haft of " + QTNAME(wielder)
			+ "'s " + wshort + " as you feel it sating itself on your lost "
			+ "energies.\n");
			wielder->catch_msg("A pale, rust-red light pulses vigorously from "
			+ "deep within the blocky runes of your " + wshort
			+ " rejuvenating your mind.\n");
			tell_room(wroom, "A pale, rust-red light throbs from deep within "
			+ "the blocky runes banding the haft of " + QTNAME(wielder)
			+ "'s " + wshort + ".\n", ({wielder, enemy}));
			dmana_back = 3;
			break;	
	}

	if (dmana_back > 0)
		wielder->add_mana(dmana_back);

	return 1;
}


/*
  Vriz in the days before the Highlords swept and the winged ones
foul felled the Stormcloud horizon.  Akrameur early of the black
order under cover of the unseen moon felt its shine draw him deep
to the broken table in the chasm beneath the vale of the Tower to
discover the chrosic runes revealed within the crack.

  Ksordch now the drive from life to persist is unrivaled among
desires.  With not energy from the other side here to the golden
barrier and bind my apprentice eternal in blood rich iron that
his drive will guide the flow from blade to mind.

  Prison eternal.  To never release.  Zynsis within and the flow
ceaseless.
                      _____________________
					 |                     |
				   ~ | Senotil Denunciarus | ~
					 |_____________________|
*/
/*
<research mages akrameur>

Excerpt from Mahler's High Sorcery Guide:

  Akrameur, an early archmage of the black order of high sorcery,
his deep delvings yielded the first exposure of Phosphentus to
the surface world.  It was said Akrameur was far ahead of his peers
in his research into the barrier between life and death.  Before
his tower was swallowed by a race only referred to as underdwellers,
eyewitness accounts told of carvings of blocky, almost crude looking
runes adorning its outer stones.  Rumoured to be older than many of
the ancient ones, their only known named reference was chrosic.
None of his research survived, and no spells in the compendium are
attributed to him.

<research mages senotil>

There is no reference to any mage or renegade mage named Senotil.

<research mages zynsis>

Excerpt from Mahler's High Sorcery Guide:

  Zynsis, mage of the black order of high sorcery, a master of the
interpretation of translations of many languages present and past.
Zynsis disappeared completely several months after returning from
an expedition reportedly beneath the Palanthian vale.

*/
/*
<research apprentices zynsis>

There is no reference to any apprentice or renegade apprentice named
Zynsis.

<research apprentices senotil>
Senotil, black order apprentice to the mage Zynsis, went renegade
after the disappearance of his master.  Was tracked to an estate in
Palanthas and killed in a standoff with high sorcery marshals when
the house collapsed.

/*
<research chrosic / chrosic runes>

Excerpt from Engyru & Rune Call:

  Derived from the presario tongue, chrosic runes, mythical runes of
unknown origin, bore claims to an age before our own long outdating
Engyru.  No examples are known to exist.  See <mages Akrameur> in
Mahler's High Sorcery Guide.
  
*/
