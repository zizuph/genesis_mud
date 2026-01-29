/*  -*- LPC -*-  */
/*
 * dainaxe.c
 *
 * Now Balin of the House of Durin's axe. (see below)
 * 
 * This is Dain Ironfoot's axe. It is supposed to be a
 * troll, orc and goblin slaying axe, specially designed
 * with magic for dwarves. Dwarves will get additional bonuses
 * for using it.
 *
 * Changed 31.07.96 due to a bug in the tellem() style combat messages
 * which didn't take into consideration the new query_option(OBT_BLOOD)
 * to filter players who wanted combat messages.
 * Odin.
 *  Added keepability functionality "/lib/keep"  -Igneous Dec 13 1996
 *  Lowered the stat requirements for wielding the axe because of the stat
 *  formula change. -Igneous June 11th 1997
 * 
 * Now Balin's Axe, as Dain Ironfoot was still alive and well, living
 * at the lonely mountain with his and Thorin Oakenshield's people.
 * As Balin was King of Khazad-Dum and of the true line of Durin 
 * there was a good chance that either he already had a powerful 
 * weapon or that one was recovered amongst the treasures of Moria.
 * Will leave the file name as is for simplicity's sake.
 *  - Jaypeg 7th December 1998
 */

#include "defs.h"
#include <cmdparse.h>

inherit "/std/weapon";
inherit "/lib/keep";

inherit "/d/Shire/moria/lib/hit_msg";
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <filter_funs.h>
#include <ss_types.h>

#define PLAYER_I_HAS_IDED_AXE   "_player_i_has_identified_dain's_axe"
#define HAS_IDED(obj)           obj->query_prop(PLAYER_I_HAS_IDED_AXE)

#define MIN_STR_2H      60
#define MIN_STR_1H     100
#define MIN_WIELD_SKILL 50

#define BAD_RACES ({ "troll", "orc", "uruk", "goblin", "half-troll", \
                     "peredhil", "yrch", "hobgoblin", "olog-hai", "uruk-hai" })

#define MIN_INT_DWARF   50 /* Minimum inteligence required for dwarves. */
#define MIN_INT         80 /* Minimum inteligence required for others. */
#define MIN_WIS_DWARF   70 /* Minimum wisdom required for dwarves. */
#define MIN_WIS        100 /* Minimum wisdom required for others. */

static int wielded_2h;

create_weapon() 
{
    set_name(({"axe","waraxe"}));
    add_name("_axe_of_balin");
    set_short("@@my_short@@");
    // set_pshort("waraxes");
    set_adj(({"ancient","balin's","dwarven","mithril",
              "magical","enchanted","large"}));
    set_long("@@my_long");
    set_hit(30);
    set_pen(52);
    set_likely_dull(0);
    set_likely_corr(0);
    set_likely_break(0);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    set_wf(TO);
    add_prop(MAGIC_AM_MAGIC,
      ({ 22, "enchantment", 40, "orc-slaying", 40, "troll-slaying" }));
    add_prop(MAGIC_AM_ID_INFO, ({ 
	"The dwarven waraxe seems to be very well crafted.\n", 1,
	"This dwarwen waraxe seems to possess unusual powers.\n",15,
	"It is made of mithril, so it is very powerful and even light.\n",34,
	"It is of slaying versus orcs and trolls.\n", 58
      }));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_LIGHT, 0);
    add_prop(OBJ_M_NO_BUY,1);

    add_prop(OBJ_I_VOLUME, 2200);
    add_prop(OBJ_I_WEIGHT, 6600); /* 6.6 kg: It is of Mithril. */
    add_prop(OBJ_I_VALUE,  6*F_VALUE_WEAPON(40, 40) + random(1000) - 500);

    add_item( ({ "waraxe's shaft", "waraxe's grip", "ornaments", "decorations",
	"shaft", "grip" }), "@@shaft_desc");
    add_item( ({ "waraxe's head", "head", "edges", "edge" }),
      "@@outlook_desc" );
}

init()
{
    ::init();
    add_action("do_wield", "wield");
    add_action("do_wield", "rewield");
    add_action("do_consider", "consider");
    add_action("do_ponder", "ponder");
}

/*
 * Returns a status of
 *     2:  Can only be wielded two-handed.
 *     1:  Can be wielded one-handed or two-handed.
 *     0:  Is not strong enough to wield it.
 *    -1:  Axe skill too low.
 *    -2:  Wisdom too low.
 *    -3:  Intelligence too low.
 */
