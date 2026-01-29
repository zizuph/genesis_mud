#pragma strict_types
/* file name:     /d/Avenir/common/holm/t_camp/amulet.c
 *  creator(s):    Rangorn, May 97
 *  revisions:     Lilith, April 98
 *                 Lilith, Jul 2003: runtime fix
 *                 Lucius, Aug 2006: runtime fix, cleanups
 *                 Lucius, Jan 2009: runtime fix for FUMBLE prop.
 *                 Petros, Sep 2013: remove abuses possible by removing
 *                                     amulet immediately after invoking or
 *                                     touching it.
 *                 Zizuph, Jun 2021: Limit insanity to only grow on players.
 *                                     When Nemur has been alive a long time,
 *                                     he fails to drop the amulet.
 *                 Lilith, Apr 2022: Players are getting the wear/remove
 *                    messages even when they aren't around the object.
 *                    Added set_this_player(interactive(environment(TO)))
 *                    and a check for interactive calling the wear func.
 *
 *  purpose:       To terrify and harass the wearer, driving him insane.
 *
 *            The player wearing this amulet experiences hallucinations
 *            both pleasant and unpleasant, and is forced to do things
 *            he or she otherwise might not. Eventually s/he is driven
 *            insane, the price for coveting an object of extreme power.
 *            With the insanity comes chance of harm and even death, the
 *            urge to do inexplicable things, the dropping of weapons, etc.
 *
 *            Wearing the amulet automatically increases spellcraft (15).
 *            To wear the amulet you must have >48 spellcraft and >80 wis.
 *
 *            Using the proper commands will grant the wearer the ability
 *            to see in darkness (5), as well as increase awareness (20)
 *            for a limited time. Upt to 100 Mana can also be replentished,
 *            but at a cost of hitpoints (5 * mana) and (100) fatigue.
 *
 *            Repeated uses will make the player will go insane.
 *            (In character that is :) ) The amulet is autoloading and
 *            the insanity_counter carries over.
 *  bug(s):
 *  to-do:
 */
inherit "/std/armour";
inherit "/lib/keep";

#include "../holm.h"
#include <ss_types.h>
#include <wa_types.h>

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
    (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
    (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define AMULET    "/d/Avenir/log/misc/amulet"
#define A_I_D     "nemur_ruby_amulet"
#define WEAR_PROP "_wearing_azmanizt"
#define INSANITY_COUNTER_PROP "_azmanizt_insanity_counter"

#define SPELLCRAFT_BOOST      15
#define MANA_BOOST            100
#define SEE_DARK_BOOST        5
#define AWARENESS_BOOST       20

#define CRY	"You are so depressed you fumble your attack."
#define LAF	"You are laughing so hard you fumble your attack."


private static int insanity_counter, id, touch_alarm;
private static int set_para, set_para2, touch_set;
private static int LAST_INVOKE_TIME = 0;

private void die_func(void);
private void no_more(void);
private void insanity_func(void);


private int
check_drop(void)	{ return (insanity_counter >= 12); }


static void
create_armour(void)
{
    if (!IS_CLONE)
	return;

    setuid();
    seteuid(getuid());

    set_name("amulet");
    add_name(({A_I_D, "armour", "azmanizt"}));
    set_adj("ruby");
    set_short("glittering ruby amulet");
    set_long("A large ruby, exquisitely cut with hundreds of tiny facets "+
      "that gather light and sets the interior afire with brilliant red "+
      "flame. The ruby is set in an unusual, glowing alloy of precious "+
      "metals, through which a single thread of webfibre has been looped. "+
      "Lightweight and oddly warm, the amulet seems to tremble and shift "+
      "with a life of its own.\n");

    add_item("ruby", "You have never seen its like before.\n");
    add_item(({"webfibre", "thread"}),
	"It is a single thread of the webfibre, "+
	"famed for its steel-like strength.\n");
    add_item(({"metal", "alloy", "setting"}),
	"The setting for the ruby is made of an indeterminate alloy "+
	"that glows and shifts before your very eyes, setting the "+
	"entire amulet aglitter.\n");

    set_default_armour(10, A_NECK);
    set_af(this_object());

    /* Its difficult to get rid of */
    add_prop(OBJ_M_NO_GIVE,
	"The amulet seems unwilling to part with you.\n");
    add_prop(OBJ_M_NO_DROP, check_drop);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    /* It weighs like a stone around the neck */
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, 500 + random(300));

    add_prop(OBJ_S_WIZINFO,
	"This amulet is a blessing and a curse: It bestows upon the "+
	"wearer the virtue of increased spellcraft (15). Using the "+
	"command 'invoke' will raise mana, but at a cost of hp and "+
	"fatigue. The command 'touch' will grant the ability to see "+
	"in the dark (5) and raise awareness (20) for a limited time. "+
	"The penelty is that the player will lose hold of his sanity, "+
	"doing things beyond his control. It will cause great pain and "+
	"hurt, that, timed wrongly, could be deadly. The only way to be "+
	"rid of it is to return to the wizard from whom it was taken, "+
	"Nemur (/d/Avenir/common/holm/mon/wizard) at /holm/t_camp/w1, "+
	"and ask him for release. If for some reason you need to remove "+
	"this from a mortal, you can call lift_curse() in it.\n");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
	"   Ancient are the flames which burn within!\n", 5,
	"   Pain and Power are the Legacy of Azmanizt.\n", 10,
	"   The reverent touch of fingers upon me brings clarity.\n", 20,
	"   An invocation improves mental health with great pain.\n", 25,
	"   'Ware the Curse of Azmanizt! 'Ware its touch upon your heart!\n", 40,
	"   Seek Nemur's aid in thine release, lest\n", 55,
	"   Madness and death take its toll on thee!\n", 70
    }));
}

