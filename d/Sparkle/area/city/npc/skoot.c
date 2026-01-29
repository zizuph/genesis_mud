/*
 *  /d/Sparkle/area/city/npc/skoot.c
 *
 *  Skoot is the salty old dwarf who runs the arm-wrestling
 *  in the lounge of the Sparkle Pub. He's good people!
 *
 *  Created May 2019, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "/d/Sparkle/lib/defs.h"

inherit "/d/Sparkle/area/city/npc/sparkle_npc";
inherit "/d/Genesis/lib/intro";
inherit "/d/Sparkle/lib/quest_reward";
inherit S_LIB_CLOCK;

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <time.h>
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"


/* Definitions */
#define    BLANK_SPACE        tell_room(environment(this_object()), "\n")
#define    WRESTLING_MASTER   (OBJ_DIR + "wrestling_master")
#define    FLIP_HOUR          23


/* Global Variables */
public string     *Skoot_Acts = ({
                       "emote yells: C'mon lads! Let's not be shy."
                     + " Be the next to offer a <challenge> and show"
                     + " us what ye be made of!",
                       "emote looks over the scoreboard and mutters"
                     + " something about the old days, when people"
                     + " lined up down the street for a shot.",
                       "emote wanders to an empty stool and takes"
                     + " a moment to count his coins.",
                       "emote talks to a nearby patron, saying:"
                     + " Oye! That last <bet> of ye's paid for"
                     + " more than a few drinks, I be guessin'!",
                       "emote smiles gratefully as Ellingnor"
                     + " sweeps in and out of the lounge, refilling"
                     + " his mug with dark ale as s/he passes.",
                       "emote passes by the scoreboard and lifts"
                     + " the list of records, reading over it with"
                     + " a smile.",
                       "emote calls out to the room, urging"
                     + " any brave soul to be the next to issue"
                     + " a proper <challenge> for a match.",
                       "emote takes a long swig from his nearly"
                     + " empty mug.", });
public int       Flipping_Date = 0; /* true when day is about to flip */


/* Prototypes */
public void        create_sparkle_npc();
public void        alert_hour_change_hook(int hour);
public void        check_for_flip();
public int         near_midnight();
public void        add_sparkle_asks();
public void        introduce(object who);
public void        react_intro(object tp);
public string      default_answer();
public void        run_away();
public void        arm_me();
public void        show_hook(object ob);
public void        react_items(object obj, object to);
public void        intro_check(object who);
public string      ask_skoot(string question);
public void        react_rudeness();
public string      check_betting_tours(object who);
public string      check_tours(object who);
public string      wrestle_rewards(object who);
public string      bet_quest_rewards(object who);
public void        reward_player(object who, string quest);


