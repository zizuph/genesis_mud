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
*/

inherit "/std/weapon";
inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>

int gQuick_extra, gParry_extra, gFury;
object gShadow;

#define SHADOW "/d/Krynn/solamn/splains/obj/kit_sword_shadow"
#define TELL_TIME 30
#define RAISE_FURY_CHANCE 5
#define ATTACK_ON_FURY 10
#define MAX_FURY 10
#define QUICKNESS_EXTRA 33
#define PARRY_EXTRA query_wielded()->query_skill(SS_WEP_SWORD)


int query_fury()
{
    return gFury;
}


void set_fury(int f)
{
    object enemies;

    if (f < 0)
	f = 0;

    if (f > MAX_FURY)
	f = MAX_FURY;

    if (query_wielded()->query_wiz_level())
	query_wielded()->catch_msg("FURY - "+f+"    (Raised: "+(f-gFury)+")\n");
    gFury = f;
}


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


void create_weapon()
{
    set_name("sword");
    add_name("sabre");
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
      "superiority around other magic weapons.\n");
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


/* This adds the parry and quickness bonuses to the wielder */
void wield_message(object ob)
{
    string str;

    if (!query_wielded() || query_wielded() != ob)
	return;

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


/* Removes the parry and quickness bonuses, as well as wielder shadow */
mixed unwield(object what)
{
    TP->change_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - gQuick_extra);
    TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY) -
      gParry_extra);

    /* Fury fades when unwielded */
    if (query_fury() >= 5)
    {
	tell_room(E(TP), "The glow of the "+short()+" dies out.\n");
    }

    set_fury(0);
    write("As you release your grasp on the "+short()+", you "+
      "feel tired, a little clumsy, and incomplete.\n");
    say(QCTNAME(TP)+" releases "+POSSESSIVE(TP)+" grip on the "+
      short()+".\n");

    gShadow->remove_shadow();
    return 0;
}


/* Add wielder shadow to wielder */
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

    if (TP->query_skill(SS_WEP_SWORD) < 80)
	return "As you grasp the hilt of the "+short()+", you "+
	"are overcome with a feeling of despair and worth"+
	"lessness. A fog of depression settles over your "+
	"soul, and with a flash of insight, you release "+
	"the blade. Your mind is instantly more at ease.\n";

    if ((weapons = E(TO)->query_weapon(-1))[sizeof(weapons) - 1] != TO)
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
    (gShadow = clone_object(SHADOW))->shadow_me(TP);
    TP->set_sword(TO);
    return 1;
}


string *get_prefix(object me, object enemy)
{
    string *tmp;

    switch(random(10))
    {
    case 0..3:
	tmp = ({ "You ", me->query_The_name(enemy)+" ", QCTNAME(me)+" " });
	break;
    case 4..6:
	tmp = ({ "With amazing speed, you ",
	  "With amazing speed, "+me->query_the_name(enemy)+" ",
	  "With amazing speed, "+QTNAME(me)+" " });
	break;
    case 7..9:
	tmp = ({ "You move with unbelievable quickness, and ",
	  me->query_The_name(enemy)+" moves with unbelievable "+
	  "quickness, and ",
	  QCTNAME(me)+" moves with unbelievable quickness, and "});
	break;
    }

    return tmp;

}


