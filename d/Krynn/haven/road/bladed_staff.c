/* Created by ?
 *
 * Revision history:
 * Aridor, 97/10/16:
 *    Added gagmisses support.
 * Cotillion, 02-07-27:
 *    Fixed resistance check, and attack delay addition method. 
 * Arman, 20-10-09:
 *    Included funcs for new spell system.
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

int attack = 0;

public void
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());   
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}

public void
create_weapon()
{
    set_name("staff");
    set_pname(({"staves","weapons"}));
    add_name("polearm");
    add_adj("bladed");
    add_adj("silver");
    set_short("bladed silver staff");
    set_pshort("bladed silver staves");
    set_long("This is a long slender staff made of silver. Two curved "+
      "blades adorn the ends of the staff. It is wonderfully balanced, " +
      "and very light. The shaft is decorated with ornate runes "+
      "towards both ends, but the middle part of the shaft is perfectly "+
      "smooth and polished to a gleaming shine. The blades at the ends "+
      "curve like miniature scimitar blades, facing opposite directions, "+
      "making the weapon very dangerous to wield, not to mention the "+
      "dangers of fighting an opponent wielding this staff.\n");

    set_default_weapon(40, 40, W_POLEARM, W_SLASH, W_BOTH);
    set_magic_spellpower(40);

    add_item(({"blade", "blades"}),
	"The two gleaming blades curve in opposite "+
	"directions. They are razor sharp, and never seem to lose their " +
	"edge. They cause a soft whining noise when spinning the staff.\n");
    add_item(({"rune", "runes"}), "@@read_runes");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This is a magical staff, enchanted by "+
      "the Goddess of Neutral Magic, Lunitari. When wielded by members "+
      "of the Wizards of High Sorcery guild, Lunitari will bestow her "+
      "blessings upon her followers if they are somewhere on Krynn.\n");
    add_prop(MAGIC_AM_ID_INFO,
      ({ "This staff is magical.\n", 5,
	"A small amount of spellcraft is required to wield it.\n", 10,
        "The staff provides the holder with some enhancement " +
        "to their magical spellpower, dependent on their spellcraft " +
        "skill.\n", 20,
	"The staff is enchanted by the Crimson Goddess of magic, "+
	"Lunitari.\n", 25, "The staff enhances greatly the power "+
        "of the wielder's spells.\n", 35,
	"Lunitari will bestow additional blessings on its wielder "+
	"only if they are a follower of the Moons of Krynn.\n", 50 }));
    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 40) + 2500);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2000);

    set_wf(TO);
    set_pm(({ -3, 0, 3}));
    seteuid(getuid(TO));
}

string
read_runes()
{
    if (TP->query_skill(SS_LANGUAGE) < 40)
	return "You cannot decipher the runes. They appear to "+
	"be magical, and elude your understanding.\n";

    if (TP->query_guild_name_occ() != "Wizards of High Sorcery")
	return "You try to understand the runes but they elude you. "+
	"You get the vague image of a beautiful crimson-haired "+
	"woman as you read, but she fades away.\n";

    return "The runes read: I bestow my blessings only to those "+
    "who serve the eyes of the night.\n";
}

void
wield_message(object wielder)
{
    if (TO->query_wielded() != wielder)
	return;
    
    set_this_player(wielder);
    
    if (TO->query_wielded()->query_guild_name_occ() ==
	"Wizards of High Sorcery")
	TO->query_wielded()->command("$trace staff");

    if (wielder->query_skill(SS_SPELLCRAFT) > 80)
    {
	write("You feel your spells will be more powerful while " +
            "wielding this staff.\n");
    }
}

mixed
wield(object what)
{

    if (TP->query_skill(SS_SPELLCRAFT) < 20)
    {
	write("You entertain thoughts of wielding this deadly weapon, but "+
	  "quickly change your mind, feeling your skill with it to be "+ 
	  "inadequate.\n");

	return "You prudently decide against using the bladed silver "+
	"staff.\n";
    }

    write("You grip the slender shaft of the "+short()+", "+
      "marvelling at its amazing balance.\n");
    say(QCTNAME(TP)+" grips the slender shaft of the "+short()+".\n");
    wielder = TP;

    int spellpen = min(50, TP->query_skill(SS_SPELLCRAFT) / 2);

    set_magic_spellpower(spellpen);
    TP->update_weapon(TO);

    set_alarm(5.0, 0.0, &wield_message(TP));
    return 1;
}

void
init()
{
    /*
     * add_action("twirl", "twirl");
     * add_action("spin", "spin");
     */
    add_action("trace", "trace");

    ::init();
}