/* 
 * Function name:       create_sparkle_npc
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sparkle_npc()
{
    set_living_name("skoot");
    set_name("skoot");
    add_name( ({ "_sparkle_pub_wrestling_manager", "bookie",
                 "manager" }) );
    set_race_name("dwarf");
    set_gender(G_MALE);
    add_adj( ({ "salty", "old", "wrestling", "arm-wrestling", }) );

    npcsize(this_object(), "extremely short", "lean");

    set_title("McGoot, Arm Wrestling Bookie of Great Reknown");

    set_short("salty old dwarf");
    set_long("A rather thin old dwarf, Skoot looks as salty as the beach"
      + " at low tide. He keeps a keen eye to the lounge, always ready to"
      + " officiate any arm-wrestling <challenge> that gets going. He"
      + " fusses at the scoreboard and dusts the payout chart somewhat"
      + " compulsively whenever there is a lull in the action. You"
      + " hear people asking him about betting and quests from time"
      + " to time, too.\n");

    set_stats( ({ 100, 65, 111, 87, 100, 90 }) );
    set_alignment(400); /* A decent fellow. */
    set_whimpy(0); /* He shall not leave! */

    add_ask( ({ "task", "tasks", "help", "help with tasks",
                "task help", "helping", "helping with tasks",
                "tasks you may need help with",
                "tasks he may need help with",
                "quest", "quests", "help", "tour", "tours",
                "for quest", "for quests", "for task", "for tasks" }),
        "say " + "@@ask_skoot|tasks@@", 1);

    add_ask( ({ "reward", "rewards", "for reward", "for rewards" }),
        "say " + "@@ask_skoot|reward@@", 1);

    add_ask( ({ "ellingnor", "bartender", }),
        "say " + "@@ask_skoot|bartender@@", 1);

    add_ask( ({ "bet", "bets", "betting", "wager", "wagers", }),
        "say " + "@@ask_skoot|betting@@", 1);

    add_ask( ({ "agreement", "special agreement", }),
        "say " + "@@ask_skoot|agreement@@", 1);

    add_ask( ({ "promise", "betting promise", "me promise",
                "special reward", "special" }),
        "say " + "@@ask_skoot|promise@@", 1);

    add_ask( ({ "wrestling", "challenge", "arm wrestling",
                "arm-wrestling", "match", "wrestle",
                "arm-wrestle" }),
        "say " + "@@ask_skoot|wrestling@@", 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " is too busy to notice you shoving"
      + " things at him. You might <bet> on a match, though.\n");

    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(NPC_I_NO_LOOKS, 1);           /* no beauty words */

    add_prop(OBJ_M_NO_ATTACK, "Somehow aware of what you are doing,"
      + " even here in the lounge, the massive hellcat peeks it's"
      + " head into the lounge and growls. You back off.\n");

    set_skill(SS_UNARM_COMBAT, 80);      /* He's a wrestler!      */
    set_skill(SS_AWARENESS, 80);         /* Keeps an eye out ...  */

    setuid();
    seteuid(getuid());
} /* create_sparkle_npc */   


/*
 * Function name:       alert_hour_change_hook
 * Description  :       This function gets called whenever the hour
 *                      hour changes in the City of Sparkle
 *                      NPCs can use this to act upon the hour,
 *                      to provide the semblance of a daily routine.
 *                      In the case of the bartender, we use this to
 *                      trigger acts, rather than using add_act().
 *                      We also use it to see if the date has
 *                      changed (at midnight RL.) If so, we erase
 *                      all scores.
 * Arguments    :       hour - current hour in Sparkle time
 */
public void
alert_hour_change_hook(int hour)
{
    switch (hour)
    {
    case 0:
    case 3:
    case 6:
    case 9:
    case 12:
    case 15:
    case 18:
    case 21:
    case 16:
    case 18:
    case 20:
        /* We only perform actions every 3 Sparkle hours, to
         * avoid undue spam. We'll limit even further with a random
         * chance.
         */
        if (!random(3) && !near_midnight())
        {
            command(one_of_list(Skoot_Acts));
            
        }
        break;
    default:
        break;
    }

    set_alarm(3.0, 0.0, check_for_flip);

    return;

} /* alert_hour_change_hook */


/*
 * Function name:        check_for_flip
 * Description  :        See if it is time, or close to time to
 *                       flip the board
 */
public void
check_for_flip()
{
    int     midnight_looms = near_midnight();

    if (Flipping_Date)
    {
        if (!midnight_looms)
        {
            Flipping_Date = 0;
            command("say Alright lads! Let's get back to the action."
              + " 'Tis a new day fer new scores!!");
            WRESTLING_MASTER->wrestling_data_check();
            return;
        }

        command("emote continues to fuss around the score board,"
          + " getting it ready for the next day.");
        return;
    }

    if (midnight_looms)
    {
        Flipping_Date = 1;

        command("say Alright lads! I've got me tallies finished and"
          + " so now I'll be settin' up the board fer the new day"
          + " ta come. We'll keep matches on hold fer another"
          + " fiver.");
        BLANK_SPACE;
        command("emote goes over and begins erasing the past day's"
          + " scores from the board.");

        WRESTLING_MASTER->flip_wrestling_day();

        return;
    }
} /* check_for_flip */