int 
query_status(object who) 
{
    if (who->query_race_name() == "troll") 
	return 1;

    if (who->query_race_name() == "dwarf") {
	if (WIS(who) < MIN_WIS_DWARF)
	    return -2;
	if (INT(who) < MIN_INT_DWARF)
	    return -3;
    }
    else
    {
	if (WIS(who) < MIN_WIS)
	    return -2;
	if (INT(who) < MIN_INT)
	    return -3;
    }

    if (who->query_skill(SS_WEP_AXE) < MIN_WIELD_SKILL)
	return -1;
    else if (STR(who) < MIN_STR_2H)
	return 0;
    else if (STR(who) < MIN_STR_1H)
	return 2;
    else
	return 1;    
}

int
query_hands()
{
    if (query_status(TP) == 1) 
	return W_ANYH;
    else 
	return W_BOTH;
}

int 
query_wielded_2h()
{
    return wep_hands == W_BOTH;
}

#define VIS_ACCESS(arr, acsfunc, also_me, also_invis) \
    (object *) CMDPARSE_STD->visible_access(arr, acsfunc, TO, also_me, also_invis)

int
do_wield(string str)
{
    string hand, tmp, res;
    object what, *items;
    int hands;
    object wielder;
    int wield_status;

    if (TP->query_wiz_level()) 
	write("In do_wield:\n");

    wielder = TP;

    if (!strlen(str)) {
	notify_fail("Wield what?\n");
	return 0;
    }

    if (parse_command(str, all_inventory(TP), 
	"%i 'in' [my] [the] %w 'hand' / 'hands'", items, hand) ||
      parse_command(str, all_inventory(TP),
	"%i %w", items, tmp) ||
      parse_command(str, all_inventory(TP),
	"%i", items))
    {
	items = VIS_ACCESS(items, "query_pen", 1, 0);
	if (!sizeof(items))
	    return 0;
	what = items[0];

	if (what != TO)
	    return 0;

	wield_status = query_status(wielder);

	if (wielder->query_wiz_level())
	    write("wield_status = " + wield_status + "\n");

	switch (wield_status) 
	{
	case -3: 
	    write("You do not fathom how you would be able to wield this waraxe.\n");
	    return 1;
	case -2:
	    write("You lack wisdom to be able to wield the waraxe.\n");
	    return 1;
	case -1:
	    write("You are too unskilled to be able to swing it around properly.\n");
	    return 1;
	case 0:
	    write("This waraxe is far too heavy for you to wield properly.\n");
	    return 1;
	}

	if (strlen(tmp))
	    if (sscanf(tmp, "%shanded", hand) != 1)
		return notify_fail("Wield it left-handed or right-handed?\n");
	if (!strlen(hand))
	    hand = "any";

	if (hand=="two-" || hand=="two " || hand=="2-" || 
	  hand=="both" || hand=="two")
	    hands = W_BOTH;
	else if (hand=="left" || hand=="left-")
	    hands = W_LEFT;
	else if (hand=="right" || hand=="right-")
	    hands = W_RIGHT;
	else
	    hands = W_ANYH;

	if (query_wielded() && query_verb() != "rewield")
	    return notify_fail("Perhaps rewield it? (Or unwield it first.)\n");

	if (query_wielded() && wep_hands != hands)
	    unwield_me();

	if ((hands != W_BOTH) && wield_status != 1)
	    return notify_fail("You are too weak to wield it in one hand.\n");

	wep_hands = hands;
	wielded_2h = (wep_hands == W_BOTH);

	res = wield_me();
	if (stringp(res)) 
	    return notify_fail(res);
	return 1; 
    }
    return 0;
}

int
wield(object to)
{
    return 0;
}

int unwield(object to)
{
    wielded_2h=0;
    return 0;
}

string
history_desc()
{
     return
        "You realize that this is Balin's Axe.\n " +
        "This axe must be a heirloom of the House of Durin, "+
        "forged long ago for some great dwarf King.\n";
}

