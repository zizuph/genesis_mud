/*
 * Name: Kitiara's Sword    (unnamed)
 * Creator: Morrigan       Date: 5/5/97
 *
 * Magical abilities:
 * The sword is sencient, and is both arrogant and ambitious
 * like Kitiara. The sword is neither good nor evil, it only
 * longs to be in the hands of a powerful being, it seeks
 * recognition and fame. It refuses to be wielded by cowards,
 * those who focus on certain stats to a much greater extent
 * than their discipline. It also refuses to be "share" its
 * wielder with any other weapon, meaning it will not let the
 * wielder wield two weapons, even though it is one-handed.
 * It adds a small amount of quickness as well as parry for
 * the wielder (this is to simulate a magical weapon of speed
 * both offensively and defensively). It will not grow dull
 * or break, and will be especially effective against enemies
 * wielding magical weapons as it will try to compete with
 * those other weapons.
 *
 * Magical ability implementation based on a prototype sword
 * by Majere, from long ago, that has apparently seen no use.
 *
 * Revision history:
 *    Aridor   97/10/16: Added /lib/keep, Added gagmisses support,
 *                       Fixed a runtime error (hopefully).
 *
 * Navarre, March 19th 2010:
 * The chatterboxing didn't correctly check if the enemy had a
 * sword before it started talking about it
 * (and calling weapon->short() on 0);
 *
 * Shanoga, 2021 May 19:
 *   Fixed shadow removal on unwield. Now calls the funtion
 *   "remove_kit_sword_shadow" which has been placed in both
 *   shadows to make sure that the correct shadow is removed.
 *   Previously was removing the most recently-added shadow
 *   rather than just the sword shadow.
 *
 * Ckrik, 2022 Jul 6:
 *   Fixed wield function to prevent stacking of effects.
 */
inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <options.h>

/* Global Variables */
int gQuick_extra, gParry_extra, gModified, gFury;
object gShadow;

/* Definitions */
#define SHADOW "/d/Krynn/solamn/splains/obj/wielder_shadow"
#define KIT_SHADOW "/d/Krynn/solamn/splains/obj/kitiara_shadow"
#define TELL_TIME 30
#define RAISE_FURY_CHANCE 5
#define ATTACK_ON_FURY 10
#define MAX_FURY 10
#define QUICKNESS_EXTRA 33
#define PARRY_EXTRA query_wielded()->query_skill(SS_WEP_SWORD) / 10


/*
 * Function name: query_fury
 * Description  : Returns the fury level of the sword as an integer.
 * Arguments    : None.
 * Returns      : See description.
 */
int query_fury()
{
    return gFury;
}


/*
 * Function name: set_fury
 * Description  : Sets the fury level of the sword.
 * Arguments    : int fury = the level to set the fury to.
 *                int shown = if shown is true, the change in fury
 *                   level will be visible, otherwise it is not.
 * Returns      : Nothing.
 */
varargs set_fury(int fury, int shown = 1)
{
    object enemies, me = E(TO);

    if (fury < 0)
	fury = 0;

    if (fury > MAX_FURY)
	fury = MAX_FURY;

    if (gFury < 5 && fury >= 5 && shown)
    {
	tell_room(E(me), QCTNAME(me)+"'s "+short()+" begins to glow "+
	  "a pale green colour.\n", me);
	me->catch_msg("Your "+short()+" begins to glow a pale green "+
	  "colour.\n");
    }

    if (gFury > 5 && fury > gFury && shown)
    {
	tell_room(E(me), "The glow around "+QTNAME(me)+"'s "+short()+
	  " grows more intense.\n", me);
	me->catch_msg("The glow around your "+short()+" grows more "+
	  "intense.\n");
    }

    if (gFury > 0 && fury == 0 && shown) 
    {
	tell_room(E(me), "The glow around the "+short()+" dies out.\n",
	  me);
	me->catch_msg("The glow around the "+short()+" dies out.\n");
    }

    if (query_wielded()->query_wiz_level())
	query_wielded()->catch_msg("DEBUG:FURY - "+fury+"    "+
	  "(Raised: "+(fury-gFury)+")\n");
    gFury = fury;
}