/*
 * Function name:       near_midnight
 * Description  :       get some info about whether it is soon to be
 *                      a day flip.
 * Returns      :       int - 0 if more than 5 minutes till midnight
 *                            otherwise, return number of minutes left
 *                            till midnight.
 */
public int
near_midnight()
{
    string    time_txt = ctime(time());
    int       hour     = atoi(time_txt[11..12]);
    int       minutes  = atoi(time_txt[14..15]);
    int       remain   = 60 - minutes;

//  command("say remain = " + remain);

    if (hour == FLIP_HOUR && remain == 10)
    {
        command("emote checks a strange glowing timepiece.");
        command("say 'Tis nigh midnight, netherworld time, ye lubbers!"
          + " I be closin' down the matches fer daily scorekeeping in"
          + " just a sec. I be needing a bit o peace fer the tallies,"
          + " so let's finish this up, and take a break!");

        write_file(LOG_DIR + "arm_wrestle_hauls", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + "Today's haul - " + WRESTLING_MASTER->net_haul());
    }

    if (hour == FLIP_HOUR && remain < 5)
    {
        return remain;
    }

    return 0;
} /* near_midnight */


/*
 * Function name:       add_sparkle_asks
 * Description  :       Redefine this so he doesn't jabber the same way
 *                      the standard Sparkle npc might.
 */
public void
add_sparkle_asks()
{
    add_ask( ({ "city", "sparkle", "city of sparkle", "town",
            "village", "area" }),
        "say " + "@@ask_skoot|sparkle@@", 1);
    add_ask( ({ "job", "occupation", "work", "career" }),
        "say " + "@@ask_skoot|job@@", 1);
    add_ask( ( Swear_Words ),
        "say " + "@@ask_skoot|cuss@@", 1);
        
} /* add_sparkle_asks */


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
        command("emote looks side to side and frowns.");
        return;
    }

    intro_check(tp);
} /* react_intro */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("say " + ask_skoot("no_info"));
    return "";
} /* default_answer */


/*
 * Function name: greetings 
 * Description:   This function makes the npc do a greeting to people it
 *                already know and to fellow npc's. It is possible to
 *                redefine, not however that it should never contain an
 *                'introduce myself' command.
 * Arguments:     object who - the living that introduced to me
 *
 */
public void
greet(object who)
{
    command("say Up for a <challenge>, " + who->query_name() + "?");
}


/*
 * Function name:        run_away
 * Description  :        we mask the fun from /std/living/combat.c to
 *                       make sure he doesn't go anywhere. Not sure if
 *                       this is possible, but just in case.
 */
public void
run_away()
{
    command("sneer");
    command("say I be never leavin' the lounge, ye rat!");

    return;
} /* run_away */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;

    arm = clone_object("/std/weapon");
    arm->set_name("chalk");
    arm->add_name("piece");
    arm->set_short("sharp piece of chalk");
    arm->set_pshort("sharp pieces of chalk");
    arm->set_adj( ({ "sharp" }) );
    arm->set_long("This chalk has been used recently to write on"
      + " something. It is worn to a fine sharp point.\n");
    arm->set_hit(5);
    arm->set_pen(14);
    arm->add_prop(OBJ_I_WEIGHT, 2);
    arm->add_prop(OBJ_I_VOLUME, 5);
    arm->move(this_object());

    command("wield all");
} /* arm_me */


/*
 * function name: show_hook
 * description  : this hook is called whenever an item is 'shown' to this
 *                living. It is shown by this_player().
 * arguments    : object ob - the object shown.
 */
public void
show_hook(object ob)
{
    set_alarm(1.0, 0.0, &react_items(ob, this_player()));
} /* show_hook */


/*
 * Function name:        react_items
 * Description  :        have the npc respond to a specific object
 * Arguments    :        object obj - the object that was shown
 *                       object to  - the player who showed it
 */
public void
react_items(object obj, object to)
{
    intro_check(to);

    command("say I gots no interest in 'yer stuff!");
    return;
} /* react_items */ 


