/*
 *  /d/Sparkle/guilds/new_merc/npc/waiter.c
 *
 *  This is the cooks wife. She is ridiculously grouchy and rules the
 *  Mercenary banquet hall with an iron fist. Pearl is an absolute
 *  beast. I am going to code her to be devastatingly tough in combat.
 *  This makes no sense of course, other than the idea that its fun
 *  to have a bitter old woman running the kitchen who casts fear into
 *  even the stoutest warrior's heart.
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 *
 *  Revision History:
 *    Aug 01, 2019 - Added ability to return the broom to the broom
 *                   closet if careless players have not returned it
 *                   and someone asks her about it.
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>

#include "../merc_defs.h"

/* Prototypes */
public void        create_monster();
public void        introduce(object who);
public void        react_intro(object tp);
public string      default_answer();
public int         special_attack(object enemy);
public varargs int heave(object victim);
public void        notify_death(object killer);
public void        run_away();
public int         notify_you_killed_me(object player);
public void        attacked_by(object attacker);
public string      check_for_broom();


/*
 * Function name:        create_monster
 * Description  :        set up the npc
 */
public void
create_monster()
{
    set_living_name("pearl");
    set_name("pearl");
    add_name( ({ "wife", "waitress", "waiter", "woman",
                 "_merc_guild_waiter" }) );
    set_race_name("human");
    set_gender(G_FEMALE);
    add_adj( ({ "cooks", "cook's" }) );

    set_title("Black, Waitress for the Mercenary Guild");

    set_short("gruff irritable waitress");
    set_long("Some people wear daggers on their belts, but this woman"
      + " wears them instead in her eyes! Her glowering disposition is"
      + " famous here in the Mercenary Guild, where she keeps things"
      + " running in the Feasting Hall. Those who cross her soon learn"
      + " why her husband, the cook, is so mild-mannered in her"
      + " presence.\n");

    set_stats( ({ 400, 400, 400, 90, 90, 200 }) ); /* Cackle!! */
    set_alignment(0); /* Serves no cause but her own. */
    set_all_hitloc_unarmed(200); /* She is nearly invulnerable. */
    set_all_attack_unarmed(60, 60); /* Hits like a ton of bricks! */
    set_whimpy(0); /* She fears nothing. */

    set_act_time(10);
    add_act("emote roars: WHO left a mess on this table? WHO!?!");
    add_act("emote storms into the kitchen where some loud crashing"
      + " is heard, and then arrives again with a set of clean"
      + " dishes.");
    add_act("emote snarls: You going to <order> something, or should"
      + " I just fix you what I think you deserve?");
    add_act("emote says: Slave all day, and what thanks do I get? More"
      + " slobs like you show up to mess the place up AGAIN!");
    add_act("shout HAROLD! Why aren't those orders cooked up yet?!");
    add_act("emote scrubs a nearby table so ferociously it looks as"
      + " if she might remove some of the varnish.");

    set_cact_time(4);
    add_cact("shout Dinner is served - first course ... your ASS!!");
    add_cact("emote gets a look in her eyes that would frighten"
      + " the Devil himself!");
    add_cact("say Time for Pearl to teach you some manners!");

    set_default_answer(VBFC_ME("default_answer"));

    add_ask( ({ "broom", "missing broom" }),
        "say " + "@@check_for_broom@@", 1);

    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(LIVE_I_NO_CORPSE, 1); /* She runs away instead. */

    set_skill(SS_UNARM_COMBAT, 100); /* Don't mess with Pearl! */

    setuid();
    seteuid(getuid());

} /* create_monster */     


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Where'd they go now?");
        return;
    }

    command("introduce me");
} /* react_intro */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("scowl . "+this_player()->query_real_name());
    command("say I got nothin' to say to you! If you want to <order>"
      + " some food, we talk!");
    return "";
} /* default_answer */


/*
 * Function name:        special_attack
 * Description  :        this is the npc's special
 *                       melee attack
 * Arguments    :        object enemy - who the npc fights
 * Returns      :        0 - no special attack
 *                       1 - special attack
 */
public int
special_attack(object enemy)
{
    int     attack_type = random(20);

    if (attack_type < 4)
    {
        set_alarm(0.0, 0.0, &heave(enemy));
        return 1;
    }

    return 0;
} /* special_attack */


/*
 * Function name:        heave
 * Description  :        this is the npcs's special attack. It takes
 *                       the player, and attempts to throw them into
 *                       the nearby rock wall to damage, and potentially
 *                       kill them.
 * Arguments    :        object victim - the player
 * Returns      :        integer 1
 */