public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object *weapons = enemy->query_weapon(-1), weapon;
    object me = query_wielded(), *all_enemies, *present_enemies, big_enemy;
    int i, magic = 0, fury = query_fury(), *stat_enemies, big_stat;
    string tmp, *pre, *suf;
    string *wep;

    if (sizeof(weapons))
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

    if (fury >= 8)
    {
	present_enemies = ({ });
	stat_enemies = ({ });
	all_enemies = me->query_enemy(-1);

	for (i = 0; i < sizeof(all_enemies); i++)
	{
	    if (E(all_enemies[i]) == E(me))
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

	if (big_enemy != me->query_attack() && F_DARE_ATTACK(me, big_enemy) &&
	  (!random(10)))
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

    /* Perform drain attack special, wielder absorbs half the damage done
    * on the hit, unless it is a killing blow, then he absorbs all damage
    */
    if (fury >= ATTACK_ON_FURY && dam > 0)
    {
	dam = dam * 2;
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
	    me->tell_watcher(QCTNAME(me)+" drives the blade of "+POSSESSIVE(me)+
	      " "+short()+" between the ribs of "+QTNAME(enemy)+", mortally "+
	      "wounding "+OBJECTIVE(enemy)+".\n", ({ enemy }) );

	    me->heal_hp(dam);
	    if (me->query_wiz_level())
		me->catch_msg("/* DRAINED: "+dam+" from "+enemy->query_name()+", "+
		  "ABSORBED: "+dam+". */ \n");
	    enemy->do_die(me);
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
	    me->catch_msg("/* DRAINED: "+dam+" from "+enemy->query_name()+", "+
	      "ABSORBED: "+dam/2+". */ \n");

	set_fury(0);
    }

    /* Raise the fury level of the sabre */
    if (fury < MAX_FURY && (magic && !random(RAISE_FURY_CHANCE / 2)) ||
      (!magic && !random(RAISE_FURY_CHANCE)))
    {
	i = random(3) + 1;
	if (fury < 5 && fury + i > 5)
	{
	    tell_room(E(me), QCTNAME(me)+"'s "+short()+" begins to glow a "+
	      "pale green colour.\n", ({ me }));
	    me->catch_msg("Your "+short()+" begins to glow a pale green colour.\n");
	}
	else if (fury > 5)
	{
	    me->catch_msg("The glow around your "+short()+" grows more intense.\n");
	    tell_room(E(me), "The glow around "+QTNAME(me)+"'s "+short()+
	      " grows more intense.\n", ({ me }));
	}
	set_fury(fury + i);
    }

    /* Send a sentient message to wielder */
    if ((magic && !random(TELL_TIME / 2)) || (!magic && !random(TELL_TIME)))
    {
	string *wep = ({ "You look with indifference at "+QTNAME(enemy)+"'s "+
	  weapon->short()+", satisfied with your superior weapon.",
	  "The "+weapon->short()+" of "+QTNAME(enemy)+" seems meager and "+
	  "ineffective to you, especially compared to your "+short()+".",
	  "A snickering thought echoes in your mind as you think how unfair "+
	  "a battle with "+QTNAME(enemy)+" is, considering your "+short()+
	  "compared to "+POSSESSIVE(enemy)+" "+weapon->short()+".",
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

    switch(phurt)
    {
    case -1:
	suf = ({ pre[0]+"aim for "+QTNAME(enemy)+" with your "+short()+
	  ", but miss.", pre[1]+"aims for you with "+POSSESSIVE(me)+
	  " but misses.", pre[2]+"aims for "+QTNAME(enemy)+
	  " with "+POSSESSIVE(me)+" "+short()+", but misses." });
	break;
    case 0:
	suf = ({ pre[0]+"swing at "+QTNAME(enemy)+" with your "+short()+
	  ", narrowly missing "+POSSESSIVE(enemy)+" "+hdesc+".",
	  pre[1]+"swings at you with "+POSSESSIVE(me)+" "+short()+
	  ", narrowly missing your "+hdesc+".", pre[2]+"swings "+
	  "at "+QTNAME(enemy)+" with "+POSSESSIVE(me)+" "+short()+
	  ", narrowly missing "+QTNAME(enemy)+"'s "+hdesc+"." });
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
	suf = ({ pre[0]+"seriously wound the "+hdesc+" of "+QTNAME(enemy)+
	  "with a precise strike of your "+short()+".", pre[1]+
	  "seriously wounds your "+hdesc+" with a precise strike of "+
	  POSSESSIVE(me)+" "+short()+".", pre[2]+"seriously wounds the "+
	  hdesc+" of "+QTNAME(enemy)+" with a precise strike of "+
	  POSSESSIVE(me)+" "+short()+"." });
	break;
    case 46..60:
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
    case 61..80:
	suf = ({ "Crouching down, you reverse your grip on the "+short()+
	  "and leap upwards and toward "+QTNAME(enemy)+", tearing "+
	  "through the flesh of "+POSSESSIVE(enemy)+"'s "+hdesc+".",
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
	      " into "+POSSESSIVE(enemy)+" chest as the feign "+
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

    me->catch_msg(suf[0]+"\n");
    enemy->catch_msg(suf[1]+"\n");
    me->tell_watcher(suf[2]+"\n", ({ enemy }));
    return 1;
}