/*
 * Function name: short_desc
 * Description  : Returns the string short description.
 * Arguments    : None.
 * Returns      : See description.
 */
string short_desc()
{
    int fury = query_fury();

    switch(fury)
    {
    case 0..4:
	return "elegant jewel-encrusted sabre";
	break;
    case 5..7:
	return "glittering jewel-encrusted sabre";
	break;
    case 8..9:
	return "gleaming jewel-encrusted sabre";
	break;
    default:
	return "glowing jewel-encrusted sabre";
	break;
    }
}


/*
 * Function name: long_desc
 * Description  : Returns the string long description.
 * Arguments    : None.
 * Returns      : See description.
 */
string long_desc()
{
    return "Magnificence. The word echoes through your mind as "+
    "you study the lustrous sabre, perfect in every way. From "+
    "hilt to tip it measures not even a meter, shorter than a "+
    "typical longsword, and more slender. The glistening blade "+
    "narrows as it curves away from the golden hilt, in which "+
    "a large emerald is set. The slender pommel of the blade "+
    "also curves, making the entire sabre bent like a crescent "+
    "moon.\n";
}


/*
 * Function name: rune_desc
 * Description  : Determines whether the reader can understand
 *                the runes on the sword or not.
 * Arguments    : None.
 * Returns      : String of the runes, either readable or not.
 */
string rune_desc()
{
    if ((TP->query_race() == "elf" &&
	TP->query_skill(SS_LANGUAGE) < 50) ||
      (TP->query_race() != "elf" &&
	TP->query_skill(SS_LANGUAGE) < 60))
	return "You try to decipher the runes, but you are not "+
	"able to.\n";

    return "You easily recognize the runes as elven, but are "+
    "amazed at the dialect which must be ancient. You can "+
    "piece together some of them, and they seem to be in "+
    "this order:\n"+
    "       From the sky of this Dream's Dance,\n"+
    "       In which Eyes unblinking look down,\n"+
    "       The Come of Winter, the Age of Light,\n"+
    "       To the world comes this item of renown.\n"+
    "The rest of the runes are unreadable.\n";
}


/* 
 * Function name: create_weapon
 * Description  : Turns this object into a weapon.
 * Arguments    : None.
 * Returns      : Nothing.
 */
void create_weapon()
{
    set_name("sword");
    add_name("sabre");
    add_adj(({"elegant", "jewel-encrusted"}));
    set_short("@@short_desc");
    set_long("@@long_desc");
    add_item("hilt", "The elegant blade is decorated with a "+
      "hilt of gold, in which is set a flawless emerald, large "+
      "enough to be seen on both sides of the thin blade's "+
      "handle. Intricate designs are carved on the hilt, they "+
      "look like runes of some sort.\n");
    add_item(({"gem", "emerald"}), "The flawless gem shimmers "+
      "in the light of the area, and you marvel at how much "+
      "the gem alone must be worth.\n");
    add_item(({"designs", "runes"}), "The designs are actually "+
      "runes carved into the hilt, perhaps you are able to "+
      "decipher their meaning.\n");
    add_cmd_item(({"designs", "runes"}), ({"read", "decipher",
	"translate"}), "@@rune_desc");

    add_prop(OBJ_M_NO_BUY, "As the shopkeeper prepares to "+
      "release the blade into your possession, a change of "+
      "mind sets in, and you cannot sway him.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This is a sabre of elven make "+
      "and magic, created in the Age of Light on the last "+
      "Dream's Dance (Thursday) of Winter Come (December) "+
      "on a night in which at least two of the three moons "+
      "were at the peak of their cycle. It is possible that "+
      "the dark moon, too, was at its peak, because the "+
      "elves would not have been able to see it and would "+
      "probably not have spoken of it even if they had. It "+
      "is now owned by Kitiara, and grants the wielder "+
      "quickness. It is very competitive, especially towards "+
      "other magical weapons; it refuses to be wielded with "+
      "another weapon, and will try to show off to prove its "+
      "superiority around other magic weapons more often.\n");
    add_prop(MAGIC_AM_ID_INFO,
      ({ "The weapon is enchanted.\n", 5,
	"It is blessed by elven magic, from the Age of Light, "+
	"created on a night of sanction.\n", 10,
	"The sword is sentient and is both arrogant and "+
	"ambitious, it will not share its wielder with any "+
	"other weapon because of this.\n", 25,
	"It has magical properties which grant the wielder "+
	"enhanced speed, and will make an effort to prove "+
	"its superiority when facing magical weapons in "+
	"battle.\n", 50}));
    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, 3000 + random(500));

    set_default_weapon(45, 40, W_SWORD, W_SLASH, W_ANYH);
    set_likely_break(0);
    seteuid(getuid(TO));
    set_wf(TO);
}