public mixed
wear(object to)
{
    int spell, wis;
    object tp;

    if (!interactive(environment(this_object())))
		return;

    set_this_player(environment(this_object()));	
 
    wis = TP->query_stat(SS_WIS);
    spell = TP->query_skill(SS_SPELLCRAFT);

    if (spell < 48 || wis < 80)
    {
        TP->heal_hp(-100);
        say("Flames erupt from the amulet as "+ QTNAME(TP) +" tries to " +
            "wear it around " + TP->query_possessive() + " neck.\n");
        return "Flames erupt from the amulet, burning you badly!\n";
    }
    
    TP->catch_tell("A fire rises from the inner depths of your soul. " +
                   "Its flickering flames consume your heart, demanding to be fed.\n");
    tell_room(environment(TP), "The ruby amulet flickers with "+
              "a faint red color as "+ QTNAME(TP) +" wears it around " +
              TP->query_possessive() + " neck.\n", ({ TP }), TP);
    
    if (!TP->query_prop(WEAR_PROP))
    {
        TP->set_skill_extra(SS_SPELLCRAFT,
                            TP->query_skill_extra(SS_SPELLCRAFT) + SPELLCRAFT_BOOST);
        TP->add_prop(WEAR_PROP, 1);
    }

    // Need to reset the insanity_counter if it's already been previously set.
    insanity_counter = 0;
    mapping insanity_mapping = query_prop(INSANITY_COUNTER_PROP);
    if (mappingp(insanity_mapping))
    {
        insanity_counter = max(insanity_counter, insanity_mapping[TP->query_real_name()]);
    }
    insanity_counter = max(insanity_counter, TP->query_prop(INSANITY_COUNTER_PROP));

    if (!get_alarm(id))
        id = set_alarm(15.0, 300.0, insanity_func);

    return 1;
}