int
twirl(string str)
{
    object *tar;

    NF("What?\n");
    if (TO->query_wielded() != TP)
	return 0;

    NF("Twirl what?\n");
    if (!str)
	return 0;

    if (str == "staff" || str == "bladed staff" || str == "silver staff")
    {
	write("You twirl the staff around your head, then bring "+
	  "one blade around, cutting a wide path through the air.\n");
	say("Twirling the staff around "+POSSESSIVE(TP)+" head, "+
	  QTNAME(TP)+" brings one blade around, " +
	  "cutting a wide path through the air.\n");
	return 1;
    }

    parse_command(str, E(TP), "'staff' [at] [the] %l", tar);

    NF("You cannot twirl the staff at more than one person at a time.\n");
    if (sizeof(tar) > 2)
	return 0;

    NF("Twirl the staff at whom?\n");
    if (!sizeof(tar))
	return 0;

    tar[0] = tar[1];

    write("You twirl the staff around your head, then bring "+
      "one blade around, cutting a wide path through the air "+
      "directly in front of "+tar[0]->query_the_name(TP)+".\n");
    say("Twirling the staff around "+POSSESSIVE(TP)+" head, "+
      QTNAME(TP)+" brings one blade around, cutting a wide "+
      "path through the air directly in front of "+QTNAME(tar[0])+
      ".\n", ({ TP, tar[0] }));
    tar[0]->catch_msg("Twirling the staff around "+POSSESSIVE(TP)+
      " head, "+QTNAME(TP)+" brings one blade around, " +
      "cutting a wide path through the air directly in " +
      "front of you!\n");
    return 1;
}

int
spin(string str)
{
    object *tar;

    NF("What?\n");
    if (TO->query_wielded() != TP)
	return 0;

    NF("Spin what?\n");
    if (!str)
	return 0;

    if (str == "staff" || str == "bladed staff" || str == "silver staff")
    {
	write("You spin the "+short()+" around your body, "+
	  "the blades making a high pitched whine as they "+
	  "cut a path through the air.\n");
	say(QCTNAME(wielder)+" spins the "+short()+" around "+
	  POSSESSIVE(wielder)+" body, the blades making a "+
	  "high pitched whine as they cut a path through the "+
	  "air.\n");
	return 1;
    }

    parse_command(str, E(TP), "'staff' [at] [the] %l", tar);

    NF("You cannot spin the staff at more than one person at a time.\n");
    if (sizeof(tar) > 1)
	return 0;

    NF("Spin the staff at whom?\n");
    if (!sizeof(tar))
	return 0;

    write("You spin the "+short()+" in a deadly arc towards "+
      tar[0]->query_the_name(TP)+", the blades making a high pitched "+
      "whine as they cut a path through the air.\n");
    say(QCTNAME(TP)+" spins the "+short()+" in a deadly "+
      "arc towards "+QTNAME(tar[0])+", the blades making a "+
      "high pitched whine as they cut a path through the "+
      "air.\n", ({ TP, tar[0] }));
    tar[0]->catch_msg(QTNAME(TP)+" spins the staff in a deadly "+
      "arc towards you, the blades making a high pitched whine "+
      "as they cut a path through the air.\n");
    return 1;
}