/*
 * Function name: wield_message
 * Description  : Adds abilities to the wielder.
 * Arguments    : object ob = wielder.
 * Returns      : Nothing.
 */
void wield_message(object ob)
{
    string str;

    if (!query_wielded() || query_wielded() != ob)
	return;

    if (sizeof(ob->query_weapons(-1)) > 1) {
    ob->catch_msg("You feel the "+short()+"'s anger at having to "+
        "share you with another weapon!\n");
        ob->command("$unwield all");
        return;
    }

    // Ckrik, 20220706 Naughty players can quickly wield/unwield and stack
    // effects without this check
    if (gModified)
    return;

    gModified = 1;

    gParry_extra = PARRY_EXTRA;
    gQuick_extra = QUICKNESS_EXTRA;

    ob->set_skill_extra(SS_PARRY, ob->query_skill_extra(SS_PARRY) +
      gParry_extra);
    ob->add_prop(LIVE_I_QUICKNESS, ob->query_prop(LIVE_I_QUICKNESS) +
      gQuick_extra);

    if (ob->query_alignment() > 500)
	str = "evil being vanquished from the world at your hands";
    else if (ob->query_alignment() < -500)
	str = "lands being conquered and brought under your control";
    else
	str = "fame and wealth";

    ob->catch_msg("Visions of "+str+" cloud your mind, and the "+short()+
      " in your hand pulses with life at your thoughts, as if "+
      "yearning to aid you in realizing your dreams. You feel "+
      "renewed with energy, and you feel your dreams will soon "+
      "become reality with the aid of this magnificent weapon.\n");
}


/*
 * Function name: unwield
 * Description  : Unwields the weapon, removes added abilities and
 *                wielder shadow from the former wielder.
 * Arguments    : object what = the weapon attemting to unwield.
 * Returns      : Nothing.
 */
mixed unwield(object what)
{
    object me = query_wielded();

    if (gModified == 1)
    {
	if (me)
	{
	    me->change_prop(LIVE_I_QUICKNESS, 
	      me->query_prop(LIVE_I_QUICKNESS) - gQuick_extra);
	    me->set_skill_extra(SS_PARRY, 
	      me->query_skill_extra(SS_PARRY) - gParry_extra);
        gQuick_extra = 0;
        gParry_extra = 0;
	}
	gModified = 0;
    }

    if (me)
    {
	me->catch_msg("As you release your grasp on the "+short()+
	  ", you feel tired, a little clumsy, and incomplete.\n");
	tell_room(E(me), QCTNAME(me)+" releases "+POSSESSIVE(me)+
	  " grip on the "+short()+".\n", me);
	set_fury(0);
    }

    if (gFury > 0)
	set_fury(0, 0);

    gShadow->remove_kit_sword_shadow();
    return 0;
}


/* 
 * Function name: wield
 * Description  : Wields the sword, adds the wielder shadow to wielder.
 * Arguments    : object what = object attempting to wield.
 * Returns      : True if wielded, string with failure message if not
 *                wielded.
 */