string
outlook_desc()
{
    if (query_status(TP) < 0)
	return ("You are looking at a marvelous dwarven waraxe with a twinkling " +
	  "and shining axe-head. The head has one slicing and one crushing " +
	  "edge. The sharp edge is semi-arced with, a thick cleaving " +
	  "section. The blunt edge, however, consists of a large head with a " +
	  "horrible mythical monster inscribed facing the opponent.\n");
    else
	return ("The waraxe is crafted in a typical dwarven fashion with a head "+
	  "made of precious Moria-silver, Mithril, making it twinkle and shine "+
	  "mysteriously.  The head has one slicing and one crushing "+
	  "edge. The sharp edge is semi-arced, with a thick cleaving section "+
	  "typically invented for armour penetration. The blunt edge, however, "+
	  "consists of a large head with a horrible mythical monster inscribed "+
	  "facing the opponent.\n");
}

string
shaft_desc()
{
    if (query_status(TP) < 0)
	return ("The shaft seems to be ornamented with strange intervening "+ 
	  "dragons and worms. It ends in a sturdy enforced leather.\n");
    else
	return ("The shaft is made of mithril as well, being ornamented with strange "+
	  "intervening dragons and worms. Its grip consists of "+
	  "sturdy enforced leather, and by its design you realize that it can "+
	  "be wielded both one- and two-handed, though being as heavy as it is, "+
	  "only strong dwarves could use it properly single-handed.\n");
}

string
conclusive_desc()
{
    if (query_status(TP) < 0)
	return ("What is rather unfortunate though is that you cannot " +
	  "quite understand how to wield this weapon. The grip seems " +
	  "very unnatural, and with the weight and balance of this weapon " +
	  "you would stumble and fall on first attempt.\n");
    else
	return ("All in all, the main impression of this weapon is that it must "+
	  "be a legendary dwarven artifact, not to be used by others than that "+
	  "of dwarves. You also suspect that such a well crafted weapon might "+
	  "have been magically enchanted as well, but neither the inscriptions "+
	  "nor the runes indicates in which way this has been done.\n");
}

string
my_long()
{
    return (HAS_IDED(TP) ? history_desc()+"\n":"") +
    outlook_desc()+"\n"+
    shaft_desc()+"\n"+
    conclusive_desc()+"\n";
}


int
do_consider(string str)
{
    if (id(str) && query_status(TP)>=-1)
    {
	write(history_desc());
	TP->add_prop(PLAYER_I_HAS_IDED_AXE, 1);
	say(QCTNAME(TP)+" considers "+HIS_HER(TP)+" waraxe.\n");
	return 1;
    }
    return 0;
}

int
do_ponder(string str)
{
    if (id(str))
    {
	write("Hmm, you wonder whose axe this once belonged to.\n" +
	  "I think you must consider other ways of figuring it out.\n");
	say(QCTNAME(TP)+" ponders the origin of "+HIS_HER(TP)+" waraxe.\n");
	return 1;
    }
    return 0;
}


string
my_short()
{

    if (HAS_IDED(TP))
	    return "ancient dwarven waraxe";
    else
	return "dwarven waraxe";
}

int
try_hit(object ob)
{
    object previous_wielder = query_wielded();
    int wep_status = query_status(query_wielded());

    if (wep_status > 0) 
	return 1;

    else
    {
	if (ENV(TO) == TP)
	{
	    write("You are confused by the waraxe!\n"+
	      "You can not use this weapon properly.\n");
	    TO->move(ENV(TP));
	    write("You drop the dwarven waraxe.\n");
	    tell_room(ENV(TO), previous_wielder->query_name()+
	      " stops wielding the dwarven waraxe.\n"+
	      previous_wielder->query_name()+" drops a "+
	      "dwarven waraxe.\n", previous_wielder);
	}
	return 0;
    }
}