int
trace(string str)
{
    NF("What?\n");
    if (!query_wielded()->query_wiz_level() &&
      query_wielded()->query_guild_name_occ() != "Wizards of High Sorcery")
	return 0;
    
    NF("Trace what?\n");
    if (!str)
	return 0;

    if (str != "staff" && str != "bladed staff" && str != "silver staff")
	return 0;
    
    write("As you trace your fingers along the shaft of the "+
	short()+", it begins to glow a soft crimson colour and "+
	"tingles of magical energy surge through your body.\n");
    say(QCTNAME(TP)+" is surrounded by a globe of crimson "+
	"light that seems to be coming from the "+short()+" "+
	PRONOUN(TP)+" carries.\n");
    return 1;
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    int a, hp, per;
    string *desc;
    string str;
    object me = query_wielded();
    int b = 0;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    str = file_name(environment(me));
    
    if (str[..7] == "/d/Krynn" || str[..9] == "/d/Ansalon")
	b = 1;

    if (attack == 1 && b)
    {
	attack = 0;

	hp = enemy->query_hp();
	a = random(150) + 100;
	a -= (a * enemy->query_magic_res(MAGIC_I_RES_LIGHT)) / 100;
	per = (!hp ? 100 : per / hp);
	
	if (!random(5))
	{
	    if (enemy->query_magic_res(MAGIC_I_RES_MAGIC))
	    {
		me->catch_msg("You hold the "+short()+" above your head and "+
		    "a shower of glittering crimson pours over "+
		    QTNAME(enemy)+", but "+PRONOUN(enemy)+" blinks "+
		    POSSESSIVE(enemy)+" eyes and seems otherwise " +
		    "unaffected.\n");
		enemy->catch_msg(QCTNAME(me)+" holds the "+short()+" above "+
		    POSSESSIVE(me)+" head, and a shower of " +
		    "glittering crimson pours over you. You " +
		    "blink your eyes.\n");
		me->tell_watcher(QCTNAME(me)+" holds the "+short()+" above "+
		    POSSESSIVE(me)+" head, and a shower of " +
		    "glittering crimson pours over "+QTNAME(enemy)+
		    ", who blinks "+POSSESSIVE(enemy)+
		    " eyes, but seems otherwise unaffected.\n", 
		    enemy);
		return 1;
	    }
	    
	    me->catch_msg("You hold the "+short()+" above your head and "+
		"a shower of glittering crimson pours over "+
		QTNAME(enemy)+", who looks dazed.\n");
	    enemy->catch_msg(QCTNAME(me)+" holds the "+short()+" above "+
		POSSESSIVE(me)+" head, and a shower of " +
		"glittering crimson pours over you. You stop " +
		"and look up in awe.\n");
	    me->tell_watcher(QCTNAME(me)+" holds the "+short()+" above "+
		POSSESSIVE(me)+" head, and a shower of " +
		"glittering crimson pours over "+QTNAME(enemy)+
		", who looks dazed.\n", enemy);
	    enemy->add_attack_delay(25, 1);
	    return 1;
	}
	
	switch(per)
	{
	case 0..15:
	    desc = ({ "a dart of crimson light springs forth, striking "+
	      QTNAME(enemy)+" in the chest.\n",
	      "a dart of crimson light springs forth, striking you in "+
	      "the chest.\n",
	      "a dart of crimson light springs forth, striking "+
	      QTNAME(enemy)+" in the chest.\n" });
	    break;
	case 16..30:
	    desc = ({ "a myriad of crimson darts fly out, burning into "+
	      QTNAME(enemy)+"'s body.\n",
	      "a myriad of crimson darts fly out, burning into your "+
	      "body.\n",
	      "a myriad of crimson darts fly out, burning into "+
	      QTNAME(enemy)+"'s body.\n" });
	    break;
	case 31..45:
	    desc = ({ "a stream of crimson light streaks towards "+
	      QTNAME(enemy)+", burning into "+POSSESSIVE(enemy)+
	      " flesh.\n",
	      "a stream of crimson light streaks towards you, burning "+
	      "into your flesh.\n",
	      "a stream of crimson light streaks towards "+QTNAME(enemy)+
	      ", burning into "+POSSESSIVE(enemy)+" flesh.\n" });
	    break;
	default:
	    desc = ({ "a sphere of blinding crimson light erupts from "+
	      "the staff bursting full upon "+QTNAME(enemy)+" with "+
	      "great intensity.\n",
	      "a sphere of blinding crimson light erupts from the "+
	      "staff, bursting full upon you.\n",
	      "a sphere of blinding crimson light erupts from the "+
	      "staff, bursting full upon "+QTNAME(enemy)+" with great "+
	      "intensity.\n" });
	    break;
	}

	enemy->heal_hp(-a);

	if (enemy->query_hp() > 0)
	{
	    wielder->catch_msg("You suddenly swing your "+short()+" in a wide "+
	      "arc in front of you, and "+desc[0]);
	    enemy->catch_msg(QCTNAME(me)+" suddenly swings "+POSSESSIVE(me)+
	      " "+short()+" in a wide arc towards you, and "+
	      desc[1]);
	    me->tell_watcher(QCTNAME(me)+" suddenly swings "+POSSESSIVE(me)+ " "+
	      short()+" in a wide arc towards "+QTNAME(enemy)+
	      ", and "+desc[2], enemy);
	}


	if (enemy->query_hp() <= 0)
	{
	    enemy->add_prop(LIVE_I_NO_CORPSE, 1);
	    me->catch_msg("The entire area is bathed in sparkling "+
	      "light, varying in intensity from bright red to deep "+
	      "violet, and where "+QTNAME(enemy)+" once stood is a "+
	      "sphere of crimson light which shrinks slowly and " +
	      "then blinks out of existance.\n");
	    me->tell_watcher("The entire area is bathed in sparkling "+
	      "light, varying in intensity from bright red to " +
	      "deep violet, and where "+QTNAME(enemy)+" once " +
	      "stood is a sphere of crimson light which " +
	      "shrinks slowly and then blinks out of " +
	      "existance.\n", enemy);
	    enemy->do_die(me);
	}
	return 1;
    }
    
    if (!random(3) && b && (query_wielded()->query_wiz_level() ||
	query_wielded()->query_guild_name_occ() == "Wizards of High Sorcery")
	&& attack != 1)
    {
	wielder->catch_msg("Your "+short()+" begins to glow a soft "+
	    "crimson colour and tingles of magical energy " +
	  "surge through your body.\n");
	enemy->catch_msg(QCTNAME(wielder)+" is surrounded by a globe of "+
	  "crimson light that seems to be coming from "+
	  POSSESSIVE(wielder)+" "+short()+".\n");
	me->tell_watcher(QCTNAME(wielder)+" is surrounded by a globe of " +
	  "crimson light that seems to be coming from "+
	  POSSESSIVE(wielder)+" "+short()+".\n", enemy);
	attack = 1;
    }

    switch(phurt)
    {
    case -2:
    case -1:
	if (!wielder->query_option(OPT_GAG_MISSES))
	    wielder->catch_msg("You spin the "+short()+" around your body, "+
	      "the blades causing a high pitched whine as they " +
	      "cut a path through the air.\n");
	if (!enemy->query_option(OPT_GAG_MISSES))
	    enemy->catch_msg(QCTNAME(wielder)+" spins the "+short()+" around "+
	      POSSESSIVE(wielder)+" body, the blades making a " +
	      "high pitched whine as they cut a path through the " +
	      "air.\n");
	me->tell_watcher_miss(QCTNAME(wielder)+" spins the "+short()+" around "+
	  POSSESSIVE(wielder)+" body, the blades making a " +
	  "high pitched whine as they cut a path through " +
	  "the air.\n",enemy);
	break;

    case 0:
	if (!wielder->query_option(OPT_GAG_MISSES))
	    wielder->catch_msg("You narrowly miss the "+hdesc+" of "+QTNAME(enemy)+
	      " as you swing your "+short()+" around your " +
	      "body.\n");
	if (!enemy->query_option(OPT_GAG_MISSES))
	    enemy->catch_msg("You narrowly avoid the blades of "+QTNAME(wielder)+
	      "'s "+short()+" as "+PRONOUN(wielder)+" swings it " +
	      "at your "+hdesc+".\n");
	me->tell_watcher_miss(QCTNAME(wielder)+" narrowly misses the "+hdesc+
	  " of "+QTNAME(enemy)+" with "+POSSESSIVE(wielder)+
	  " "+short()+".\n", enemy);
	break;

    case 1..4:
	wielder->catch_msg("You spin your "+short()+" in a deadly arc, "+
	  "tearing a shallow wound into "+QTNAME(enemy)+"'s "+
	  hdesc+".\n");
	enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" lashes out in a "+
	  "deadly arc, slicing into your "+hdesc+".\n");
	me->tell_watcher(QCTNAME(wielder)+"'s "+short()+" lashes out in a "+
	  "deadly arc, tearing a shallow wound into the "+hdesc+
	  " of "+QTNAME(enemy)+".\n",enemy);
	break;

    case 5..9:
	wielder->catch_msg("Twirling your "+short()+" about your body, you "+
	  "suddenly bring it down in a vicious stroke, " +
	  "striking "+QTNAME(enemy)+"'s "+hdesc+
	  " painfully.\n");
	enemy->catch_msg("Twirling "+POSSESSIVE(wielder)+" "+short()+" about "+
	  POSSESSIVE(wielder)+" body, "+QTNAME(wielder)+
	  " suddenly brings it down upon your "+hdesc+
	  " painfully.\n");
	me->tell_watcher("Twirling "+POSSESSIVE(wielder)+" "+short()+" about "+
	  POSSESSIVE(wielder)+ " body, "+QTNAME(wielder)+
	  " suddenly brings it down in a vicious stroke, " +
	  "striking "+QTNAME(enemy)+"'s "+ hdesc+" painfully.\n",
	  enemy);
	break;

    case 10..19:
	wielder->catch_msg("You lash out unexpectedly at "+QTNAME(enemy)+
	  ", driving a blade deep into "+POSSESSIVE(enemy)+" "+
	  hdesc+".\n");
	enemy->catch_msg(QCTNAME(wielder)+" lashes out unexpectedly at you "+
	  "with "+POSSESSIVE(wielder)+" "+short()+", driving a " +
	  "blade deep into your "+hdesc+".\n");
	me->tell_watcher(QCTNAME(wielder)+" lashes out unexpectedly at "+
	  QTNAME(enemy)+" with "+POSSESSIVE(wielder)+" "+short()+
	  ", driving a blade deep into "+QTNAME(enemy)+"'s "+
	  hdesc+".\n",enemy);
	break;

    case 20..29:
	wielder->catch_msg("You swing the "+short()+" towards "+QTNAME(enemy)+
	  ", slashing deeply into "+POSSESSIVE(enemy)+" "+hdesc+
	  ".\n");
	enemy->catch_msg(QCTNAME(wielder)+" swings the "+short()+" towards "+
	  "you with deadly accuracy, slashing deeply into your "+
	  hdesc+".\n");
	me->tell_watcher(QCTNAME(wielder)+" swings the "+short()+" towards "+
	  QTNAME(enemy)+" with deadly accuracy, slashing " +
	  "deeply into "+POSSESSIVE(enemy)+" "+hdesc+".\n",enemy);
	break;

    case 30..49:
	wielder->catch_msg(QCTNAME(enemy)+" staggers as you bring the "+
	  short()+" crashing down upon "+POSSESSIVE(enemy)+" "+hdesc+
	  ".\n");
	enemy->catch_msg("You stagger as "+QTNAME(wielder)+" brings the "+
	  short()+" crashing down upon your "+hdesc+".\n");
	me->tell_watcher(QCTNAME(enemy)+" staggers as "+QTNAME(wielder)+
	  " brings the "+short()+" crashing down upon "+
	  POSSESSIVE(enemy)+" "+hdesc+".\n",enemy);
	break;

    case 50..75:
	wielder->catch_msg("With perfect timing, you twirl the "+short()+
	  " around your head, cutting to the bone of "+
	  QTNAME(enemy)+"'s "+ hdesc+" on the downstroke.\n");
	enemy->catch_msg(QCTNAME(wielder)+" twirls the "+short()+" around "+
	  POSSESSIVE(wielder)+" head, cutting all the way to " +
	  "the bone of your "+hdesc+" on the downstroke.\n");
	me->tell_watcher(QCTNAME(wielder)+" twirls the bladed staff around "+
	  POSSESSIVE(wielder)+" head, bringing it down upon "+
	  QTNAME(enemy)+"'s "+hdesc+" with perfect timing, " +
	  "and cutting to the bone.\n",enemy);
	break;

    case 76..99:
	wielder->catch_msg("Spinning your "+short()+" around you, you "+
	  "lunge at "+QTNAME(enemy)+" tearing into "+
	  POSSESSIVE(enemy)+" "+hdesc+" with one blade, then " +
	  "suddenly twirl, bringing the other blade around " +
	  "in a wide arch, nearly slicing clean through "+
	  POSSESSIVE(enemy)+" "+hdesc+".\n");
	enemy->catch_msg(QTNAME(wielder)+" lunged at you, tearing into "+
	  "your "+hdesc+" with one of the blades, then suddenly "+
	  PRONOUN(wielder)+" twirls, bringing the other blade " +
	  "around in a wide arch, and nearly slicing clean " +
	  "through your "+hdesc+".\n");
	me->tell_watcher(QCTNAME(wielder)+" lunges at "+QTNAME(enemy)+" tearing"+
	  " into "+POSSESSIVE(enemy)+" "+hdesc+" with one blade. "+
	  capitalize(PRONOUN(wielder))+" then suddenly twirls, " +
	  "bringing the other blade around in a wide arch, and " +
	  "nearly slicing through "+QTNAME(enemy)+"'s "+
	  hdesc+".\n",enemy);
	break;

    default:
	wielder->catch_msg("You feel victory upon you: Slowly twirling, you "+
	  "spin blade after blade into "+QTNAME(enemy)+"'s " +
	  "shattered body. Your macabre dance of death " +
	  "ends, and with a final spin you slice into "+
	  POSSESSIVE(enemy)+" exposed neck.\n");
	enemy->catch_msg(QCTNAME(wielder)+" begins to slowly twirl, and "+
	  "blade after blade slices into you in this macabre " +
	  "dance of death. With a last spin, the blade tears " +
	  "through your neck, leaving you stunned, as your " +
	  "lifeblood drains from you.\n");
	me->tell_watcher(QCTNAME(wielder)+" begins to slowly twirl, in a "+
	  "horrific but beautiful dance of death, sending " +
	  "blade after blade "+
	  "of the "+short()+" tearing into "+QTNAME(enemy)+
	  "'s body. With a final spin, the blade slashes " +
	  "through "+POSSESSIVE(enemy)+" throat, and "+
	  PRONOUN(enemy)+" stands there stunned, as the "+
	  "remaining blood pours from " + POSSESSIVE(enemy)+
	  " many wounds.\n",enemy);
	break;
    }
    return 1;
}