public int
remove(object to)
{
    object owner = query_worn();

    if (!query_interactive(owner))
        return 0;
    
    if (insanity_counter >= 12)
    {
        owner->catch_tell("You struggle to remove the amulet but you " +
                          "cannot lift it from its place over your heart!\n");
        tell_room(environment(owner), QCTNAME(owner) + " tries to remove "+
                  owner->query_possessive() +" ruby amulet but fails.\n",
                  ({ owner }), owner);
        
        return -1;
    }
    
    owner->catch_tell("The flames embracing your heart flicker and die, "+
                      "leaving a cold, bare place over your heart.\n");
    owner->remove_prop(LIVE_S_EXTRA_SHORT);
    
    if (owner->query_prop(WEAR_PROP))
    {
        owner->set_skill_extra(SS_SPELLCRAFT,
                               owner->query_skill_extra(SS_SPELLCRAFT) - SPELLCRAFT_BOOST);
        owner->remove_prop(WEAR_PROP);
    }

    // When this amulet is removed, we want to store the insanity counter
    // for this person. That means that for the life of this amulet during
    // this Armageddon, a person cannot reduce their insanity to 0 just
    // by removing it.
    mapping insanity_mapping = query_prop(INSANITY_COUNTER_PROP);
    if (!mappingp(insanity_mapping))
    {
        insanity_mapping = ([ ]);
    }
    insanity_mapping[owner->query_real_name()] = insanity_counter;
    add_prop(INSANITY_COUNTER_PROP, insanity_mapping);
    // We also store the insanity counter on both the person and the item,
    // so that you can't get multiple copies of the amulet and take
    // advantage of it.
    owner->add_prop(INSANITY_COUNTER_PROP, insanity_counter);

    // Reset the alarm and the insanity counter
    insanity_counter = 0;
    remove_alarm(id);
    id = 0;
    // If the touch_alarm is still active, we end it and call no_more to have the effects be removed
    if (get_alarm(touch_alarm))
    {
        remove_alarm(touch_alarm);
        no_more();
    }
    touch_alarm = 0;
    return 1;
}

public int
invoke_func(string str)
{
    int mana, max_mana, diff, hp;

    // Check if player is wearing this amulet.
    if (!query_worn())
    {
	notify_fail("Invoke what?\n");
	return 0;
    }

    if (str != "amulet" && str != "azmanizt")
    {
	notify_fail("Invoke what?\n");
	return 0;
    }

    if (time() - LAST_INVOKE_TIME < 30)
    {
        query_worn()->catch_tell("You cradle the amulet in your hands and "
                                 + "attempt to invoke its powers. You sense "
                                 + "that it is simply too soon since the last "
                                 + "time you invoked it.\n");
        return 1;
    }
    LAST_INVOKE_TIME = time(); // limit the use of this to every 30 seconds.

    query_worn()->catch_tell("You cradle the amulet in your hands and "+
      "attempt to invoke its powers. The flames engulfing your "+
      "heart burn stronger for a brief moment, searing your soul.\n");

    // Give the player up to 100 mana at a cost of 5*mana hitpoints.
    max_mana = query_worn()->query_max_mana();
    mana = query_worn()->query_mana();
    mana = max_mana - mana;

    if (mana > MANA_BOOST)
        mana = MANA_BOOST;

    query_worn()->add_mana(mana);

    // Drain the player of fatigue and health.
    query_worn()->add_fatigue(-100);
    // Player loses up to 500 hitpoints.
    query_worn()->heal_hp(-(mana * 5));
    hp = query_worn()->query_hp();

    query_worn()->catch_tell("You feel mentally refreshed, but physically "+
      "tired and in great pain.\n");

    if (hp < 0)
    {
        query_worn()->catch_tell("The pain swells to an unbearable level, "+
                                 "and you realize that you have pulled too deeply upon your "+
                                 "physical reserves...\n");
        die_func();
    }

    return (insanity_counter += 6);
}

public int
touch_func(string str)
{
    int check;

    // Check if player is wearing this amulet.
    if (!query_worn())
    {
	notify_fail("Touch what?\n");
	return 0;
    }

    if (str != "amulet" && str != "azmanizt")
    {
	notify_fail("Touch what?\n");
	return 0;
    }

    if (touch_set)
    {
	notify_fail("You grasp the amulet in an attempt to call " +
	    "upon its powers but nothing happens.\n");
	return 0;
    }

    touch_set = 1;
    query_worn()->catch_tell("You touch the amulet with gentle reverence, "+
      "briefly calling upon its powers.\nThe flames engulfing your "+
      "heart burn triumphantly. You feel that your senses have sharpened. "+
      "The world is painfully clear.\n");

    check = query_worn()->query_prop(LIVE_I_SEE_DARK);
    query_worn()->add_prop(LIVE_I_SEE_DARK, check + SEE_DARK_BOOST);

    query_worn()->set_skill_extra(SS_AWARENESS,
	query_worn()->query_skill_extra(SS_AWARENESS) + AWARENESS_BOOST);

    touch_alarm = set_alarm(60.0, 0.0, no_more);
    return (insanity_counter += 4);
}