public varargs int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam, int hid)
{
    object  tp; /* Who is wielding the axe. */
    int     extra_dam = 0;	// The extra damage.
    mixed   res;		// Result of the _______
    string  text = "";		// Extra text.
    string  shortie;		// Short of the weapon.
    int     wep_status;         // Weapon status.
    string hand;
    string hand2;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    wep_status = query_status(tp = query_wielded());
    change_prop(OBJ_I_LIGHT, 0);

    shortie = "dwarven waraxe";

    if (query_hands() == W_BOTH) 
    {
	hand = "both your hands";
	hand2 = "in both "+HIS_HER(tp)+" hands";
    }
    else if (query_hands() == W_LEFT)
    {
	hand = "in your left hand";
	hand2 = "in "+HIS_HER(tp)+" left hand";
    }
    else 
    {
	hand = "in your right hand";
	hand2 = "in "+HIS_HER(tp)+" right hand";  
    }

    /*
     * I want the players to use two hands. This
     * rewards them for that.
     */
    if (query_wielded_2h() && wep_status > 0) 
    {
	extra_dam += dam * random(STR(tp) - MIN_STR_2H) / 100;
	/*
	 * Overview
	 * Strength:     50     75    100      125    150     175     200
	 * Extra_dam:    0%    0-25%  0-50%   0-75%  0-100%  0-125%  0-150%
	 *
	 * Note that the extra damage is in percent of the origianal damage.
	 * I.e.: Only hits produce extra damage.
	 */ 

	shortie = "firm waraxe";
    }

    if (member_array(enemy->query_race(), BAD_RACES) >= 0)
    {
	if (dam <= 0 && !random(10))
	    extra_dam += random(100);     // 10 % that a miss really did hit.
	else
	    extra_dam += dam * random(50) / 100;       // 0-49 % extra damage.
	shortie = "glowing waraxe";
	change_prop(OBJ_I_LIGHT, 1);
    }

    if (enemy->query_race() == "orc" ||
      enemy->query_race() == "troll" ||
      enemy->query_race() == "goblin")
    {
	if (TO->query_attack_id() == W_BOTH)
	{
	    tp->catch_msg("Your dwarven waraxe glows pale red as "+
	      "you firmly hold it in both your hands.\n");
	    enemy->catch_msg(QCTNAME(tp)+"'s dwarven waraxe glows pale "+
	      "red as "+HE_SHE(tp)+" firmly hold it in both "+
	      HIS_HER(tp)+" hands!\n");
	    tp->tell_watcher(QCTNAME(tp)+"'s dwarven waraxe glows pale "+
	      "red as "+HE_SHE(tp)+" firmly holds it in both "+
	      HIS_HER(tp)+" hands!\n");
	}
	else if (TO->query_attack_id() == W_LEFT)
	{
	    tp->catch_msg("Your dwarven waraxe glows pale red as "+
	      "you firmly hold it in your left hand.\n");
	    enemy->catch_msg(QCTNAME(tp)+"'s dwarven waraxe glows pale "+
	      "red as "+HE_SHE(tp)+" firmly hold it in in "+HIS_HER(tp)+
	      " left hand!\n");
	    tp->tell_watcher(QCTNAME(tp)+"'s dwarven waraxe glows pale "+
	      "red as "+HE_SHE(tp)+" firmly holds it in "+HIS_HER(tp)+
	      " left hand!\n");
	}
	else
	{
	    tp->catch_msg("Your dwarven waraxe glows pale red as "+
	      "you firmly hold it in your right hand.\n");
	    enemy->catch_msg(QCTNAME(tp)+"'s dwarven waraxe glows pale "+
	      "red as "+HE_SHE(tp)+" firmly holds it in "+
	      HIS_HER(tp)+" right hand!\n");
	    tp->tell_watcher(QCTNAME(tp)+"'s dwarven waraxe glows pale "+
	      "red color as "+HE_SHE(tp)+" firmly holds it in "+HIS_HER(tp)+
	      " right hand!\n");
	}
    }
    /*
     * Now, only those who has identified this axe are permitted
     * to the extra damage. Non-dwarves recieve only 1/3 extra dam.
     */
    if (HAS_IDED(tp) && extra_dam >= 0)
    {
	/* Of course, only dwarves can fight well with a dwarven waraxe. */
	if (tp->query_race_name() != "dwarf")
	    extra_dam /= 3; 

	//
	// Reduces the extra damage linearly from 0 to 100%
	// as a function of SS_WEP_AXE.
	//

	extra_dam = extra_dam * (tp->query_skill(SS_WEP_AXE) - MIN_WIELD_SKILL) / (100 - MIN_WIELD_SKILL);

	enemy->heal_hp(-extra_dam);
	phurt += extra_dam*100/MAX_HP(enemy);
	//tp->catch_msg("Damage: "+extra_dam+", %hurt: "+phurt+".\n");
    }

    if (dt==0)
	dt = random(2) ? W_SLASH : W_BLUDGEON;

    produce_msg(enemy,hdesc,MIN(phurt,100),dt,shortie);
    return 1;
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_reocver(string arg)
{
    init_wep_recover(arg);

    init_keep_recover(arg);
}