public varargs int
heave(object victim)
{
    object *enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
    mixed  *sdam;
    string *hitloc;
    string  his = victim->query_possessive();
    string  him = victim->query_objective();
    string  he  = victim->query_pronoun();
    string *msg_var = one_of_list( ({
              ({ "the wall", "shoulder", "the timbers" }),
              ({ "one of the tables", "hip", "the hard wooden edge" }),
              ({ "a window", "back", "the window frame" }),
              ({ "the bulletin board", "head", "its numerous pointy"
                 + " bits" }) }) );

    if (!objectp(victim) && !sizeof(enemies))
    {
        return 1;
    }

    if (!objectp(victim))
    {
        victim = enemies[random(sizeof(enemies))];
    }

    if (environment(victim) != environment(this_object()))
    {
        return 1;
    }

    sdam = victim->hit_me(F_PENMOD(70, 100), W_IMPALE, this_object(), -1);

    switch(sdam[0])
    {
        case 0:
            victim->catch_msg(QCTNAME(this_object()) + " lunges at you with"
              + " terrifying speed, but you leap aside!\n");
            say(QCTNAME(this_object()) + " lunges suddenly toward "
              + QTNAME(victim) + " with terrifying speed, but "
              + QTNAME(victim) + " leaps aside!\n", victim);
            break;
        case 1..5:
            victim->catch_msg(QCTNAME(this_object()) + " lunges suddenly"
              + " at you, and grabs you by the scruff of the neck to"
              + " throw you hard against " + msg_var[0]
              + "! You just barely manage to stagger your"
              + " steps to cushion against the blow as your " + msg_var[1]
              + " glances against " + msg_var[2] + ".\n");
            say(QCTNAME(this_object()) + " lunges suddenly at " 
              + QTNAME(victim) + ", grabbing " + him + " by the scruff"
              + " of the neck to throw "
              + him + " hard against " + msg_var[0] + "! " + QTNAME(victim)
              + " just manages to stagger " + his + " steps to"
              + " cushion against the blow as " + his + " " + msg_var[1]
              + " glances against " + msg_var[2] + ".\n", victim);
            break;
        case 6..20:
            victim->catch_msg(QCTNAME(this_object()) + " grabs you roughly by"
              + " the arm, and flings you sidelong into the chimney!"
              + " Pain washes over your entire side as you collide"
              + " with the jagged surface, and you scramble to regain"
              + " your footing.\n");
            say(QCTNAME(this_object()) + " grabs " + QTNAME(victim) + " roughly"
              + " by the arm, and flings " + him + " sidelong into"
              + " the chimney! A look of pain crosses " + his
              + " face as " + he + " collides with the jagged surface,"
              + " and quickly attempts to regain " + his
              + " footing.\n", victim);
            break;
        case 21..50:
            victim->catch_msg(QCTNAME(this_object()) + " grabs you suddenly by"
              + " the throat, and thrusts you against the bulletin board"
              + " with blinding speed! You senses are blinded"
              + " momentarily by pain as your head and back are pinned"
              + " by her fearsome grip! You twist out of her grasp and"
              + " quickly turn to face her once more.\n");
            say(QCTNAME(this_object()) + " grabs " + QTNAME(victim) + " suddenly"
              + " by the throat, and thrusts " + him + " against the"
              + " bulletin board with blinding speed! " + capitalize(his)
              + " face blanches as " + his + " head and back are"
              + " pinned by " + QTNAME(this_object()) + "'s fearsome grip! "
              + QCTNAME(victim) + " twists away and turns quickly"
              + " again to face " + his + " enemy.\n", victim);
            break;
        case 51..99:
            victim->catch_msg(QCTNAME(this_object()) + " grabs you by the"
              + " back of your head, driving you face-first into the"
              + " surface of a nearby table with terrifying power! All"
              + " goes black for a moment, as pain and numbness wash over"
              + " your senses. Disoriented, you slowly rise to your feet.\n");
            say(QCTNAME(this_object()) + " grabs " + QTNAME(victim) + " by the"
              + " back of " + QTNAME(victim) + "'s"
              + " head, driving " + him + " face-first into the surface"
              + " of a nearby table with terrifying force! Dazzled by the"
              + " collision, " + QTNAME(victim) + " sprawls to the"
              + " ground and slowly rises, wobbling slightly, to "
              + his + " feet.\n", victim);
            break;
        default:
            victim->catch_msg("With a hair-raising cackle, "
              + QTNAME(this_object()) + " lunges for you, grabbing your neck with"
              + " both of her powerful hands! You feel your entire body"
              + " dragged head-first toward the cauldron of boiling water"
              + " that hangs over the fire! The last thing you hear is the sound"
              + " of your own face being cooked!\n");
            say("With a hair-raising cackle, " + QTNAME(this_object())
              + " lunges for " + QTNAME(victim) + ", grabbing " + his
              + " neck with both powerful hands! Her spindly arms twisting"
              + " with terrible strength, " + QTNAME(this_object()) + " drags "
              + QTNAME(victim) + "'s helpless body forward and dunks "
              + him + " head-first into the cauldron of boiling water"
              + " that hangs over the fire! The gut-churning sound of"
              + " a cooking face sounds throughout the hall, and "
              + QTNAME(victim) + " falls dead to the floor.\n", victim);
            break;
    }

    if (victim->query_hp() == 0)
    {
        victim->do_die(this_object());
    }

    return 1;
} /* heave */


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death,
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    tell_room(environment(this_object()), 
        QCTNAME(this_object()) + " bellows: Driven out of my own"
          + " guild by this riff raff?! I'll never live this down!!\n"
          + QCTNAME(this_object()) + " shoves you out of the way and"
          + " storms out of the building!\n");

    if (living(killer))
    {
        tell_object(killer, 
            "You've bested Pearl!\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + 
            " has bested Pearl!\n",
           ({ this_object(), killer }));
    }

    write_file(LOG_DIR + "pearl", killer->query_name() + " ("
      + killer->query_average_stat() + ") defeated Pearl!\n");
} /* notify_death */