/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{

    command("say I be not wantin' yer things. If ye care to <bet>"
      + " on a match, we'll deal in coin, o'course.");


    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));

    if (environment(obj) == this_object())
    {
        command("drop " + OB_NAME(obj));
    }
} /* return_object */


/*
 * Function name:        intro_check
 * Description  :        Lets shorten the spam by having him intro if
 *                       the player doesn't know him yet.
 * Arguments    :        object who - the player
 */
public void
intro_check(object who)
{
    if (!IN_ARRAY(this_object()->query_real_name(),
         m_indices(who->query_introduced())))
    {
        command("say Aha ... perhaps here be a new challenger?");
        command("introduce myself");
    }
}


/*
 * Function name:        ask_skoot
 * Description  :        Make a particular query to Skoot
 * Arguments    :        string question - the subject of the ask
 * Returns      :        The response
 */
public string
ask_skoot(string question)
{
    intro_check(this_player());

    switch(question)
    {
        default:
        case "no_info":
            return "I got nothin' on me mind but arm-wrestling! If"
              + " ye want to ask me about that, we talk!";
            break;
        case "tasks":
            return check_tours(this_player());
            break;
        case "bartender":
            return "That one be a saint, and friend to the whole"
              + " brotherhood o' arm-wrestlin'!";
            break;
        case "betting":
            return "Betting be half the fun! Once we've got two"
              + " challengers I be openin' the bets. Then ye can"
              + " <bet> on whoever ye wish. Ye can see the payouts"
              + " on the chart there beneath the scoreboard. Ye"
              + " can also ask about the special agreement I be"
              + " havin' with ye if ye bet!";
            break;
        case "agreement":
            return check_betting_tours(this_player());
            break;
        case "promise":
            return bet_quest_rewards(this_player());
            break;
        case "wrestling":
            return "Be ye wantin' to arm-wrestle? Ye need but"
              + " <challenge> the room, and we'll see if anyone"
              + " feels like takin' ye on! Ye can check the scoreboard"
              + " ta see how the days matches have gone so far. There"
              + " also be the all-time records if ye wants ta see"
              + " 'em on the list below the board. Also! Ye ask"
              + " about quests! Arm-wrestling be quest-worthy!";
            break;
        case "reward":
            return wrestle_rewards(this_player());
            break;
    }

    /* Should never happen, but just in case. */
    return "Ehh? What's that? I be a bit confused ...";
} /* ask_skoot */


/*
 * Function name: emote_hook
 * Description  : Whenever an emotion is performed on this living, or when it
 *                is performed in the room in general, this function is called
 *                to let the living know about the emotion. This way we can
 *                avoid the usage of all those costly triggers.
 * Arguments    : string emote - the name of the emotion performed. This
 *                    always is the command the player typed, query_verb().
 *                object actor - the actor of the emotion.
 *                string adverb - the adverb used with the emotion, if there
 *                    was one. When an adverb is possible with the emotion,
 *                    this argument is either "" or it will contain the used
 *                    emotion, preceded by a " " (space). This way you can
 *                    use the adverb in your reaction if you please without
 *                    having to parse it further.
 *                object *oblist - the targets of the emotion, if any.
 *                int cmd_attr - the command attributes, if any.
 *                int target - if true, this object was a target of the emote.
 *
 * We are masking this hook to allow Ellingnor to react to various
 * types of emotes.
 */
public void
emote_hook(string emote, object actor, string adverb, object *oblist,     
           int cmd_attr, int target)
{
    if (ACTION_OFFENSIVE & cmd_attr)
    {
        react_rudeness();
    }

    if (ACTION_INTIMATE & cmd_attr)
    {
        react_rudeness();
    }
} /* emote_hook */


/*
 * Function name:        react_rudeness
 * Description  :        We'll give some likely responses to rude
 *                       behavior
 */