public int
release_func(string str)
{
    string vis = one_of_list(
	({"blue","white","red","yellow","black","purple","green"}));

    // Check if player is wearing this amulet.
    if(!query_worn())
    {
	notify_fail("Free what?\n");
	return 0;
    }

    if (str != "amulet" && str != "azmanizt")
    {
	notify_fail("Free what?\n");
	return 0;
    }

    if (insanity_counter++ < 12)
    {
	notify_fail("You try to interlock your mind with the amulet but " +
	  "you fail completely.\nA voice hisses in your mind: Weak-minded "+
	  "fool! Seek the wizard Nemur. He will release us both from this "+
	  "bondage...\n");
	return 0;
    }

    query_worn()->catch_tell("The ruby on your amulet flickers with a "+
      vis +" light.\n");
    query_worn()->catch_tell("A voice hisses in your mind: Almost! Yet "+
      "it appears you lack the strengths to free me. Seek out the "+
      "wizard Nemur. He will release us both from this interminable "+
      "bondage...\n");
    say(QCTPNAME(query_worn()) + " amulet flickers with a "+
	vis +" light.\n", query_worn());

    return 1;
}

// This is a function that is called every 5 minute to check the insanity
// level of the player wearing the amulet.
private void
insanity_func(void)
{
    object *team, *team2, enemy;
    mixed check_wield1, check_wield2;
    int amuletrnd, nr, nr2, mem, i, j, k;

    if (!query_worn())
	return;

    amuletrnd = random(5) + insanity_counter;
    i = random(2); j = random(6); k = random(3);

    // Give the person that we are fighting a scary message and
    // and make him/her more panicy.
    enemy = query_worn()->query_attack();
    if (present(enemy, environment(query_worn())))
    {
	if (j == 0)
	{
	    enemy->catch_tell("Your vision fades for a moment and "+
		"darkness comes crashing down on you.\n");
	    enemy->add_panic(-random(50));
	}
	else if (j == 1)
	{
	    enemy->catch_tell("You feel as though your hands have suddenly "+
	      "caught fire as an intense, burning pain sears your palms.\n");
	    enemy->add_panic(-random(60));
	}
	else if (j == 2)
	{
	    enemy->catch_tell("You are overcome by an intense feeling of "+
		"loneliness and despair.\n");
	    enemy->add_panic(-random(70));
	}
    }

    if (set_para)
    {
	string *prop = query_worn()->query_prop(LIVE_AS_ATTACK_FUMBLE);

	if (pointerp(prop))
	    query_worn()->add_prop(LIVE_AS_ATTACK_FUMBLE, prop - ({ LAF }));

	query_worn()->remove_prop(LIVE_S_EXTRA_SHORT);
	query_worn()->catch_tell(
	    "You finally manage to pull yourself together.\n");
	say(QCTNAME(query_worn())+ " finally stops laughing.\n", 
	    query_worn());
	set_para = 0;
	return;
    }

    if (set_para2)
    {
	string *prop = query_worn()->query_prop(LIVE_AS_ATTACK_FUMBLE);

	if (pointerp(prop))
	    query_worn()->add_prop(LIVE_AS_ATTACK_FUMBLE, prop - ({ CRY }));

	query_worn()->remove_prop(LIVE_S_EXTRA_SHORT);
	query_worn()->catch_tell(
	    "You finally manage to pull yourself together.\n");
	say(QCTNAME(query_worn())+ " finally stops sobbing.\n", 
	    query_worn());
	set_para2 = 0;
	return;
    }

    // There is a 33% chance that that this function isn't executed
    // This is just to make sure that a player gets a message at a
    // more random interval.
    if (!random(3))
	return;

    // We will let NPCs avoid the insanity - such as Nemur.
    if (query_worn()->query_npc())
	return;

    insanity_counter++;
    function tellme = query_worn()->catch_tell;

    switch(amuletrnd)
    {
    case 0..7:
	switch(j)
	{
	case 0:
	    tellme("A soft voice echos through your mind: " +
		"Free me and I, Azmanizt, will see to it that "+
		"unimaginable powers will be yours.\n");
	    break;
	case 1:
	    tellme("The flickering flames engulfing your heart "+
		"flare up for a split second, as if to remind you of the "+
		"amulet's presence and its seeming desire to be touched.\n");
	    break;
	case 2:
	    tellme("A seductive voice echos through your mind"+
		"...\n   Why not use my powers to make things easier? "+
		"Touch me! Invoke me! Free me!\n");
	    break;
	case 3:
	    tellme("A soft voice echos through your mind... "+
		"Trust no one.\n");
	    break;
	case 4:
	    tellme("Someone taps you on the shoulder. As you " +
		"turn around you can't see anyone there. Perhaps it "+
		"was just a figment of your active imagination.\n");
	    break;
	case 5:
	    tellme("A soft voice echos through your mind... "+
		"I am your only friend..\n");
	    break;
	}
	break;

    case 8..10:
	check_wield1 = query_worn()->query_weapon(W_RIGHT);
	check_wield2 = query_worn()->query_weapon(W_LEFT);

	if (check_wield1 || check_wield2)
	    query_worn()->command("$drop weapons");

	if (!k)
	{
	    tellme("Your head is flooded with dozens of voices, "+
		"each one screaming in a high pitched tone! You "+
		"put your hands to your ears trying to mute the "+
		"voices.\nSuddenly the voices fades away leaving "+
		"you weary and tired.\n");
	    say(QCTNAME(query_worn()) + " suddenly puts "+
		query_worn()->query_possessive()+" hands to "+
		query_worn()->query_possessive()+" ears.\n", query_worn());

	    query_worn()->add_fatigue(-50);
	}
	else if (k == 1)
	{
	    query_worn()->command("$scream");
	    tellme("A raging fire erupts from your heart, racing "+
		"up to your head! Flames burst from your eyes, blind"+
		"ing you!\nYou desperately beat your face with your "+
		"hands in an attempt to put out the flames. You scream "+
		"with agony as the flames retreat back to the inner "+
		"sanctum of your heart.\nYou run your fingers across "+
		"your face, but you can't find any burn marks.\n");
	    say(QCTNAME(query_worn()) +" suddenly screams and starts "+
		"hitting "+ query_worn()->query_possessive() +" face "+
		"with "+ query_worn()->query_possessive() +" hands.\n", 
		query_worn());
	}
	else
	{
	    tellme("You suddenly remember that you were supposed to do "+
		"something important today...But you are not sure what "+
		"it was. Suddenly it occurs to you that maybe if you "+
		"jump up and down for a while then you might remember!\n");

	    query_worn()->command("$jump");
	    query_worn()->command("$jump");
	    query_worn()->command("$jump");

	    tellme("Hmmm no that didn't help it, probably wasn't "+
		"important anyway.\n");

	    query_worn()->command("$sigh");
	}
	break;

    case 11..15:
	nr = sizeof(team = query_worn()->query_team());
	nr2 = sizeof(team2 = query_worn()->query_team_others());

	mem = random(nr);

	if (nr > 0 && i == 0)
	{
	    query_worn()->command("$glare susp all");
	    tellme("You feel that betrayal is all around you. Are "+
		"these really your friends? Can they really be trusted?\n"+
		"Especially "+ QTNAME(team[mem]) +"! " +
		capitalize(team[mem]->query_pronoun()) +" has always "+
		"been envious of your success. Maybe it would be best "+
		"to get rid of "+ team[mem]->query_objective() +" before "+
		team[mem]->query_pronoun() +" betrays you!\n");
	    team[mem]->catch_tell("You notice that "+ QTNAME(query_worn()) +
		" is looking strangely at you.\n");
	}
	else if (nr > 0 && i == 1)
	{
	    tellme(QCTNAME(team[mem]) + " suddenly starts bleeding "+
		"from "+ team[mem]->query_possessive() +" mouth, eyes "+
		"and nose. Small wounds burst open up on "+
		team[mem]->query_possessive() +" chest and arms!\n"+
		"Ack! You'd better leave before you catch whatever "+
		"disease "+ team[mem]->query_pronoun() +" has!\n");

	    query_worn()->command("$grin hyst");
	    query_worn()->run_away();
	    query_worn()->run_away();
	}

	if (nr2 > 0 && i == 0)
	{
	    tellme("Hmmm why are we going in this direction?\n" +
		"Maybe you are being led into a trap? Yes! Go! "+
		"You'd better leave them now before it is to late!\n");

	    query_worn()->command("$leave");
	    query_worn()->run_away();
	}
	else if (nr2 > 0 && i == 1)
	{
	    tellme("You have a sudden, inexplicable urge "+
		"to be rid of your teammates! You can't stand their " +
		"complaining and whining anymore!\n");

	    query_worn()->command("$shout I hate all of you!");
	    query_worn()->command("$shout All you do is whine!");
	    query_worn()->command("$leave");
	    query_worn()->run_away();
	}

	if (i == 0 && nr == 0 && nr2 == 0)
	{
	    string *prop = query_worn()->query_prop(LIVE_AS_ATTACK_FUMBLE);

	    tellme("Nothing makes any sense...what is the point..."+
		"all this mindless killing and senseless violence...\n"+
		"You sit down on the ground and put your head in your "+
		"hands. You slowly rock back and forth.\n");
	    say(QCTNAME(query_worn()) + " sits down on the ground and "+
		"puts "+ query_worn()->query_possessive() +" head in " +
		query_worn()->query_possessive() +" hands and slowly "+
		"starts rocking back and forth.\n", query_worn());

	    query_worn()->command("$despair");
	    query_worn()->add_prop(LIVE_S_EXTRA_SHORT,
		" is sobbing uncontrollably");

	    if (pointerp(prop))
		prop += ({ CRY });
	    else
		prop  = ({ CRY });

	    query_worn()->add_prop(LIVE_AS_ATTACK_FUMBLE, prop);
	    set_para2 = 1;
	}
	else if (i == 1 && nr == 0 && nr2 == 0)
	{
	    tellme("The flames in your heart suddenly turn cold! "+
		"You break out in a clammy sweat. Maybe the flames will " +
		"leave you...maybe they have gone forever...maybe you "+
		"are not worthy of them...\n");

	    query_worn()->command("$shout Noooo don't leave! "+
		"I will try to do better!");
	    query_worn()->command("$grin fanat");

	    tellme("The flames suddenly turn warm again, " +
		"soothing your pain and removing your sense of loss.\n");
	}
	break;

    case 16..20:
	if (i)
	{
	    string *prop = query_worn()->query_prop(LIVE_AS_ATTACK_FUMBLE);

	    tellme("You suddenly remember something very funny! "+
		"You are not quite sure what it was, but even trying "+
		"to recall it leaves you trembling with suppressed mirth.\n"+
		"You soon fail to contain it and burst into hysterical "+
		"laughter.\n");
	    say(QCTNAME(query_worn()) +" starts to laugh hysterically.\n", 
	        query_worn());

	    query_worn()->add_prop(LIVE_S_EXTRA_SHORT,
		" is laughing hysterically");

	    if (pointerp(prop))
		prop += ({ LAF });
	    else
		prop  = ({ LAF });

	    query_worn()->add_prop(LIVE_AS_ATTACK_FUMBLE, prop);
	    set_para = 1;
	}
	else
	{
	    tellme("For no apparent reason, everything suddenly seems "+
		"overwhelmingly beautiful...Tears well in your eyes as "+
		"the beauty of your environment touches a nostalgic chord "+
		"deep within you. A feeling of all-encompassing love fills "+
		"you.\n");

	    query_worn()->command("$kiss all");
	    query_worn()->command("$say You are so beautiful!");
	    query_worn()->command("$smile tear");
	}
	break;

    default:
	if (i)
	{
	    tellme("You gasp in astonishment as a giant worm suddenly "+
		"crawls out of your left ear!\nTwo smaller worms fall "+
		"out of your nose, landing on the ground before you! "+
		"You try to pull the worm out of your ear but it is "+
		"stuck there!\n");

	    query_worn()->command(
		"$shout The worms!");
	    query_worn()->command(
		"$shout Can't you see them? They fell out of my nose!");
	    query_worn()->command(
		"$shout Kill them now before it is to late!");

	    say(QCTNAME(query_worn())+ " suddenly starts hitting "+
		query_worn()->query_possessive()+ " head with "+ 
		query_worn()->query_possessive()+ " hands.\n", query_worn());

	    set_alarm(5.0, 0.0, die_func);
	}
	else
	{
	    tellme("Suddenly two giant worms crawl up from the ground. "+
		"They slowly slither up and around your body, squeezing "+
		"you tighter and tighter! You fear that soon you wont "+
		"be able to breathe!\n");

	    query_worn()->command("$sob hyst");
	    query_worn()->command("$shout Kill the worms! Kill them now!");

	    set_alarm(5.0, 0.0, die_func);
	}
    }
}