/*
 * Function name:        run_away
 * Description  :        we mask the fun from /std/living/combat.c to
 *                       keep him from ever leaving the ledge.
 */
public void
run_away()
{
    command("cackle");
    command("shout My husband's cooking is scarier than you!");

    return;
} /* run_away */


/*
 * Function name:        notify_you_killed_me
 * Description  :        Called when this npc kills something. We want
 *                       to see who she ends up killing.
 * Arguments    :        object player: the one who was killed
 * Returns      :        1
 */
public int
notify_you_killed_me(object player)
{
    write_file(LOG_DIR + "pearl",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(player->query_name()) + " was killed by "
      + capitalize(query_real_name()) + "!\n");

    return 1;
} /* notify_you_killed_me */


/*
 * Function name:        attacked_by
 * Description  :        Lets keep track of who attacks us for now
 * Arguments    :        object attacker - who is attacking us?
 */
public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);

    this_player()->catch_tell(this_object()->query_The_name(attacker)
      + " spins to face you with a savage look in her eyes.\n");
    tell_room(environment(this_object()), QCTNAME(this_object())
      + " spins to face " + QTNAME(attacker) + " with a savage look"
      + " in her eyes.\n", attacker);
    tell_room(environment(this_object()), QCTNAME(this_object())
      + " shrieks: You haven't got what it takes, "
      + ((attacker->query_gender()) ? "girlie" : "sonny") + "!\n");

    write_file(LOG_DIR + "pearl", 
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(attacker->query_name()) + " attacked"
      + " Pearl.\n");
} /* attacked_by */


/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */


/*
 * Function name:        check_for_broom
 * Description  :        If the broom has been removed from the
 *                       broom closet, the waitress can find it
 *                       and bring it back, or summon a new one.
 * Returns      :        string - the spoken response to the
 *                                add_ask that calls this function.
 */
public string
check_for_broom()
{
    object  broom_location;
    object  broom_closet;
    string  broom_txt;

    broom_closet = safely_load_master_file(ROOM_DIR + "broom_closet");
    broom_location = broom_closet->add_broom();

    write_file(LOG_DIR + "broom", ctime() + ": " + this_player()->query_real_name() + " summoned broom\n");

    switch (broom_location)
    {
        case 1:
            broom_txt = "Bah! Someone obviously took it and lost it"
              + " completely. Wasteful and annoying!!";
            break;
        case 2:
            broom_txt = "Looks like some careless idiot took it and"
              + " left it somewhere OTHER than where it belongs.";
            break;
        case 3:
            broom_txt = "Some fool has carried it off and probably"
              + " forgot they even have it. How typical!!";
            break;
        default:
            return "The broom is in the broom closet where it"
              + " belongs. Quit bothering me about that!";
            break;
    }

    return broom_txt + "\n\nShe snaps her fingers and there is a"
      + " brief flash of magic!\n\nShe says: There. It is back in the"
      + " broom closet where it belongs.";
} /* check_for_broom */