public void
react_rudeness()
{
    command(one_of_list( ({ "ack", "gasp", "blink", "glare" }) ));

    command(one_of_list( ({
        "say Ach, ye be a drowned wretch, ye be!",
        "say Scuttle off, ye black-bottomed lubber!",
        "say I'll be cleanin' yer clock soon, ye dog!",
        "say Take yer fool self away before I gets upset!",
        "say Someone be teachin ye' a lesson someday!",
        "say Get ye' away, fool!",
        "say I'll be reportin' this ta the barkeep soon!",
        "say Quit yer fool behavior!",
        "say T'ain't what I be in the mood fer, ye scum-dog!",
        "say Ten thousand thundering typhoons!",
        }) ));
} /* react_rudeness */


/*
 * Function name:        check_betting_tours
 * Description  :        See if this player has already done the quests
 *                       given out by this npc for betting
 * Arguments    :        object who - the player
 * Returns      :        string - what s/he (the npc) will say
 */
public string
check_betting_tours(object who)
{
    if (!who->test_bit("Sparkle",
            WRESTLE_BETS_Q1_GROUP,
            WRESTLE_BETS_Q1_BIT))
    {
        BLANK_SPACE;
        return "Arm wrestlin' be a beautiful thing. But it be at"
          + " its finest when thar be fun and profit fer all! I'll"
          + " make ye a promise. Ye win a single <bet> on any"
          + " wrestlin' challenger, and I'll give ye a special"
          + " reward. Just <ask> me about me promise once ye've"
          + " done it!";
    }

    if (!who->test_bit("Sparkle",
            WRESTLE_BETS_Q2_GROUP,
            WRESTLE_BETS_Q2_BIT))
    {
        BLANK_SPACE;
        return "Ye've done a bit o betting now, eh? Let's take"
          + " that up a notch with me next promise. Ye go ahead"
          + " and win ten bets in a single day, and then I"
          + " be givin' ye another reward. Just <ask> me about"
          + " me promise once yet get 'em all!";
    }

    BLANK_SPACE;
    return "Ah, it's ye! Ye be one of my favorites. Ye've done more"
      + " betting than most, and I be appreciatin' it! I've"
      + " honoured me promises and got none left fer ye other"
      + " than to encourage ye to keep tryin' fer money on more"
      + " betting wins.";
} /* check_betting_tours */


/*
 * Function name:        check_tours
 * Description  :        See if this player has already done the quest
 *                       given out by this npc
 * Arguments    :        object who - the player
 * Returns      :        string - what s/he (the npc) will say
 */
public string
check_tours(object who)
{
    if (!who->test_bit("Sparkle",
            ARM_WRESTLE_Q1_GROUP,
            ARM_WRESTLE_Q1_BIT))
    {
        BLANK_SPACE;
        return "Ye seem pretty green ta the beautiful art o' arm-"
          + "wrestling, thar, matey! Yer first task along the"
          + " path is ta win a match - any kind o match! Just"
          + " <challenge> the room and see if thar be anyone who'll"
          + " give it a go with ye! If ye've got yer win, just ask"
          + " me about yer reward.";
    }

    if (!who->test_bit("Sparkle",
            ARM_WRESTLE_Q2_GROUP,
            ARM_WRESTLE_Q2_BIT))
    {
        BLANK_SPACE;
        return "Aye, so ye've at least won a match. But, have ye"
          + " done it as an underdog? Ask me fer another reward once"
          + " ye've beaten a much stronger foe! (Be rememberin' the"
          + " amulet Karkadelt sells if ye be bigger 'n most"
          + " folk ...) Also, did ye notice ye can take on"
          + " any <attitude> ye be wantin' fer the match?";
    }

    if (!who->test_bit("Sparkle",
            ARM_WRESTLE_Q3_GROUP,
            ARM_WRESTLE_Q3_BIT))
    {
        BLANK_SPACE;
        return "Aye now ... ye've shown us that ye can win no"
          + " matter the odds. This be what we need around here!"
          + " Now, I be givin ye the next reward, a dandy one too,"
          + " if ye be winning fifteen matches in a single day. Har!"
          + " That'll be a feat! And, I'll give ye a reward once"
          + " ye've done it. Ye can <exa board> here to see how"
          + " ye be doin' along the way.";
    }

    if (!who->test_bit("Sparkle",
            ARM_WRESTLE_Q4_GROUP,
            ARM_WRESTLE_Q4_BIT))
    {
        BLANK_SPACE;
        return "Ah, it be ye. Folk still be talkin' about yer"
          + " fifteen wins in a single day, oho yes! And ye be still"
          + " lookin' fer a bigger fish ta fry?? Well, so be it!"
          + " Ye win five wins in a single day as an UNDERDOG."
          + " Ye do that, and I'll reward ye like yer a frickin'"
          + " King O The Ring! (Oh, and if ye be findin none who"
          + " is bigger than ye, just remember that amulet thingie"
          + " Karkadelt sells. It be makin' ye nice and weak!)";
    }

    if (!who->test_bit("Sparkle",
            ARM_WRESTLE_CHAMP_GROUP,
            ARM_WRESTLE_CHAMP_BIT))
    {
        BLANK_SPACE;
        return "Ye've done proved yerself as a real force at the"
          + " table, mate. I do be havin' one final challenge"
          + " fer the ultimate achievement, but it be too must"
          + " ta be askin' most folks. But ye be different than"
          + " most folks already! I got this here tally o"
          + " champions. It be those who had the top number o"
          + " wins at the end of an entire day. If ye ever make"
          + " it on this list, ye be askin' fer the last reward,"
          + " and ye will have earned it - more reward than"
          + " all the others combined!";
    }

    BLANK_SPACE;
    return "Oho, tis ye! Behold, the Frickin' Legend in the"
      + " flesh!! Ye've proved all needs be proved ta me and any"
      + " arm-wrestler in the realm! I be a fan, I be! That"
      + " bein' the case, ye've got all the rewards I can"
      + " think to give.";
} /* check_tours */