private void
die_func(void)
{
    int hp;

    query_worn()->catch_tell("The flickering flames in your heart "+
                             "erupt with volcanic strength.\nA dark voice laughs mockingly.\n");
    say(QCTNAME(query_worn()) +" suddenly turns into a living torch!\n" +
        "Within just a few seconds large areas of blackened flesh appear "+
        "on "+ QTPNAME(query_worn()) +" chest and arms!\n", query_worn());
    
    query_worn()->heal_hp(-500);
    hp = query_worn()->query_hp();

    if (hp < 0)
    {
        query_worn()->add_prop(LIVE_I_NO_CORPSE);
        query_worn()->heal_hp(-10000);
        query_worn()->do_die();
    }
}

private void
no_more(void)
{
    int check;

    touch_set = 0;
    check = query_worn()->query_prop(LIVE_I_SEE_DARK);
    query_worn()->remove_prop(LIVE_I_SEE_DARK, check - SEE_DARK_BOOST);
    query_worn()->set_skill_extra(SS_AWARENESS,
                                  query_worn()->query_skill_extra(SS_AWARENESS) - AWARENESS_BOOST);
    query_worn()->catch_tell("The world suddelnly shifts and becomes "+
                             "a blur of colors and shapes.\n");
}

public void
lift_curse(void)
{
    if (query_worn()->query_prop(LIVE_S_EXTRA_SHORT))
	query_worn()->remove_prop(LIVE_S_EXTRA_SHORT);

    remove_alarm(id);
    set_alarm(3.5, 0.0, &remove_object());
    if (get_alarm(touch_alarm))
    {
        remove_alarm(touch_alarm);
        no_more();
        touch_alarm = 0;
    }

    query_worn()->catch_tell("The insiduous tendrils of the amulet's "+
	"flames begin to withdraw from your heart.\n");
    insanity_counter = 0;
}

public void
init(void)
{
    ::init();

    add_action(release_func, "release");
    add_action(release_func, "free");
    add_action(touch_func,   "touch");
    add_action(invoke_func,  "invoke");
}

public void
enter_env(object to, object from)
{
    int i;
    object *obs;

    ::enter_env(to, from);

    SCROLLING_LOG(AMULET, "/holm/obj/amulet in "+
	(living(to) ? to->query_cap_name() : to->short()));

    if (!living(to))
	return;

    /* Only ever one at a time in a person's inventory */
    foreach(object ob : all_inventory(to))
    {
	if (ob == this_object())
	    continue;

	if (!ob->id(A_I_D))
	    continue;

	ob->remove_object();
	to->catch_tell("The "+ short() +"s shimmer in your "+
	    "hands, then merge and become one.\n");
    }
}

public int
query_recover(void)
{
    return 0;
}

public void
init_arg(string arg)
{
    sscanf(arg, "#INSANITY#%d", insanity_counter);
    wear_me();
}

public mixed
query_auto_load(void)
{
    /* 25% chance won't auto-load  */
    if (!random(4))
	return 0;

    return MASTER +":#INSANITY#" + insanity_counter;
}