mixed wield(object what)
{
    string str;
    object *weapons;

    if (max(TP->query_stat(SS_STR), TP->query_stat(SS_DEX),
	TP->query_stat(SS_CON), TP->query_stat(SS_INT),
	TP->query_stat(SS_WIS)) > TP->query_stat(SS_DIS) +
      TP->query_stat(SS_DIS) / 4)
	return "A feeling of terror grips your mind as you "+
	"grasp the hilt of the "+short()+". Morbid images "+
	"of broken and shattered bodies plague your thoughts "+
	"and you are forced to release the blade.\n";

    if (TP->query_skill(SS_WEP_SWORD) < 60)
	return "As you grasp the hilt of the "+short()+", you "+
	"are overcome with a feeling of despair and worth"+
	"lessness. A fog of depression settles over your "+
	"soul, and with a flash of insight, you release "+
	"the blade. Your mind is instantly more at ease.\n";

    if ((weapons = E(TO)->query_weapon(-1))[sizeof(weapons) - 1] != TO ||
      sizeof(weapons) > 1)
	return "The emerald set in the hilt of your "+short()+
	" flares up, casting a pale green glow along the "+
	"blade. You feel a yearning to use the elegant "+
	"blade, but something deep inside you realizes "+
	"that it will not accept you as its wielder.\n";

    if (TP->query_alignment() > 500)
	str = "righteous indignation at the evil in the world";
    else if (TP->query_alignment() < -500)
	str = "confidence to destroy those foolish of the world "+
	"who would oppose you";
    else
	str = "power to defeat your enemies";

    set_alarm(10.0, 0.0, "wield_message", TP);
    write("You grasp the "+short()+", and a feeling of "+str+
      " sweeps over you.\n");
    say(QCTNAME(TP)+" grasps the hilt of the "+short()+".\n");
    wielder = TP;

    /* Kitiara needs a special shadow (can't remask wield) */
    if (TP->query_npc())
	(gShadow = clone_object(KIT_SHADOW))->shadow_me(TP);
    else /* Give wielder the normal shadow */
	(gShadow = clone_object(SHADOW))->shadow_me(TP);
    TP->set_sword(TO);
    return 1;
}


/* Function name: get_prefix
 * Description  : Get one of the random prefixes to the combat
 *                messages.
 * Arguments    : object me = wielder.
 *                object enemy = enemy wielder is attacking.
 * Returns      : Array of strings for the wielder, enemy, and 
 *                watchers of the battle.
 */
string *get_prefix(object me, object enemy)
{
    string *tmp;

    switch(random(12))
    {
    case 0..2:
	tmp = ({ "You ", me->query_The_name(enemy)+" ", QCTNAME(me)+
	  " " });
	break;
    case 3..5:
	tmp = ({ "With tremendous speed, you ",
	  "With tremendous speed, "+me->query_the_name(enemy)+" ",
	  "With tremendous speed, "+QTNAME(me)+" " });
	break;
    case 6..8:
	tmp = ({ "You move with unbelievable quickness, and ",
	  me->query_The_name(enemy)+" moves with unbelievable "+
	  "quickness, and ", QCTNAME(me)+" moves with unbelievable "+
	  "quickness, and "});
	break;
    default:
	tmp = ({ "Acting with swiftness not your own, you ",
	  "Acting with swiftness not "+POSSESSIVE(me)+" own, "+
	  me->query_the_name(enemy)+" ", "Acting with swiftness "+
	  "not "+POSSESSIVE(me)+" own, "+QTNAME(me)+" " });
    }

    return tmp;
}


/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. If the weapon
 *                chooses not to handle combat messages then a default
 *                message is generated.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over
 */