/*
 * Function name:        wrestle_rewards
 * Description  :        Allow players to check if they have
 *                       earned a reward for arm-wrestling.
 * Arguments    :        object who - the player checking
 * Returns      :        string - The npc dialogue
 */
public string
wrestle_rewards(object who)
{
    string  wname = who->query_real_name();
    int     victory_test;

    if (!who->test_bit("Sparkle",
            ARM_WRESTLE_Q1_GROUP,
            ARM_WRESTLE_Q1_BIT))
    {
        victory_test = WRESTLING_MASTER->query_victories(wname);

        if (!victory_test)
        {
            BLANK_SPACE;
            return "Reward? Fer what?? Ye've not won a single"
              + " arm-wrestling <challenge> yet today! Ye can"
              + " ask me about me quests if ye wants to know"
              + " what I'd be wantin' ta see from ye!";
        }

        set_alarm(1.0, 0.0, &reward_player(who, "one"));

        BLANK_SPACE;
        return "Ye did a good job out thar, matey! Everybody"
          + " likes ta see a winner, and ye did not dissapoint!"
          + " I got a bit more questin' fer ya, if ye be"
          + " wantin' to prove yerself again.";
    }

    if (!who->test_bit("Sparkle",
            ARM_WRESTLE_Q2_GROUP,
            ARM_WRESTLE_Q2_BIT))
    {
        victory_test = WRESTLING_MASTER->query_victories(
                                             wname, "udog");

        if (!victory_test)
        {
            BLANK_SPACE;
            return "Reward? Ye've not done much ta deserve it,"
              + " ye lubber! Ye be askin' me about quests I be"
              + " lookin' ta see done, and maybe ye be earnin'"
              + " one with a bit o' sweat.";
        }

        set_alarm(1.0, 0.0, &reward_player(who, "two"));

        BLANK_SPACE;
        return "Ye went and won as an underdog! I tell ye ..."
          + " nothin' be gettin' tha room more riled up and"
          + " bettin' strong than that! I be grateful, and"
          + " ye be deservin' this! I got more, too, if ye"
          + " want ta ask about another quest.";
    }

    if (!who->test_bit("Sparkle",
            ARM_WRESTLE_Q3_GROUP,
            ARM_WRESTLE_Q3_BIT))
    {
        victory_test = WRESTLING_MASTER->query_victories(wname);

        if (victory_test < 15)
        {
            BLANK_SPACE;
            return "Ye've shown ye can arm-wrestle, yes ..."
              + " But ye needs ta take it ta the next level"
              + " fer me ta reward ye again. Fifteen wins in a single"
              + " day be the goal. Be ye up to it, I wonder?";
        }

        set_alarm(1.0, 0.0, &reward_player(who, "three"));

        BLANK_SPACE;
        return "Here be the next Mergula, it be seemin!! Ye've"
          + " made me a heap o' coin on all yer wins today,"
          + " mate! I'd be a sorry bookie if I dinna pay out"
          + " to me champions somehow. Ye be earnin' this,"
          + " and no mistake! I be havin' another quest, if ye"
          + " be up for a true challenge!";
    }

    if (!who->test_bit("Sparkle",
            ARM_WRESTLE_Q4_GROUP,
            ARM_WRESTLE_Q4_BIT))
    {
        victory_test = WRESTLING_MASTER->query_victories(
                                             wname, "udog");

        if (victory_test < 5)
        {
            BLANK_SPACE;
            return "Aye, this one be askin' a lot, and ye've not"
              + " yet done it. We can talk about the quest again"
              + " if ye wants ta ask me. Don't be gettin'"
              + " discouraged - this one be takin' a session or"
              + " three fer even the best o the best!";
        }

        set_alarm(1.0, 0.0, &reward_player(who, "four"));

        BLANK_SPACE;
        return "IT BE UNBELIEVABLE!! Five wins in the span o"
          + " a single day as a wee underdog?? What ye' be eatin' fer"
          + " breakfast, mate? We all be listenin' and ready"
          + " ta copy yer ways! Ye've done all I be askin'"
          + " and made me more money than if I'd sold the"
          + " Sparkle Stone itself! Well, I guess thar do be"
          + " ONE more quest, if ye be in it fer the long haul.";
    }

    if (!who->test_bit("Sparkle",
            ARM_WRESTLE_CHAMP_GROUP,
            ARM_WRESTLE_CHAMP_BIT))
    {
        victory_test = WRESTLING_MASTER->has_been_champion(wname);

        if (!victory_test)
        {
            BLANK_SPACE;
            return "Aye, but the ultimate achievement still be"
              + " eludin' ye, matey! Ye've got to be the top champion"
              + " fer total wins at the end of an entire day! Ye talk"
              + " to me once ye've made me tally o' champions, and then"
              + " ye be earnin' the last and best reward.";
        }

        set_alarm(1.0, 0.0, &reward_player(who, "five"));

        BLANK_SPACE;
        return "TEN THOUSAND THUNDERIN' TYPHOONS, but ye did it"
          + " matey! YE DID IT!! Ye was champion after an entire"
          + " day, and that be worth its weight in gold fer a"
          + " bookie like meself. I be owin' ye, and ye've given"
          + " us all somethin' ta aspire to!";
    }

    BLANK_SPACE;
    return "Oho, tis ye! Behold, the Frickin' Legend in the"
      + " flesh!! Ye've proved all needs be proved ta me and any"
      + " arm-wrestler in the realm! I be a fan, I be! That"
      + " bein' the case, ye've got all the rewards I can"
      + " think to give.";
} /* wrestle_rewards */


/*
 * Function name:        bet_quest_rewards
 * Description  :        Allow players to check if they have
 *                       earned a quest reward for winning bets.
 * Arguments    :        object who - the player checking
 * Returns      :        string - The npc dialogue
 */
public string
bet_quest_rewards(object who)
{
    string  wname = who->query_real_name();
    int     bets_won = WRESTLING_MASTER->query_bets_won(wname);
    string  bet_talk = " ain't won any bets";

    if (!who->test_bit("Sparkle",
            WRESTLE_BETS_Q1_GROUP,
            WRESTLE_BETS_Q1_BIT))
    {
        if (!bets_won)
        {
            BLANK_SPACE;
            return "Promise? Me promise is to reward ye if ye can win"
              + " even one bet. Ye ain't done it yet today!";
        }

        set_alarm(1.0, 0.0, &reward_player(who, "six"));

        BLANK_SPACE;
        return "Ye went and won a bet, didn't ye! Well, I be a"
          + " dwarf o me word, and a promise is a promise. Here's"
          + " yer reward! Now, I gots another special agreement"
          + " fer ye, if ye be interested.";
    }

    if (!who->test_bit("Sparkle",
            WRESTLE_BETS_Q2_GROUP,
            WRESTLE_BETS_Q2_BIT))
    {
        if (bets_won < 10)
        {
            switch(bets_won)
            {
                case 1:
                    bet_talk = "'ve won only a single bet";
                    break;
                case 0:
                    break;
                default:
                    bet_talk = "'ve won " + LANG_NUM2WORD(bets_won)
                             + " bets";
                    break;
            }

            BLANK_SPACE;
            return "Me promise? Sure, and I be seein' ye"
              + bet_talk + " so far today. I be fulfillin' me"
              + " promise when ye be winnin' ten!";
        }

        set_alarm(1.0, 0.0, &reward_player(who, "seven"));

        BLANK_SPACE;
        return "Have ye won ten bets already today?? It be powerful"
          + " good luck! Well, ye win some, and ye lose some. Money"
          + " be comin' my way with so much bettin' and fer that I"
          + " be good on me word. A promise is a promise, and yer"
          + " reward is well earned!";
    }

    BLANK_SPACE;
    return "Ah, yes, I be still rememberin' the ten bets ye won!"
      + " We both been good on our word, thar, so let's call it"
      + " good enough fer now. Maybe ye feel like betting a bit"
      + " more just fer the coin ye be winnin'?";
} /* bet_quest_rewards */