public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object* weapons = enemy->query_weapon(-1);
    object weapon;

    object me = query_wielded();
    object* all_enemies;
    object* present_enemies;
    object big_enemy;

    int i;
    int magic = 0;
    int fury = query_fury();
    int* stat_enemies;
    int big_stat;

    string tmp;
    string* pre;
    string* suf;
    string* wep;

    if (sizeof(weapons))
    {
	for (i = 0; i < sizeof(weapons); i++)
	{
	    if (!weapons[i]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
	    {
		weapon = weapons[i];
		magic = 1;
	    }
	    else
	    {
		weapon = weapons[0];
	    }
	}
    }

    if (fury >= 8)
    {
	present_enemies = ({ });
	stat_enemies = ({ });
	all_enemies = me->query_enemy(-1);

	for (i = 0; i < sizeof(all_enemies); i++)
	{
	    if (all_enemies[i] && me && E(all_enemies[i]) == E(me))
		present_enemies += ({ all_enemies[i] });
	}

	for (i = 0; i < sizeof(present_enemies); i++)
	{
	    stat_enemies += ({ present_enemies[i]->query_average_stat() });
	}

	big_stat = applyv(max, stat_enemies);

	for (i = 0; i < sizeof(stat_enemies); i++)
	{
	    if (stat_enemies[i] == big_stat)
		big_enemy = present_enemies[i];
	}

	if (big_enemy != me->query_attack() && F_DARE_ATTACK(me, big_enemy)
	  && !random(10))
	{
	    me->catch_msg("You realize that nothing will be accomplished "+
	      "by you slaying this inconsequential creature, and you "+
	      "turn your attention to a more formidable opponent in "+
	      QTNAME(big_enemy)+".\n");
	    big_enemy->catch_msg(QCTNAME(me)+" attacks you!\n");
	    tell_room(E(me), QCTNAME(me)+" attacks "+QTNAME(big_enemy)+".\n",
	      ({ me, big_enemy }));
	    me->attack_object(big_enemy);
	}
    }

    /*
     * Perform drain attack special, wielder absorbs half the damage done
     * on the hit, unless it is a killing blow, then he absorbs all damage
     */
    if (fury >= ATTACK_ON_FURY && dam > 0)
    {
	dam = dam / 2 + random(dam);
	enemy->heal_hp(-dam);

	if (me->query_alignment() > 500)
	    tmp = "vanquish evil from the world";
	else if (me->query_alignment() < -500)
	    tmp = "bring the world under your control";
	else
	    tmp = "attain fame and fortune";

	if (enemy->query_hp() <= 0)
	{
	    me->catch_msg("As you strike the killing blow, the emerald of your "+
	      short()+" pulses, and you feel a surge of power flow through "+
	      "your body as the sword aids you in your quest to "+tmp+".\n");
	    enemy->catch_msg("The world around you slows, and you feel a strong "+
	      "force gripping your soul as your life drains away. The feel "+
	      "of cold steel between your ribs fades, and you see no more.\n");
	    tell_room(E(me), "The "+short()+" held by "+QTNAME(me)+" flashes "+
	      "brightly.\n", ({ enemy, me }));
	    me->tell_watcher(QCTNAME(me)+" drives the blade of "+POSSESSIVE(me)+
	      " "+short()+" between the ribs of "+QTNAME(enemy)+", mortally "+
	      "wounding "+OBJECTIVE(enemy)+".\n", enemy);

	    me->heal_hp(dam);
	    if (me->query_wiz_level())
		me->catch_msg("DEBUG:DRAINED - "+dam+" from "+enemy->query_name()+
		  ", ABSORBED: "+dam+"\n");
	    enemy->do_die(me);
	    set_fury(0, 0);
	    return 1;
	}

	me->catch_msg("You feel stronger as the emerald on the "+short()+
	  " flashes brightly, aiding you in your quest to "+tmp+".\n");
	enemy->catch_msg("You feel weakened as the emerald on "+QTNAME(me)+
	  "'s "+short()+" flashes brightly.\n");
	tell_room(E(me), "The "+short()+" held by "+QTNAME(me)+" flashes "+
	  "brightly.\n", ({ enemy, me }));
	me->heal_hp(dam / 2);

	if (me->query_wiz_level())
	    me->catch_msg("DEBUG:DRAINED - "+dam+" from "+enemy->query_name()+
	      ", ABSORBED: "+dam/2+"\n");

	set_fury(0, 0);
    }

    /* Raise the fury level of the sabre */
    if (fury < MAX_FURY && (magic && !random(RAISE_FURY_CHANCE / 2)) ||
      (!magic && !random(RAISE_FURY_CHANCE)))
    {
	set_fury(fury + random(3) + 1);
    }

    /* Send a sentient message to wielder */
    if (weapon && 
	((magic && !random(TELL_TIME / 2)) || 
         (!magic && !random(TELL_TIME))))
    {
	string *wep = ({ "You look with indifference at "+QTNAME(enemy)+"'s "+
	  weapon->short()+", satisfied with your superior weapon.",

	  "The "+weapon->short()+" of "+QTNAME(enemy)+" seems meager and "+
	  "ineffective to you, especially compared to your "+short()+".",

	  "A snickering thought echoes in your mind as you think how unfair "+
	  "a battle with "+QTNAME(enemy)+" is, considering your "+short()+
	  " compared to "+POSSESSIVE(enemy)+" "+weapon->short()+".",

	  "A feeling of confidence washes over you, as you know that with "+
	  "this "+short()+" you cannot be defeated.",

	  "Looking at the paltry "+weapon->short()+" of "+QTNAME(enemy)+
	  " you know that you have nothing to fear.",

	  "Your "+short()+" feels marvellous in your hand, certainly superior "+
	  "to the "+weapon->short()+" of your enemy, "+QTNAME(enemy)+".",

	  "The "+short()+" flickers slightly, and you feel energy surge "+
	  "through you, strengthening you even further.",

	  "A cool voice soothes you, saying: 'Trust me, no harm will befall "+
	  "you with me at your side.'",

	  "A confident voice reassures you with: 'Look at "+QTNAME(enemy)+"'s "+
	  weapon->short()+", it does not do for "+OBJECTIVE(enemy)+" what I do "+
	  "for you.'",

	  "An arrogant thought impresses on your mind: 'Only a fool would "+
	  "choose a "+weapon->short()+" over me.'",

	  "A voice tinged with jealousy asks: 'You would never trade me "+
	  "for a primitive "+weapon->short()+", would you?...'",

	  "A voice of rage echoes in your head: 'I am far more powerful "+
	  "than any "+weapon->short()+", prove it to "+QTNAME(enemy)+", "+
	  "and I will grant you power beyond your wildest imagination.\n",
	  "Dripping with sarcasm, a voice chides: 'What a magnificent "+
	  weapon->short()+", aren't you jealous?...'",
	  "A casual voice soothes you: 'Surely you have nothing to fear "+
	  "from that pathetic "+weapon->short()+" with me on your side.'",
	  "A voice full of nonchalance jokes: 'You had better polish me "+
	  "after this fight, to clean the broken shards of that "+
	  weapon->short()+" off my flawless surface.'" });

	me->catch_msg("\n"+wep[random(sizeof(wep))]+"\n\n");
    }

    pre = get_prefix(me, enemy);
    i = 0; /* If this is set, check for gagmisses */

    switch(phurt)
    {
    case -1:
	suf = ({ "You aim for "+QTNAME(enemy)+" with your "+short()+
	  ", but miss.", QCTNAME(me)+" aims for you with "+POSSESSIVE(me)+
	  " "+short()+" but misses.", QCTNAME(me)+" aims for "+QTNAME(enemy)+
	  " with "+POSSESSIVE(me)+" "+short()+", but misses." });
	i = 1;
	break;
    case 0:
	suf = ({ pre[0]+"swing at "+QTNAME(enemy)+" with your "+short()+
	  ", narrowly missing "+POSSESSIVE(enemy)+" "+hdesc+".",
	  pre[1]+"swings at you with "+POSSESSIVE(me)+" "+short()+
	  ", narrowly missing your "+hdesc+".", pre[2]+"swings "+
	  "at "+QTNAME(enemy)+" with "+POSSESSIVE(me)+" "+short()+
	  ", narrowly missing "+QTNAME(enemy)+"'s "+hdesc+"." });
	i = 1;
	break;
    case 1..4:
	suf = ({ pre[0]+"scratch "+QTNAME(enemy)+"'s "+hdesc+" with "+
	  "the tip of your "+short()+".", pre[1]+"scractches your "+
	  hdesc+" with the tip of "+POSSESSIVE(me)+" "+short()+".",
	  pre[2]+"scratches "+QTNAME(enemy)+"'s "+hdesc+" with the "+
	  "tip of "+POSSESSIVE(me)+" "+short()+"." });
	break;
    case 5..9:
	suf = ({ pre[0]+"leave a shallow cut on the "+hdesc+" of "+
	  QTNAME(enemy)+" with your "+short()+".", pre[1]+"leaves a "+
	  "shallow cut on your "+hdesc+" with "+POSSESSIVE(me)+" "+
	  short()+".", pre[2]+"leaves a shallow cut on the "+hdesc+
	  " of "+QTNAME(enemy)+" with "+POSSESSIVE(me)+" "+short()+"." });
	break;
    case 10..19:
	suf = ({ pre[0]+"graze "+QTNAME(enemy)+"'s "+hdesc+" with the "+
	  "blade of your "+short()+".", pre[1]+"grazes your "+hdesc+
	  " with the blade of "+POSSESSIVE(me)+" "+short()+".", pre[2]+
	  "grazes "+QTNAME(enemy)+"'s "+hdesc+" with "+POSSESSIVE(me)+
	  " "+short()+"." });
	break;
    case 20..29:
	suf = ({pre[0]+"slash twice with your "+short()+", slicing into "+
	  QTNAME(enemy)+"'s "+hdesc+" with each swing.", pre[1]+"slashes "+
	  "twice with "+POSSESSIVE(me)+" "+short()+", slicing into your "+
	  hdesc+" both times.", pre[2]+"slashes twice with "+POSSESSIVE(me)+
	  " "+short()+", slicing into "+QTNAME(enemy)+"'s "+hdesc+ " with "+
	  "each swing." });
	break;
    case 30..45:
	suf = ({ pre[0]+"reverse your grip on the "+short()+", slicing "+
	  "into the "+hdesc+" of "+QTNAME(enemy)+" as you swing it in "+
	  "a deadly arc in front of you.", pre[1]+"reverses "+POSSESSIVE(me)+
	  " grip on the "+short()+", slicing through the flesh of your "+
	  hdesc+" as "+PRONOUN(me)+" swings it in a deadly arc in front "+
	  "of "+OBJECTIVE(me)+".", pre[2]+"reverses "+POSSESSIVE(me)+
	  " grip on the "+short()+", slicing through the flesh of "+
	  QTNAME(enemy)+"'s "+hdesc+" as "+PRONOUN(me)+" swings it in "+
	  "a deadly arc in front of "+OBJECTIVE(me)+"." });
	break;
    case 46..59:
	suf = ({ pre[0]+"seriously wound the "+hdesc+" of "+QTNAME(enemy)+
	  " with a precise slash of your "+short()+".", pre[1]+
	  "seriously wounds your "+hdesc+" with a precise slash of "+
	  POSSESSIVE(me)+" "+short()+".", pre[2]+"seriously wounds the "+
	  hdesc+" of "+QTNAME(enemy)+" with a precise slash of "+
	  POSSESSIVE(me)+" "+short()+"." });
	break;
    case 60..79:
	suf = ({ "You lash out at "+QTNAME(enemy)+" with your "+short()+
	  ", then reverse your grip on the blade and slash into "+
	  POSSESSIVE(enemy)+" "+hdesc+" again, completing the double "+
	  "slash with lightning speed.", QCTNAME(me)+" lashes out with "+
	  POSSESSIVE(me)+" "+short()+", then reverses "+POSSESSIVE(me)+
	  " grip on the blade and slashes into your "+hdesc+" again, "+
	  "completing the double slash with lightning speed.", QCTNAME(me)+
	  " lashes out at "+QTNAME(enemy)+" with "+POSSESSIVE(me)+" "+
	  short()+", then reverses "+POSSESSIVE(me)+" grip on the blade "+
	  "and slashes into "+QTNAME(enemy)+"'s "+hdesc+" again, "+
	  "completing the double slash with lightning speed." });
	break;
    case 80..99:
	suf = ({ "Crouching down, you reverse your grip on the "+short()+
	  " and leap upwards and toward "+QTNAME(enemy)+", tearing "+
	  "through the flesh of "+POSSESSIVE(enemy)+" "+hdesc+".",
	  "Crouching down, "+QTNAME(me)+" reverses the grip on the "+
	  short()+" and leaps upwards and toward you, tearing through "+
	  "the flesh of your "+hdesc+".", "Crouching down, "+QTNAME(me)+
	  " reverses the grip on the "+short()+" and leaps upwards "+
	  "and toward "+QTNAME(enemy)+", tearing through the flesh of "+
	  POSSESSIVE(enemy)+" "+hdesc+"." });
	break;
    default:
	switch(random(3))
	{
	case 2:
	    suf = ({ "You feign an attack to "+QTNAME(enemy)+"'s "+
	      "legs, and then drive the blade of your "+short()+
	      " into "+POSSESSIVE(enemy)+" chest as the feint "+
	      "leaves an opening in "+POSSESSIVE(enemy)+" defences.",
	      QCTNAME(me)+" swings low with "+POSSESSIVE(me)+" "+
	      short()+", and too late you realize your mistake. As "+
	      "you fall for the feigned attack, you feel cold steel "+
	      "slide effortlessly between your exposed ribs.",
	      QCTNAME(me)+" swings low with "+POSSESSIVE(me)+" "+
	      short()+", then drives the blade of "+POSSESSIVE(me)+
	      " "+short()+" into "+QTNAME(enemy)+"'s chest as "+
	      PRONOUN(enemy)+" falls for the feigned attack." });
	    break;
	case 1:
	    suf = ({ "Reversing your grip on the "+short()+" you "+
	      "leap forward, past "+QTNAME(enemy)+", swinging out "+
	      "to your side as you pass "+OBJECTIVE(enemy)+". Turning, "+
	      "you see "+OBJECTIVE(enemy)+" slump to the ground, "+
	      "bleeding heavily from the gaping wound.", "Reversing "+
	      POSSESSIVE(me)+" grip on the "+short()+", "+QTNAME(me)+
	      " leaps forward, past you, swinging out to "+POSSESSIVE(me)+
	      " side as "+PRONOUN(me)+" does. Looking down, you see "+
	      "blood flowing freely from the gaping wound, and feel "+
	      "your legs buckle.", "Reversing "+POSSESSIVE(me)+" grip "+
	      "on the "+short()+", "+QTNAME(me)+" leaps forward, past "+
	      QTNAME(enemy)+", swinging out to "+POSSESSIVE(me)+" side "+
	      "as "+PRONOUN(me)+" passes "+OBJECTIVE(enemy)+". "+
	      QCTNAME(me)+" turns slowly to face "+QTNAME(enemy)+", "+
	      "who slumps to the ground, bleeding heavily from the "+
	      "gaping wound." });
	    break;
	default:
	    suf = ({ "Your movements become blurred as your "+short()+
	      " crosses back and forth before you, slicing wound after "+
	      "wound into "+QTNAME(enemy)+"'s now shattered and broken "+
	      "body.", QCTNAME(me)+"'s movements become blurred as "+
	      POSSESSIVE(me)+" "+short()+" crosses back and forth "+
	      "before "+OBJECTIVE(me)+", slicing wound after wound into "+
	      "your now shattered body.", QCTNAME(me)+"'s movements "+
	      "become blurred as "+POSSESSIVE(me)+" "+short()+" crosses "+
	      "back and forth before "+OBJECTIVE(me)+", slicing wound "+
	      "after wound into "+QTNAME(enemy)+"'s now shattered and "+
	      "broken body." });
	}

    }
    if (!i || (i && !me->query_option(OPT_GAG_MISSES)))
	me->catch_msg(suf[0]+"\n");
    if (!i || (i && !enemy->query_option(OPT_GAG_MISSES)))
	enemy->catch_msg(suf[1]+"\n");
    if (i)
	me->tell_watcher_miss(suf[2]+"\n", enemy);
    else
	me->tell_watcher(suf[2]+"\n", enemy);
    return 1;

}