/*
 * Function name:        reward_player
 * Description  :        Give the player their exp and let
 *                       them know they've gotten it.
 * Arguments    :        object who   - the player
 *                       string quest - which quest to reward
 */
public void
reward_player(object who, string quest)
{
    mapping w_map = ([ "one"   : ({ ARM_WRESTLE_Q1_GROUP,
                                    ARM_WRESTLE_Q1_BIT,
                                    ARM_WRESTLE_Q1_EXP,
                                    "a little bit more" }),
                       "two"   : ({ ARM_WRESTLE_Q2_GROUP,
                                    ARM_WRESTLE_Q2_BIT,
                                    ARM_WRESTLE_Q2_EXP,
                                    "a bit more", }),
                       "three" : ({ ARM_WRESTLE_Q3_GROUP,
                                    ARM_WRESTLE_Q3_BIT,
                                    ARM_WRESTLE_Q3_EXP,
                                    "more" }),
                       "four"  : ({ ARM_WRESTLE_Q4_GROUP,
                                    ARM_WRESTLE_Q4_BIT,
                                    ARM_WRESTLE_Q4_EXP,
                                    "much more" }),
                       "five"  : ({ ARM_WRESTLE_CHAMP_GROUP,
                                    ARM_WRESTLE_CHAMP_BIT,
                                    ARM_WRESTLE_CHAMP_EXP,
                                    "VASTLY more" }),
                       "six"   : ({ WRESTLE_BETS_Q1_GROUP,
                                    WRESTLE_BETS_Q1_BIT,
                                    WRESTLE_BETS_Q1_EXP,
                                    "a little bit more" }),
                       "seven" : ({ WRESTLE_BETS_Q2_GROUP,
                                    WRESTLE_BETS_Q2_BIT,
                                    WRESTLE_BETS_Q2_EXP,
                                    "more" }),
                     ]);
    int     w_group = w_map[quest][0];
    int     w_bit = w_map[quest][1];
    int     w_exp  = w_map[quest][2];
    string  w_msg  = w_map[quest][3];

    who->catch_tell("\nYou feel " + w_msg + " experienced!\n\n");

    give_reward(who, w_group, w_bit, w_exp,
                "arm_wrestling_" + LANG_WORD2NUM(quest), 1);
} /* reward_player */
