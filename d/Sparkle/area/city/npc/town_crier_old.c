/*
 *  /d/Sparkle/area/city/npc/town_crier.c
 *
 *  This is Carlsan, the Town Crier of Sparkle. He will be a questmaster
 *  for new players, handing out Tour-Style quests and magic maps to
 *  players who do not have them.
 *
 *  Created March 2011, by Cooper Sherry (Gorboth)
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
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <time.h>
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"


/* Definitions */
#define            BLANK_SPACE   tell_room(environment(this_object()), "\n")

/* Global Variables */
public int         Awake = 1; /* Is he awake? */
public int         Busy  = 0;
public object      Dog;
public string      Time_Readout = capitalize(s_get_stime_hour_of_period());
public object      Form;
public string     *Asleep_Acts = ({
                       "emote leans back in his chair, snoring loudly.",
                       "emote snores noisily, causing his bushy moustache"
                     + " to flutter.",
                       "emote suddenly jerks awake. Blinks sleepily a few"
                     + " times, and then leans back in his chair and"
                     + " begins snoring softly.",
                       "emote wakes as he hears a passer-by, and quickly"
                     + " begins shuffling papers around on his table, trying"
                     + " to look busy. After a moment, he falls back"
                     + " asleep.",
                       "emote is woken by the fluffy brown dog, who"
                     + " licks his hand determinedly. Tossing the dog"
                     + " a scrap of meat, he closes his eyes again.",
                       "emote slumps forward onto the table, snoring"
                     + " softly.",
                       "emote snores softly.",
                       "emote chuckles quietly in his sleep.", });
public string     *Awake_Acts = ({
                       "emote blinks sleepily.",
                       "emote rubs his moustache, peering around"
                     + " absentmindedly.",
                       "emote leans back in his chair, gets cozy, and sighs"
                     + " in relaxation.",
                       "emote smiles as he sees a passer-by, and quickly"
                     + " begins shuffling papers around on his table, trying"
                     + " to look busy.",
                       "emote smiles fondly at his dog, and rubs her"
                     + " on the head.",
                       "emote looks happily up and down the street.", });
public string     *Go_To_Sleep = ({
                       "emote slumps suddenly in his chair, and appears"
                     + " to have fallen asleep.",
                       "emote suddenly begins snoring loudly.",
                       "emote goes suddenly still, and begins softly"
                     + " snoring.",
                       "emote appears to have fallen asleep.",
                       "emote suddenly slumps forward, fast asleep.",
                       "emote closes his eyes and begins snoring.", });
public string     *Wake_Up = ({
                       "emote jerks awake, saying: Yes? What? Of course!",
                       "emote leaps forward in his chair, suddenly awake.",
                       "emote immediately opens his eyes and blinks.",
                       "emote almost falls off his chair, saying: Who?"
                     + " What? Oh ...",
                       "emote snaps out of his sleep and looks around.",
                       "emote comes awake and rubs his eyes.", });


/* Prototypes */
public void        create_sparkle_npc();
public void        add_sparkle_asks();
public void        introduce(object who);
public void        react_intro(object tp);
public string      default_answer();
public void        run_away();
public void        arm_me();
public void        alert_hour_change_hook(int hour);
public void        show_hook(object ob);
public void        react_items(object obj, object to);
public void        init_living();
public void        intro_check(object who);
public string      ask_sleeper(string question);
public void        awake_check(int dog_woke = 1);
public string      describe();
public void        check_dog();
public void        react_rudeness();
public void        react_freshness();
public string      exa_poster();
public int         do_wake(string arg);
public void        trigger_sleep();
public string      survey_results();
public string      check_tours(object who);
public void        react_form(object who);
public void        check_remaining_tours(object who);
public void        update_poster();
public void        enter_env(object dest, object old);
public void        react_cadets_checklist(object who);
public void        react_localqm_checklist(object who);
public int         crier_exit_check(object who);

public int         query_awake() { return Awake; }


/* 
 * Function name:       create_sparkle_npc
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sparkle_npc()
{
    set_living_name("carlsan");
    set_name("carlsan");
    add_name( ({ "crier", TOWN_CRIER, "man" }) );
    set_race_name("human");
    add_adj( ({ "town", "large", "sleepy", "sleeping", "snoring",
                "cheerful" }) );

    set_title("Fountaine, Town Crier of Sparkle");

    npcsize(this_object(), "short", "fat");

    set_short("large cheerful man");
    set_long("@@describe@@");

    set_stats( ({ 70, 40, 100, 30, 15, 20 }) ); /* He is not impressive. */
    set_alignment(500); /* A pleasant fellow. */

    set_default_answer(VBFC_ME("default_answer"));

    add_item( ({ "snorer", "town snorer" }),
        "If there were such a position as town snorer - he'd have it"
      + " completely covered. As it is, he is just the sort who falls"
      + " asleep on the job.\n");
    add_item( ({ "other paper", "other papers" }),
        "Among the other papers on the table you notice what appears to be"
      + " the tabulated results of a survey.\n");
    add_item( ({ "results", "survey results", "tabulated results",
                 "tabulated results of a survey",
                 "tabulated survey results" }), "@@survey_results@@");
    add_item( ({ "table", "large table" }),
        "The table is situated near to the entrance to the church, perhaps"
      + " so that the town crier can interact with any new visitors to the"
      + " realms. Of course, he'd have to be awake to do that, which is"
      + " all too often not the case.\n");
    add_item( ({ "clutter" }),
        "The table would be a total mess if not for the dog.\n");
    add_item( ({ "form", "forms", "official looking form",
                 "official looking forms", "official form",
                 "official forms", "survey", "surveys",
                 "survey form", "survey forms", "rating form",
                 "rating forms", "sign rating form",
                 "sign rating forms" }),
        "The forms on the table appear to be a survey of some kind. If you"
      + " haven't already done so, perhaps you could <ask> the town"
      + " crier about any tasks he may have. Perhaps these are involved"
      + " in one of them.\n");
    add_item( ({ "poster", }), "@@exa_poster@@");
    add_cmd_item( ({ "poster" }),
                  ({ "read" }), "@@exa_poster@@");
    add_cmd_item( ({ "form", "forms", "official looking form",
                 "official looking forms", "official form",
                 "official forms", "survey", "surveys",
                 "survey form", "survey forms", "rating form",
                 "rating forms", "sign rating form",
                 "sign rating forms" }),
                  ({ "get", "take", "steal" }),
        "The fluffy brown dog growls at you as you try to take one. Perhaps"
      + " if you <ask> the crier about tasks he might have something for"
      + " you to do with one of them.\n");

    remove_prop(LIVE_I_NEVERKNOWN);

    add_prop(OBJ_M_NO_ATTACK, "Just as you begin to make your move,"
      + " the fluffy brown dog at his side bares her teeth and"
      + " produces an uncanny growl. Whether there are some odd magicks"
      + " at work with this beast you cannot be sure, but you find your"
      + " willpower faltering completely.\n");

    set_skill(SS_UNARM_COMBAT, 20);      /* Just a bit here ...       */
    set_skill(SS_AWARENESS, 50);         /* His job calls for it.     */
    set_skill(SS_ANI_HANDL, 80);         /* He's good with his pooch. */


    add_ask( ({ "task", "tasks", "help", "help with tasks",
                "task help", "helping", "helping with tasks",
                "tasks you may need help with",
                "tasks he may need help with",
                "quest", "quests", "help", "tour", "tours" }),
        "say " + "@@ask_sleeper|tasks@@", 1);

    add_ask( ({ "poster" }), "say " + "@@ask_sleeper|poster@@", 1);

    add_ask( ({ "orc dungeon", "orc dungeons", "orc temple",
                "temple", "dungeon", "dungeons" }),
        "say " + "@@ask_sleeper|dungeon@@", 1);
    add_ask( ({ "magic map", "map" }),
        "say " + "@@ask_sleeper|map@@", 1);
    add_ask( ({ "church", "first church of sparkle", "sparkle church",
                "church of sparkle", "table" }),
        "say " + "@@ask_sleeper|church@@", 1);
    add_ask( ({ "orc", "orcs" }),
        "say " + "@@ask_sleeper|orcs@@", 1);
    add_ask( ({ "reward" }),
        "say " + "@@ask_sleeper|reward@@", 1);
    add_ask( ({ "pookie", "dog", "pet", "fluffy dog",
                "brown dog", "fluffy brown dog" }),
        "say " + "@@ask_sleeper|dog@@", 1);
    add_ask( ({ "carlsan", "town crier", "crier" }),
        "say " + "@@ask_sleeper|myself@@", 1);
    add_ask( ({ "sign", "signs", "survey", "participate",
                "paper", "papers", "form", "forms",
                "survey form", "survey forms" }),
        "say " + "@@ask_sleeper|signs@@", 1);
    add_ask( ({ "chadwick", "chadwick fountaine", "son", "family" }),
        "say " + "@@ask_sleeper|son@@", 1);
    add_ask( ({ "time" }),
        "say " + "@@ask_sleeper|time@@", 1);
    add_ask( ({ "genesis", "donut", "realm" }),
        "say " + "@@ask_sleeper|genesis@@", 1);
    add_ask( ({ "oat", "oats", "creamed oats", "food",
                "favorite food", "favourite food", "inn",
                "silver swan", "silver swan inn" }),
        "say " + "@@ask_sleeper|oats@@", 1);
    add_ask( ({ "drink", "brew", "special brew", "alcohol", "pub",
                "local pub", "bar", "saloon", "sparkle pub" }),
        "say " + "@@ask_sleeper|drink@@", 1);
    add_ask( ({ "dock", "docks", "genesis shiplines", "ships",
                "ship", "vessels", "genesis shiplines sign",
                "genesis shipline signs", "genesis shiplines company" }),
        "say " + "@@ask_sleeper|docks@@", 1);
    add_ask( ({ "orb", "orbs", "quest orb", "quest orbs" }),
        "say " + "@@ask_sleeper|orbs@@", 1);
    add_ask( ({ "tower", "tower of realms" }),
        "say " + "@@ask_sleeper|tower@@", 1);
    add_ask( ({ "calia", "lands of calia" }),
        "say " + "@@ask_sleeper|calia@@", 1);
    add_ask( ({ "gelan", "city of gelan" }),
        "say " + "@@ask_sleeper|gelan@@", 1);
    add_ask( ({ "xania", "xorfin", "cadet", "cadets",
                "cadet guild", "cadets guild",
                "academy", "academics",
                "academics guild", "school" }),
        "say " + "@@ask_sleeper|cadet@@", 1);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    setuid();
    seteuid(getuid());
} /* create_sparkle_npc */   



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
        "say " + "@@ask_sleeper|sparkle@@", 1);
    add_ask( ({ "job", "occupation", "work", "career" }),
        "say " + "@@ask_sleeper|job@@", 1);
    add_ask( ( Swear_Words ),
        "say " + "@@ask_sleeper|cuss@@", 1);
        
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
        awake_check();
        command("emote looks a bit confused.");
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
    string      question = query_question();

    if (strlen(question))
    {
        write_file(LOG_DIR + "crier_asks", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " questions the town crier: '"+
            ((question != OrigQuestion) ? OrigQuestion+"' -> '" : "")+
                question+"'\n");
    }

    command("say " + ask_sleeper("no_info"));
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
    awake_check();

    command("say Oh ... er ... hello again, " + who->query_name() + "!");
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
    awake_check();
    command("peer defiantly");
    command("say I'm not moving from my post!");

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

    arm = clone_object("/d/Sparkle/area/orc_temple/wep/crude_dagger");
    arm->set_name("pencil");
    arm->set_short("trusty pencil");
    arm->set_adj( ({ "trusty" }) );
    arm->set_long("This pencil looks like it has been very well used.\n");
    arm->move(this_object());

    awake_check();

    command("wield all");
} /* arm_me */


/*
 * Function name:       alert_hour_change_hook
 * Description  :       This function gets called whenever the hour
 *                      hour changes in the City of Sparkle
 *                      NPCs can use this to act upon the hour,
 *                      to provide the semblance of a daily routine.
 *                      In the case of the enchanter, we use this to
 *                      trigger his acts, rather than using add_act().
 * Arguments    :       hour - current hour in Sparkle time
 */
public void
alert_hour_change_hook(int hour)
{
    /* Make sure the dog is in place */
    check_dog();

    if (is_busy())
    {
        /* Don't participate in routines when interacting. */
        return;
    }

    if (!random(3))
    {
        if (!Awake)
        {
            command(one_of_list(Asleep_Acts));
        }
        else if (Awake == 1)
        {
            trigger_sleep();
        }
        else
        {
            command(one_of_list(Awake_Acts));
            Awake--;
        }

        return;
    }

    if (!Awake ||
        random(2))
    {
        return;
    }

    update_poster();
    return;

} /* alert_hour_change_hook */


/*
 * function name: show_hook
 * description  : this hook is called whenever an item is 'shown' to this
 *                living. It is shown by this_player().
 * arguments    : object ob - the object shown.
 */
public void
show_hook(object ob)
{
    awake_check();

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
    object    reward;

    awake_check();
    intro_check(to);

    if (obj->id("_sparkle_tour_food"))
    {
        command("say Ahhh ... those smell just delicious! If you want to"
          + " <give> them to me, I'd be happy to take them off your"
          + " hands.");
        command("smile hope");
        return;
    }

    if (obj->id("_sparkle_tour_quest_drink"))
    {
        command("say Oooo! You gonna drink that? If not, you could certainly"
          + " <give> it to me, and I'll show you how it's done!");
        command("smile hope");
        return;
    }

    if (obj->id(RATING_FORM))
    {
        if (to->test_bit("Sparkle",
                CITY_TOUR_SIGN_GROUP,
                CITY_TOUR_SIGN_BIT))
        {
            command("say Hmmm ... you've already filled out a survey. It"
              + " might skew the results to have you fill out another. Here,"
              + " I'd better take that.");
            command("emote takes the form and feeds it to his dog.");
            obj->remove_object();
            return;
        }

        if (to->query_prop(SPARKLE_TOUR_PROP) != "sign_rating")
        {
            command("say How did you get one of those?! I'm the only one"
              + " who is supposed to be handing them out! Here, I need to"
              + " take that.");
            command("emote takes the form and feeds it to his dog.");
            obj->remove_object();
            return;
        }

        if (!obj->finished_form())
        {
            command("say Ah, how are the ratings coming? Looks like you"
              + " still need to complete the form. Be sure to <read> it"
              + " and follow the instructions carefully.");
            return;
        }

        command("say Oh, look! You've finished filling out the form! If"
          + " you feel you are ready, you can <submit> it to me now. But"
          + " if you want to change any of your scores, you can do that"
          + " too.");
        return;
    }

    if (obj->id(SCRUB_BRUSH))
    {
        if (to->test_bit("Sparkle",
                CITY_TOUR_DOCK_GROUP,
                CITY_TOUR_DOCK_BIT))
        {
            command("say Hmmm ... if I recall, you have already done"
              + " your fair share of cleaning those blasted signs. No"
              + " reason to have you slave over it any more.");
            command("emote takes the brush and tucks it away.");
            obj->remove_object();
            return;
        }

        if (to->query_prop(SPARKLE_TOUR_PROP) != "tour_docks")
        {
            command("say Who gave you that? The gnomes are very particular"
              + " about the tools used to clean their signs, so I'd better"
              + " take that.");
            command("emote takes the brush and tucks it away.");
            obj->remove_object();
            return;
        }

        command("say Oh, how have you done? Quick, Pookie! Go see if"
          + " all the signs look clean!");

        BLANK_SPACE; /* for player readability */

        tell_room(environment(this_object()), "The fluffy brown dog"
          + " bounds out of the room heading east toward the docks.\n");

        BLANK_SPACE; /* for player readability */

        if (!obj->finished_task())
        {
            tell_room(environment(this_object()), "After a minute"
              + " she returns and whimpers crossly.\n");

            BLANK_SPACE; /* for player readability */

            command("say Oh dear. It looks as if Pookie found a few"
              + " signs along the docks that still look pretty scummy."
              + " You'll need to carefully <read> each sign on the"
              + " docks and <scrub> any of them on which you see"
              + " that blasted scum!");
            return;
        }

        tell_room(environment(this_object()), "After a minute she returns"
          + " and barks happily.\n");

        BLANK_SPACE; /* for player readability */

        command("say Really, girl? All of them cleaned up? Oh, that is"
          + " just great news! Here, you have earned this!");

        BLANK_SPACE; /* for player readability */

        reward = MONEY_MAKE_GC(5);
        reward->move(this_object());
        command("give coins to " + OB_NAME(to));

        if (environment(reward) == this_object())
        {
           command("drop coins");
        }

        command("emote takes the brush and tucks it away.");
        obj->remove_object();

        BLANK_SPACE; /* for player readability */

        give_reward(to,
                        CITY_TOUR_DOCK_GROUP,
                        CITY_TOUR_DOCK_BIT,
                        CITY_TOUR_DOCK_EXP,
                        "tour_dock");  

        check_remaining_tours(to);
        return;
    }

    if (obj->id(FEATHER_DUSTER))
    {
        if (to->test_bit("Sparkle",
                CITY_TOUR_ORBS_GROUP,
                CITY_TOUR_ORBS_BIT))
        {
            command("say Hmmm ... if I recall, you have already done"
              + " your fair share of dusting all those orbs. No"
              + " reason to have you slave over it any more.");
            command("emote takes the feather duster and tucks it away.");
            obj->remove_object();
            return;
        }

        if (to->query_prop(SPARKLE_TOUR_PROP) != "tour_orbs")
        {
            command("say Who gave you that? That is my special tool"
              + " to be used when I am ... er, or someone I've asked to"
              + " help me is ... busy dusting the quest orbs!");
            command("emote takes the feather duster and tucks it away.");
            obj->remove_object();
            return;
        }

        command("say Oh, did you finish up? Quick, Pookie! Go see if"
          + " all the orbs are free of dust!");

        BLANK_SPACE; /* for player readability */

        tell_room(environment(this_object()), "The fluffy brown dog"
          + " bounds out of the room heading east toward the tower.\n");

        BLANK_SPACE; /* for player readability */

        if (!obj->finished_task())
        {
            tell_room(environment(this_object()), "After a minute"
              + " she returns and whimpers crossly.\n");

            BLANK_SPACE; /* for player readability */

            command("say Oh dear. It looks as if Pookie found a few"
              + " orbs that still looked rather dusty."
              + " You'll need to make sure to <dust> each orb in the"
              + " tower to make sure they are all clean.");
            return;
        }

        tell_room(environment(this_object()), "After a minute she returns"
          + " and barks happily.\n");

        BLANK_SPACE; /* for player readability */

        command("say Is that so? Each one nicely dusted? Oh, what a huge"
          + " relief! Here, you're just so much help!");

        BLANK_SPACE; /* for player readability */

        reward = MONEY_MAKE_GC(5);
        reward->move(this_object());
        command("give coins to " + OB_NAME(to));

        if (environment(reward) == this_object())
        {
           command("drop coins");
        }

        command("emote takes the feather duster and tucks it away.");
        obj->remove_object();

        BLANK_SPACE; /* for player readability */

        give_reward(to,
                        CITY_TOUR_ORBS_GROUP,
                        CITY_TOUR_ORBS_BIT,
                        CITY_TOUR_ORBS_EXP,
                        "tour_orbs");  

        check_remaining_tours(to);

        return;
    }

    command("say I haven't got much to tell you about that, I'm afraid.");
    return;
} /* react_items */ 


/*
 * Function name:        init_living
 * Description  :        set up some actions for the players who
 *                       enter the room
 */
public void
init_living()
{
    ::init_living();

    add_action(do_wake, "wake");
} /* init_living */


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
    object  reward;

    awake_check();

    if (obj->id("coin"))
    {
        command("say Oh, that's very kind of you! But you go ahead and"
          + " keep it. I make an honest living.");
    }
    else if (obj->id("_sparkle_tour_food"))
    {
        if (to->test_bit("Sparkle",
            CITY_TOUR_FOOD_GROUP,
            CITY_TOUR_FOOD_BIT))
        {
            command("say Oh my, I do love these! Thank you so much for"
              + " remembering!");
            set_stuffed(0);
            command("eat oatses");
            set_alarm(0.0, 0.0, &command("drop oatses"));
            return;
        }

        if (to->query_prop(SPARKLE_TOUR_PROP) != "get_food")
        {
            command("say Why, the creamed oats from the Silver Swan Inn!"
              + " Oh, I just love these, thank you!");
            set_stuffed(0);
            command("eat oatses");
            set_alarm(0.0, 0.0, &command("drop oatses"));
            return;
        }

        BLANK_SPACE; /* for player readability */

        command("say Oh, you found the Inn, and what is more, you've"
          + " brought me my favorite treat! Here, please take this for"
          + " your trouble.");

        BLANK_SPACE; /* for player readability */

        reward = MONEY_MAKE_GC(1);
        reward->move(this_object());
        command("give coins to " + OB_NAME(to));

        if (environment(reward) == this_object())
        {
           command("drop coins");
        }

        BLANK_SPACE; /* for player readability */

        give_reward(to,
                        CITY_TOUR_FOOD_GROUP,
                        CITY_TOUR_FOOD_BIT,
                        CITY_TOUR_FOOD_EXP,
                        "tour_food");  

        BLANK_SPACE; /* for player readability */

        to->remove_prop(SPARKLE_TOUR_PROP);

        command("say You should be sure to keep yourself well fed, because"
          + " it prevents you from getting tired out too quickly. Now, if"
          + " you don't mind ...");
        set_stuffed(0);
        command("eat oatses");
        set_alarm(0.0, 0.0, &command("drop oatses"));

        BLANK_SPACE; /* for player readability */

        check_remaining_tours(to);
        return;
    }
    else if (obj->id("_sparkle_tour_quest_drink"))
    {
        if (to->test_bit("Sparkle",
            CITY_TOUR_DRINK_GROUP,
            CITY_TOUR_DRINK_BIT))
        {
            command("say Ho ho! You can never get enough of these! Thanks,"
              + " again mate, you're a life-saver!");
            set_soaked(0);
            command("drink brews");
            set_alarm(0.0, 0.0, &command("drop brews"));
            return;
        }

        if (to->query_prop(SPARKLE_TOUR_PROP) != "get_drink")
        {
            command("say Well, look'ee here, its one of my favorite"
              + " beverages in all of Genesis! You're a life-saver!");
            set_soaked(0);
            command("drink brews");
            set_alarm(0.0, 0.0, &command("drop brews"));
            return;
        }

        BLANK_SPACE; /* for player readability */

        command("say Well, you did it! Found the pub and bought me the"
          + " finest beverage a man could ever want! Here's a coin for"
          + " your trouble, but you'll feel a bit more experienced, I'll"
          + " wager!");

        BLANK_SPACE; /* for player readability */

        reward = MONEY_MAKE_GC(1);
        reward->move(this_object());
        command("give coins to " + OB_NAME(to));

        if (environment(reward) == this_object())
        {
           command("drop coins");
        }

        BLANK_SPACE; /* for player readability */

        give_reward(to,
                        CITY_TOUR_DRINK_GROUP,
                        CITY_TOUR_DRINK_BIT,
                        CITY_TOUR_DRINK_EXP,
                        "tour_drink");  

        BLANK_SPACE; /* for player readability */

        to->remove_prop(SPARKLE_TOUR_PROP);

        command("say I tell you, if you ever find yourself low on health,"
          + " drinking yourself silly is the surest way back to feeling"
          + " fit as a fiddle! Speaking of which ...");
        set_soaked(0);
        command("drink brews");
        command("burp");
        set_alarm(0.0, 0.0, &command("drop brews"));

        BLANK_SPACE; /* for player readability */

        check_remaining_tours(to);
        return;
    }
    else
    {
        command("say You go ahead and keep that.");
    }
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
        awake_check();

        command("say Oh hello! Maybe we haven't met before!");
        command("introduce myself");
    }
}


/*
 * Function name:        ask_sleeper
 * Description  :        The guy is always falling asleep. So, we first
 *                       have to make sure he is awake.
 * Arguments    :        string question - the subject of the ask
 * Returns      :        The response
 */
public string
ask_sleeper(string question)
{
    awake_check();
    intro_check(this_player());

    switch(question)
    {
        default:
        case "no_info":
            command(one_of_list( ({ "think", "confused", "hmm" }) ));
            return(one_of_list( ({
                "Don't know much about that, I'm afraid.",
                "Wish I could help you there.",
                "Err ... I'm no help to you on that, I guess.",
                "Maybe you'll find someone else who knows about that.",
                }) ));
            break;
        case "tasks":
            return check_tours(this_player());
            break;
        case "poster":
            update_poster();
            command("smile proud");
            return "Yes, please read my poster! I keep it very up-to-date.";
            break;
        case "dungeon":
            return "You'd want to go ask the Enchanter about that. He is"
              + " just down the street to the west and then north up by"
              + " the Post Office. You can <exa> your magic map to find"
              + " him easily.";
            break;
        case "orcs":
            return "I hate them! They keep attacking our city!";
            break;
        case "reward":
            switch(this_player()->query_prop(SPARKLE_TOUR_PROP))
            {
                case "sign_rating":
                    return "You'll need to complete your sign rating"
                      + " form before I can give you a reward. Just"
                      + " <read form> and follow the instructions.";
                    break;
                default:
                    return "Reward? For what? Did you perhaps want to"
                      + " try helping me with a task or some kind? If"
                      + " so, just <ask> me about tasks.";
                    break;
            }
            break;
        case "sparkle":
            return "Oh, Sparkle is a wonderful city. I've lived here all" 
              + " of my life! You can <exa> your magic map to get a"
              + " feel for it.";
            break;
        case "job":
            return "Why, I'm the Town Crier!";
            break;
        case "cuss":
            return "Cussing isn't going to get you very far with me!";
            break;
        case "map":
            if (!present("_sparkle_magic_map", this_player()))
            {
                command("say Pookie! Give this fine "
                  + this_player()->query_race_name() + " a magic map!");
                Dog->give_map(this_player());
            }

            return "The magic map is one of the most useful things in all"
              + " of Genesis! Just <exa map> wherever you are, and if the"
              + " wizards have done their job, you can see your location"
              + " on the map.";
            break;    
        case "dog":
            command("say Oh, isn't she sweet. I wish she were a bit more"
              + " alert, though ... she tends to take naps!");
            Dog->command("rolleyes");
            return "";
            break;  
        case "church":
            return "The church staff were nice enough to let me set my table"
              + " up right here before their doorstep.";
            break;
        case "myself":
            command("eyebrow");
            return "Why, that's me!";
            break;    
        case "signs":
            return "Oh, I'm giving out a survey about the signs around the"
              + " city! Anyone who is interested can <ask> me about"
              + " tasks to participate.";
            break;
        case "son":
            return "Chadwick, my son, is the only family I have. I am"
              + " so proud of him!";
            break;
        case "time":
            return "Oh, you can check yourself! Just type <time> in most"
              + " places in the realm, and if you are out of doors, you"
              + " will be able to tell from the sky what time it is in"
              + " the local region. I've heard that the gnomes have"
              + " come up with some fancy device to keep track of it"
              + " all, too.";
            break;
        case "genesis":
            return "Genesis, the donut we inhabit, has been floating"
              + " around in the oven of the Maker for quite a while"
              + " now. You can know more with <help history>.";
            break;
        case "oats":
            return "The creamed oats from the Silver Swan Inn are simply"
              + " the best food in town!";
        case "drink":
            return "The special brew they pour over at the pub is the best"
              + " stuff served in Sparkle!";
            break;
        case "docks":
            return "Just east of hear you'll find the docks where all"
              + " of the vessels controlled by the Genesis Shiplines"
              + " Company come to port.";
            break;
        case "orbs":
            return "The Tower of Realms, just a bit east along this"
              + " very street contains all of the quest orbs. They are"
              + " extremely useful in helping you know what quests"
              + " exist in Genesis, and where they can be found!";
            break;
        case "tower":
            return "The Tower of Realms is just to the east of here"
              + " along the south side of the road. You can find it"
              + " if you <exa map> to see it on your magic map.";
            break;
        case "calia":
            return "Calia is one of the many lands in Genesis you can"
              + " visit via the GSL Shiplines. Go east to the pier and"
              + " read the signs. I'm sure you'll find a few that go"
              + " to Calia.";
            break;
        case "gelan":
            return "Gelan is the main city in the lands of Calia. I"
              + " recommend that young people visit Gelan and pay a"
              + " visit to the school there to learn about the"
              + " Cadets and the Academics Guilds.";
            break;
        case "cadet":
            return "It is at the school in Gelan where Xania and Xorfin"
              + " preside over the learning of people who join the"
              + " Cadets or the Academics guilds. I highly recommend"
              + " joining these guilds to all new travellers to Genesis!";
            break;
    }

    /* Should never happen, but just in case. */
    return "What? Sorry, I seem to be confused.";
} /* ask_sleeper */


/*
 * Function name:        awake_check
 * Description  :        Wake the guy up if he's asleep
 * Arguments    :        int dog_woken - true by default. indicates that
 *                                       the npc is woken by the dog.
 */
public void
awake_check(int dog_woke = 1)
{
    check_dog();

    if (Awake)
    {   
        /* Any interaction from a player renews his wakefulness. */
        Awake = 2;
        return;
    }

    if (dog_woke)
    {
        Dog->bark();
    }

    command(one_of_list(Wake_Up));
    Awake = 2;

    return;
} /* awake_check */


/*
 * Function name:        describe
 * Description  :        Provide a state-dependant description of the
 *                       npc
 * Returns      :        string - the description
 */
public string
describe()
{
    return "Here sits the town crier of Sparkle. To look at him, though,"
      + " it would seem that \"town snorer\" might be a more fitting"
      + " title. He is resting comfortably behind a large table that is"
      + " positioned beside the entrance to the church, surrounded by"
      + " many official looking forms and other papers. A large poster"
      + " stands near him on top of the table, and you notice a fluffy brown"
      + " dog at his side regarding you with keen interest.\n"
      + "---------------------------------------------------------"
      + "------------\n"
      + "You sense that you could <ask> him about tasks he may need"
      + " help with.\n"
      + "---------------------------------------------------------"
      + "------------\n"
      + ((Awake) ? "" : "He is currently fast asleep.\n");
} /* describe */


/*
 * Function name:        check_dog
 * Description  :        Make sure his dog is here.
 */
public void
check_dog()
{
    if (!environment(this_object()))
    {
        return;
    }

    if (!objectp(Dog = present(CRIER_DOG, environment(this_object()))))
    {
        Dog = clone_object(NPC_DIR + "dog");
        Dog->move(environment(this_object()));
    }
} /* check_dog */


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
 * We are masking this hook to allow players to wake Carlsan up with
 * emotes that make contact.
 */
public void
emote_hook(string emote, object actor, string adverb, object *oblist,     
           int cmd_attr, int target)
{
    string  asleep_txt;

    if (ACTION_CONTACT & cmd_attr)
    {
        awake_check(0);
    }
    else if ((ACTION_AURAL & cmd_attr) &&
        IN_ARRAY(this_object(), oblist))
    {
        awake_check(0);
    }
    else if (!Awake)
    {
        if (IN_ARRAY(this_object(), oblist))
        {
            command("emote " + one_of_list( ({
                " is sound asleep, so he doesn't notice.",
                " snores loudly in response.",
                " appears not to have noticed as he is fast asleep.",
                " merely snores, completely oblivious to what is going on.",
                " keeps right on sleeping.",
                " isn't awake, and doesn't notice." }) ));
        }

        return;
    }

    if (ACTION_OFFENSIVE & cmd_attr)
    {
        react_rudeness();
    }

    if (ACTION_INTIMATE & cmd_attr)
    {
        react_freshness();
    }
} /* emote_hook */


/*
 * Function name:        react_rudeness
 * Description  :        We'll give him some likely responses to rude
 *                       behavior
 */
public void
react_rudeness()
{
    if (!random(3))
    {
        command(one_of_list( ({ "ack", "gasp", "blink", "glare" }) ));
    }

    command(one_of_list( ({
        "say What the?! Who taught you your manners?",
        "say Well, I never ... !",
        "say Oh, for the ... I've never seen such behavior!",
        "say You take that sort of nonsense elsewhere!",
        "say Of all the ... quit behaving like a fool!",
        "say Heavens! Someone ought to teach you a lesson!",
        "say By the Devil! You stop that!",
        "say Why, I oughta ... (mumble, mutter, mumble ...)",
        "say I fed the last person who did that to Pookie, you scumbag!",
        "say If I wasn't in a good mood, you'd be in trouble!",
        "say Hey! Are you lookin' for a teatime with Lars?",
        "say Of all the nerve!",
        }) ));
} /* react_rudeness */


/*
 * Function name:        react_freshness
 * Description  :        We'll give him some likely responses to fresh
 *                       behavior
 */
public void
react_freshness()
{
    if (!random(3))
    {
        command(one_of_list( ({ "ack", "swallow", "blink", "blush" }) ));
    }

    command(one_of_list( ({
        "say I'm a married man!",
        "say If you please!",
        "say I'll thank you to take your affections elsewhere.",
        "say Errr ...",
        "say That will be enough of that, thank you very much!",
        }) ));
} /* react_freshness */


/*
 * Function name:        exa_poster
 * Description  :        This is the poster that the Town Crier uses to
 *                       do his job so he can sleep.
 * Returns      :        string - the readout
 */
public string
exa_poster()
{
    string  time_message = 
                sprintf("%|30s", Time_Readout + " O'Clock and All's Well!");


    VENDOR->set_info(QUEST_FILE(this_player()->query_real_name()),
        "crier_seen", "yes");

    return
        "  .-----------------------------------------------------------------.\n"
      + " |                                                                   |\n"
      + " |        ====================================================       |\n"
      + " |                  " + time_message + "                   |\n"
      + " |        ====================================================       |\n"
      + " |                                                                   |\n"
      + " |  Hello there, visitor, citizen, or what-have-you!                 |\n"
      + " |                                                                   |\n"
      + " |  It is my job to greet people as they come into town, and I am    |\n"
      + " |  quite happy to offer any would-be-tourists some small tasks      |\n"
      + " |  which will not only help familiarize them with the city and      |\n"
      + " |  give them some experience, but also help out a bit around town.  |\n"
      + " |                                                                   |\n"
      + " |  If you wish to begin a tour, just <ask carlsan task> and I'll    |\n"
      + " |  get you started right away. Oh, and if I appear to be asleep,    |\n"
      + " |  I am merely resting my eyes.                                     |\n"
      + " |                                                                   |\n"
      + " |  Yours truly,                                                     |\n"
      + " |  Carlsan Fountaine, Town Crier                                    |\n"
      + " |                                                                   |\n"
      + "  `-----------------------------------------------------------------'\n";
} /* exa_poster */


/*
 * Function name:        do_wake
 * Description  :        Allow players to try to wake him
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_wake(string arg)
{
    int  align;

    if (!strlen(arg))
    {
        notify_fail("Whom do you wish to wake?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [large] [sleepy] [sleeping] [town] 'man' / 'human'"
      + " / 'carlsan' / 'crier' [up]"))
    {
        notify_fail("Are you trying to wake up the town crier, perhaps?\n");
        return 0;
    }

    if (Awake)
    {
        notify_fail("But he isn't asleep!\n");
        return 0;
    }

    align = this_player()->query_alignment();

    if (align < -619)
    {
        write("You give the table a swift kick, causing it to fly up and"
          + " smash " + this_object()->query_the_name(this_player())
          + " in the face!\n");
        tell_room(environment(this_object()), QCTNAME(this_player())
          + " delivers a swift kick to the table, causing it to fly up"
          + " and smash " + QTNAME(this_object()) + " in the face!\n",
            this_player());
    }
    else if (align > 549)
    {
        write("You gently rustle "
          + this_object()->query_the_name(this_player()) + " by the"
          + " shoulders.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())
          + " gently rustles " + QTNAME(this_object()) + " by the"
          + " shoulders.\n",
            this_player());
    }
    else
    {
        write("You rap your knuckles a few times on the table, jiggling it"
          + " just enough to disturb " 
          + this_object()->query_the_name(this_player()) + " a bit.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())
          + " raps " + this_player()->query_possessive() + " knuckles on"
          + " the table, jiggling it just enough to disturb "
          + QTNAME(this_object()) + " a bit.\n",
            this_player());
    }

    awake_check(0);
    return 1;
} /* do_wake */


/*
 * Function name:        trigger_sleep
 * Description  :        He falls asleep
 */
public void
trigger_sleep()
{
    command(one_of_list(Go_To_Sleep));
    Awake = 0;
} /* trigger_sleep */


/*
 * Function name:        survey_results
 * Description  :        Show the player the results of the sign rating
 *                       surveys
 * Returns      :        string - the description
 */
public string
survey_results()
{
    if (!objectp(Form))
    {
        Form = clone_object(OBJ_DIR + "sign_form");
    }

    return Form->display_ratings();
} /* survey_results */


/*
 * Function name:        check_tours
 * Description  :        see what tours, if any, the player has that
 *                       remain incomplete and give them that task.
 * Arguments    :        object who - the player
 * Returns      :        string - what he will say
 */
public string
check_tours(object who)
{
    object  s_form;

    BLANK_SPACE; /* for player readability */

    if (!this_player()->test_bit("Sparkle",
            CITY_TOUR_SIGN_GROUP,
            CITY_TOUR_SIGN_BIT))
    {   
        if (this_player()->query_prop(SPARKLE_TOUR_PROP) == "sign_rating")
        {
            if (!present(RATING_FORM, who))
            {
                s_form = clone_object(OBJ_DIR + "sign_form");
                s_form->move(who);

                command("say Oh, did you lose your form somehow?");
                BLANK_SPACE; /* for player readability */

                write(this_object()->query_The_name(who) + " gives you a sign"
                  + " rating form.\n");
                tell_room(environment(this_object()), QCTNAME(this_object())
                  + " gives a sign rating form to " 
                  + QTNAME(who) + ".\n", who);
                BLANK_SPACE; /* for player readability */
            }

            return "Please <read form>, and when you have"
              + " finished filling it out, return to me and <submit> it for a"
              + " reward. You can <exa map> to see where in town the various"
              + " signs are located. Make sure you are standing in the street"
              + " when you try to <read> a given sign.";
        }

        TELL_G(capitalize("\n\n\t" + who->query_name()) + " begins the sign rating"
          + " quest! --**--*--**--*--\n");

        command("say Sparkle has been undergoing a lot of renovations"
          + " in recent years, and a lot of local people have found"
          + " good paying jobs as a result. Just look at me, for example!");
        BLANK_SPACE; /* for player readability */
        command("say My son, too, has been hired by the Sparkle Magistrate"
          + " to create signs for all the local businesses. He is just"
          + " fantastic with wood and paint!");
        BLANK_SPACE; /* for player readability */
        command("say I keep telling him that his signs are great, but he"
          + " is a perfectionist. Because I'm the Town Crier, he has asked"
          + " me to pay people to fill out a survey about the merits of"
          + " each of the signs he has created. Here, please take this"
          + " survey form!");
        BLANK_SPACE; /* for player readability */
        s_form = clone_object(OBJ_DIR + "sign_form");
        s_form->move(who);
        write(this_object()->query_The_name(who) + " gives you a sign"
          + " rating form.\n");
        tell_room(environment(this_object()), QCTNAME(this_object())
          + " gives a sign rating form to " + QTNAME(who) + ".\n", who);
        BLANK_SPACE; /* for player readability */
        command("say Please <read form>, and when you have finished"
          + " filling it out, return to me and <submit> it for a"
          + " reward. You can <exa map> to see where in town the various"
          + " signs are located. Make sure you are standing in the street"
          + " when you try to <read> a given sign.");
        BLANK_SPACE; /* for player readability */

        write_file(LOG_DIR + "quest_begin", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " began the sign rating quest.\n");

        this_player()->add_prop(SPARKLE_TOUR_PROP, "sign_rating");
        return "";
    }

    if (!this_player()->test_bit("Sparkle",
            CITY_TOUR_FOOD_GROUP,
            CITY_TOUR_FOOD_BIT))
    {
        if (this_player()->query_prop(SPARKLE_TOUR_PROP) == "get_food")
        {
            return "Oh, have you managed to find the Inn yet and buy me"
              + " some of those delicious creamed oats? If so, please"
              + " <give> them to me! If not, please <exa map> so you can"
              + " see where to find the Inn.";
        }

        TELL_G(capitalize("\n\n\t" + who->query_name()) + " begins the food"
          + " tour! --**--*--**--*--\n");

        command("say Lords, but I am hungry! You know, perhaps you could"
          + " do me a favor.");
        BLANK_SPACE; /* for player readability */
        command("say Have you noticed that Sparkle has an Inn? We"
          + " were all very pleasantly surprised when that elvish fellow"
          + " arrived from Emerald and decided to make our city his home.");
        BLANK_SPACE; /* for player readability */
        command("say It really is a beautiful Inn, but I must tell you, the"
          + " food they serve is the interesting part! I can't usually"
          + " afford the more pricey stuff, but they have these creamed"
          + " oats that aren't too expensive, and they are just delicious!");
        BLANK_SPACE; /* for player readability */
        command("say If you have time, please go visit the Inn, and"
          + " when you are there <read> their menu and <buy> me some of"
          + " those creamed oats. Then return and <give> them to me, and"
          + " I'll be so grateful! You can <exa> your magic map if you"
          + " need help locating the place. It is just up near the"
          + " Post Office.");
        BLANK_SPACE; /* for player readability */

        write_file(LOG_DIR + "quest_begin", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " began the Sparkle Food Tour quest.\n");

        this_player()->add_prop(SPARKLE_TOUR_PROP, "get_food");
        return "";
    }

    if (!this_player()->test_bit("Sparkle",
            CITY_TOUR_DRINK_GROUP,
            CITY_TOUR_DRINK_BIT))
    {
        if (this_player()->query_prop(SPARKLE_TOUR_PROP) == "get_drink")
        {
            return "Oh, did you make it over to the pub yet? If so, did"
              + " you happen to pick me up one of their special brews?"
              + " Just <give> it to me, and I'll make it worth"
              + " your while! If you're having trouble finding the pub,"
              + " head east from here until you hit the docks, and"
              + " then <exa map> to see where it is located.";
        }

        TELL_G(capitalize("\n\n\t" + who->query_name()) + " begins the drink"
          + " tour! --**--*--**--*--\n");

        command("say All of this Town Crier work has my mouth just as"
          + " dry as a desert dust devil!");
        BLANK_SPACE; /* for player readability */
        command("say I'm not sure if you've traveled over by the docks"
          + " yet, but if so perhaps you've noticed our local pub?");
        BLANK_SPACE; /* for player readability */
        command("say The barkeep is a bit particular about things, but"
          + " they serve some fine drinks! Much better than the Elvish"
          + " stuff at the Inn.");
        BLANK_SPACE; /* for player readability */
        command("say If you have time, please head over to the pub, and"
          + " <buy> me one of their special brews. You'll have to head"
          + " east from here until you get to the docks. Once you do,"
          + " you can <exa map> to see where the pub is located. If the"
          + " barkeep isn't around just <ring> the bell and they'll show"
          + " up before long.");
        BLANK_SPACE; /* for player readability */

        write_file(LOG_DIR + "quest_begin", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " began the Sparkle Drink Tour quest.\n");

        this_player()->add_prop(SPARKLE_TOUR_PROP, "get_drink");
        return "";
    }

    if (!this_player()->test_bit("Sparkle",
            CITY_TOUR_DOCK_GROUP,
            CITY_TOUR_DOCK_BIT))
    {   
        if (this_player()->query_prop(SPARKLE_TOUR_PROP) == "tour_docks")
        {
            if (!present(SCRUB_BRUSH, who))
            {
                s_form = clone_object(OBJ_DIR + "scrub_brush");
                s_form->move(who);

                command("say Oh, did you lose your scrub-brush somehow?");
                BLANK_SPACE; /* for player readability */

                write(this_object()->query_The_name(who) + " gives you a"
                  + " sturdy scrub-brush.\n");
                tell_room(environment(this_object()), QCTNAME(this_object())
                  + " gives a sturdy scrub-brush to " 
                  + QTNAME(who) + ".\n", who);
                BLANK_SPACE; /* for player readability */
            }

            return "Please go visit the docks east of here and <read>"
              + " each of the Genesis ShipLines signs you find there."
              + " Using your brush, <scrub> any of them that you find"
              + " are covered with any scum, and then return to me and"
              + " <show> me the brush.";
        }

        TELL_G(capitalize("\n\n\t" + who->query_name()) + " begins the dock"
          + " quest! --**--*--**--*--\n");

        command("say Sparkle has been enjoying its status as the Hub"
          + " of Genesis, and we have our faithful Genesis ShipLines"
          + " Company to thank for it!");
        BLANK_SPACE; /* for player readability */
        command("say The gnomes who run the operation, however, are too"
          + " busy with constant repairs to their vessels to have time"
          + " to maintain the signs that they use to advertise their"
          + " various travel lines here in Sparkle.");
        BLANK_SPACE; /* for player readability */
        command("say Here, please take this scrub-brush.");
        BLANK_SPACE; /* for player readability */
        s_form = clone_object(OBJ_DIR + "scrub_brush");
        s_form->move(who);
        write(this_object()->query_The_name(who) + " gives you a sturdy"
          + " scrub-brush.\n");
        tell_room(environment(this_object()), QCTNAME(this_object())
          + " gives a sturdy scrub-brush to " + QTNAME(who) + ".\n", who);
        BLANK_SPACE; /* for player readability */
        command("say Please go and visit the docks east of here and"
          + " <read> each of the Genesis ShipLines signs that you find"
          + " there. Using your brush, <scrub> any of them that you find"
          + " are covered with any scum, and then return to me and"
          + " <show> me the brush when all of them are cleaned up.");
        BLANK_SPACE; /* for player readability */

        write_file(LOG_DIR + "quest_begin", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " began the dock quest.\n");

        this_player()->add_prop(SPARKLE_TOUR_PROP, "tour_docks");
        this_player()->add_prop(DOCK_TOUR_PROP, ({}));
        return "";
    }

    if (!this_player()->test_bit("Sparkle",
            CITY_TOUR_ORBS_GROUP,
            CITY_TOUR_ORBS_BIT))
    {   
        if (this_player()->query_prop(SPARKLE_TOUR_PROP) == "tour_orbs")
        {
            if (!present(FEATHER_DUSTER, who))
            {
                s_form = clone_object(OBJ_DIR + "feather_duster");
                s_form->move(who);

                command("say Oh, did you lose your feather duster somehow?");
                BLANK_SPACE; /* for player readability */

                write(this_object()->query_The_name(who) + " gives you a"
                  + " feather duster.\n");
                tell_room(environment(this_object()), QCTNAME(this_object())
                  + " gives a feather duster to " 
                  + QTNAME(who) + ".\n", who);
                BLANK_SPACE; /* for player readability */
            }

            command("say Please go <dust> the orbs in each of the rooms"
              + " within the Tower of Realms, which you can find on"
              + " your magic map. Once you've dusted them all, return"
              + " here and <show> the duster to me. I'll reward you!");
        }

        TELL_G(capitalize("\n\n\t" + who->query_name()) + " begins the orbs"
          + " quest! --**--*--**--*--\n");

        command("say You know, the help you've been giving me is the sort"
          + " of thing that counts as a quest in Genesis! Doing quests"
          + " is a great way to earn experience and advance yourself in"
          + " the world.");
        BLANK_SPACE; /* for player readability */
        command("say Just here on this street you can find the Tower of"
          + " Realms. Inside are many rooms which you can visit to see"
          + " which quests exist in the different lands of Genesis. The"
          + " orbs in the rooms display the quests, you see. You should"
          + " go and <exa> each orb! Some even contain hints as to how"
          + " to get started on the quests!");
        BLANK_SPACE; /* for player readability */
        command("say Of course, the orbs tend to get a bit dusty, and it"
          + " makes it hard for people to see into them very clearly."
          + " I'm the one who is supposed to clean them, but I keep"
          + " forgetting to do it. Maybe you can help me!");
        BLANK_SPACE; /* for player readability */
        command("say Here, please take this feather duster.");
        BLANK_SPACE; /* for player readability */
        s_form = clone_object(OBJ_DIR + "feather_duster");
        s_form->move(who);
        write(this_object()->query_The_name(who) + " gives you a feather"
          + " duster.\n");
        tell_room(environment(this_object()), QCTNAME(this_object())
          + " gives a feather duster to " + QTNAME(who) + ".\n", who);
        BLANK_SPACE; /* for player readability */
        command("say Please go <dust> the orbs in each of the rooms"
              + " within the Tower of Realms, which you can find on"
              + " your magic map. Once you've dusted them all, return"
              + " here and <show> the duster to me. I'll reward you!");
        BLANK_SPACE; /* for player readability */

        write_file(LOG_DIR + "quest_begin", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " began the orbs quest.\n");

        this_player()->add_prop(SPARKLE_TOUR_PROP, "tour_orbs");
        this_player()->add_prop(ORBS_TOUR_PROP, ({}));
        return "";
    }

    if (!this_player()->test_bit("Sparkle",
            CITY_TOUR_GUILD_GROUP,
            CITY_TOUR_GUILD_BIT))
    {   
        if (this_player()->query_prop(SPARKLE_TOUR_PROP) == "tour_guild")
        {
            if (!present(CADETS_CHECKLIST, who))
            {
                s_form = clone_object(OBJ_DIR + "cadets_checklist");
                s_form->move(who);

                command("say Oh, did you lose the document somehow?");
                BLANK_SPACE; /* for player readability */

                write(this_object()->query_The_name(who) + " gives you an"
                  + " official looking document.\n");
                tell_room(environment(this_object()), QCTNAME(this_object())
                  + " gives an official-looking document to " 
                  + QTNAME(who) + ".\n", who);
                BLANK_SPACE; /* for player readability */
            }

        command("say Please <read> the document, and then follow the"
          + " instructions upon it to get the needed signatures from"
          + " Xania and Xorfin in Gelan. I get a commission for each"
          + " of those I bring back signed to the Sparkle Magistrate!");
        return "";
        }

        TELL_G(capitalize("\n\n\t" + who->query_name()) + " begins the cadets"
          + " quest! --**--*--**--*--\n");

        command("say You've shown yourself to be very capable, my friend!"
          + " I wonder if I could give you a slightly more involved"
          + " undertaking, now.");
        BLANK_SPACE; /* for player readability */
        command("say Genesis is filled with guilds that persons such as"
          + " yourself can join up with. Guilds basically give you a way"
          + " to identify yourself with a certain class or profession,"
          + " and make you a whole lot more powerful with the skills"
          + " and abilities they teach you!");
        BLANK_SPACE; /* for player readability */
        command("say In the lands of Calia is the city of Gelan, where"
          + " you can find the Cadet's guild and the Academy. It is in"
          + " this place that I recommend all beginning adventurers"
          + " sign on to learn either the ways of magic or melee combat"
          + " by joining one of those two guilds.");
        BLANK_SPACE; /* for player readability */
        command("say Here, please take this document.");
        BLANK_SPACE; /* for player readability */
        s_form = clone_object(OBJ_DIR + "cadets_checklist");
        s_form->move(who);
        write(this_object()->query_The_name(who) + " gives you an"
          + " official-looking document.\n");
        tell_room(environment(this_object()), QCTNAME(this_object())
          + " gives an official-looking document to "
          + QTNAME(who) + ".\n", who);
        BLANK_SPACE; /* for player readability */
        command("say Please <read> the document, and then follow the"
          + " instructions upon it to get the needed signatures from"
          + " Xania and Xorfin in Gelan. I get a commission for each"
          + " of those I bring back signed to the Sparkle Magistrate!");
        BLANK_SPACE; /* for player readability */

        write_file(LOG_DIR + "quest_begin", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " began the cadets quest.\n");

        this_player()->add_prop(SPARKLE_TOUR_PROP, "tour_guild");
        return "";
    }

    if (!this_player()->test_bit("Sparkle",
            CITY_TOUR_LOCALQM_GROUP,
            CITY_TOUR_LOCALQM_BIT))
    {   
        if (this_player()->query_prop(SPARKLE_TOUR_PROP) == "tour_localqm")
        {
            if (!present(LOCAL_QM_CHECKLIST, who))
            {
                s_form = clone_object(OBJ_DIR + "local_qm_checklist");
                s_form->move(who);

                command("say Oh, did you lose the checklist somehow?");
                BLANK_SPACE; /* for player readability */

                write(this_object()->query_The_name(who) + " gives you a"
                  + " checklist.\n");
                tell_room(environment(this_object()), QCTNAME(this_object())
                  + " gives a checklist to " 
                  + QTNAME(who) + ".\n", who);
                BLANK_SPACE; /* for player readability */
            }

        command("say Please <read> the checklist, and then follow the"
          + " instructions upon it to get each of the questmasters"
          + " to check their part of the list as complete. Again, I get a"
          + " nice commission for each of these I bring back completed"
          + " to the Sparkle Magistrate!");
        return "";
        }

        TELL_G(capitalize("\n\n\t" + who->query_name()) + " begins the local"
          + " questmaster quest! --**--*--**--*--\n");

        command("say Seems like you're ready to move on to bigger and"
          + " better things, now.");
        BLANK_SPACE; /* for player readability */
        command("say Here in and around Sparkle, you'll find a number"
          + " of people who can give out lots of quests just like I"
          + " have done. In fact, you can do a lot of good for the"
          + " lands of Genesis by finding and helping such people!");
        BLANK_SPACE; /* for player readability */
        command("say I've got a list of people who need help, and who"
          + " can reward you like I have if you help them out.");
        BLANK_SPACE; /* for player readability */
        command("say Here, please take this checklist.");
        BLANK_SPACE; /* for player readability */
        s_form = clone_object(OBJ_DIR + "local_qm_checklist");
        s_form->move(who);
        write(this_object()->query_The_name(who) + " gives you a"
          + " checklist.\n");
        tell_room(environment(this_object()), QCTNAME(this_object())
          + " gives a checklist to "
          + QTNAME(who) + ".\n", who);
        BLANK_SPACE; /* for player readability */
        command("say Please <read> the checklist, and then follow the"
          + " instructions upon it to get each of the questmasters"
          + " to check their part of the list as complete. Again, I get a"
          + " nice commission for each of these I bring back completed"
          + " to the Sparkle Magistrate!");
        BLANK_SPACE; /* for player readability */

        write_file(LOG_DIR + "quest_begin", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " began the local questmaster quest.\n");

        this_player()->add_prop(SPARKLE_TOUR_PROP, "tour_localqm");
        return "";
    }

    check_remaining_tours(this_player());
    return "";
} /* check_tours */


/*
 * Function name:        react_form
 * Description  :        This function is called with a player is trying
 *                       to complete the Sign Rating tour.
 * Arguments    :        object who - the player completing the tour
 */
public void
react_form(object who)
{
    object  reward;

    BLANK_SPACE; /* for player readability */

    command("say Oh, good! You've done it! I really can't thank you"
      + " enough. Chadwick will be so pleased. Here, please take this.");

    BLANK_SPACE; /* for player readability */

    reward = MONEY_MAKE_GC(5);
    reward->move(this_object());
    command("give coins to " + OB_NAME(who));

    if (environment(reward) == this_object())
    {
       command("drop coins");
    }

    BLANK_SPACE; /* for player readability */

    give_reward(this_player(),
            CITY_TOUR_SIGN_GROUP,
            CITY_TOUR_SIGN_BIT,
            CITY_TOUR_SIGN_EXP,
            "tour_signs");  

    BLANK_SPACE; /* for player readability */

    this_player()->remove_prop(SPARKLE_TOUR_PROP);

    command("say Here, if you like you can <exa results> here at my"
      + " table any time you like to see how others have rated the"
      + " signs, too!");

    check_remaining_tours(who);
    return;
} /* react_form */


/*
 * Function name:        check_remaining tours
 * Description  :        See if there are other tours that the player
 *                       can still do here, and if so, have the npc
 *                       inform them of this.
 * Arguments    :        object who - the player to check for
 */
public void
check_remaining_tours(object who)
{
    BLANK_SPACE; /* for player readability */

    if (!this_player()->test_bit("Sparkle",
            CITY_TOUR_LOCALQM_GROUP,
            CITY_TOUR_LOCALQM_BIT))
    {
        command("say I've still got more for you to do, if you'd like"
          + " to <ask> me for another task.");
        return;
    }

    command("say You've completed all of the tours I am currently giving"
      + " out. You might try returning again later on to see if I have any"
      + " new ones in the future, though!");
    return;
} /* check_remaining_tours */


/*
 * Function name:        update_poster
 * Description  :        See if the poster needs an update, and have him
 *                       change the time if needed.
 */
public void
update_poster()
{
    string  hour = capitalize(s_get_stime_hour_of_period());

    if (Time_Readout == hour)
    {
        return;
    }

    command("emote suddenly seems to remember something. He quickly peers"
      + " at the sky to check the <time> and uses a pencil to erase and"
      + " then change some numbers on the poster he is sitting beside.");
    Time_Readout = hour;
    return;
}


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    check_dog();
} /* enter_env */


/*
 * Function name:        react_cadets_checklist
 * Description  :        This function is called with a player is trying
 *                       to complete the Cadet's Guild tour.
 * Arguments    :        object who - the player completing the tour
 */
public void
react_cadets_checklist(object who)
{
    object  reward;

    BLANK_SPACE; /* for player readability */

    command("say Aha! Looks like you found the cadets, and spoke to"
      + " Xania and Xorfin. Perfect! That school is just the best place"
      + " in Genesis for beginning adventurers to learn things, you"
      + " know. If you're still feeling a bit green, you should sign" 
      + " up with those guilds, if you haven't already.");

    BLANK_SPACE; /* for player readability */

    reward = MONEY_MAKE_GC(10);
    reward->move(this_object());
    command("give coins to " + OB_NAME(who));

    if (environment(reward) == this_object())
    {
       command("drop coins");
    }

    BLANK_SPACE; /* for player readability */

    give_reward(this_player(),
            CITY_TOUR_GUILD_GROUP,
            CITY_TOUR_GUILD_BIT,
            CITY_TOUR_GUILD_EXP,
            "tour_guild");  

    BLANK_SPACE; /* for player readability */

    this_player()->remove_prop(SPARKLE_TOUR_PROP);

    command("say There you go. You've earned those coins!");

    check_remaining_tours(who);
    return;
} /* react_cadets_checklist */


/*
 * Function name:        react_localqm_checklist
 * Description  :        This function is called with a player is trying
 *                       to complete the Local Questmaster tour.
 * Arguments    :        object who - the player completing the tour
 */
public void
react_localqm_checklist(object who)
{
    object  reward;

    BLANK_SPACE; /* for player readability */

    command("say Really? You've found all these questmasters and done"
      + " all they've asked of you? Heavens, but you've been busy! Well,"
      + " this really does deserve some recognition.");

    BLANK_SPACE; /* for player readability */

    reward = MONEY_MAKE_PC(3);
    reward->move(this_object());
    command("give coins to " + OB_NAME(who));

    if (environment(reward) == this_object())
    {
       command("drop coins");
    }

    BLANK_SPACE; /* for player readability */

    give_reward(this_player(),
            CITY_TOUR_LOCALQM_GROUP,
            CITY_TOUR_LOCALQM_BIT,
            CITY_TOUR_LOCALQM_EXP,
            "tour_localqm");  

    BLANK_SPACE; /* for player readability */

    this_player()->remove_prop(SPARKLE_TOUR_PROP);

    command("say There you go. You've earned those coins!");

    check_remaining_tours(who);
    return;
} /* react_localqm_checklist */


/*
 * Function name:        crier_exit_check
 * Description  :        If players are young and have not yet seen
 *                       the sign, they are forced to see it before
 *                       leaving this room. This helps newbies realize
 *                       there are tasks that can be done in this
 *                       room.
 * Arguments    :        object who - the player
 * Returns      :        1 - cannot exit, 0 - can exit
 */
public int
crier_exit_check(object who)
{
    if (VENDOR->get_info(QUEST_FILE(who->query_real_name()),
        "crier_seen") == "yes")
    {
        return 0;
    }

    if (who->test_bit("Sparkle",
            CITY_TOUR_SIGN_GROUP,
            CITY_TOUR_SIGN_BIT))
    {
        return 0;
    }

    if (!SD_IS_NEWBIE(who))
    {
        return 0;
    }

    tell_room("As " + QTNAME(who) + " turns to leave, the fluffy brown"
      + " dog leaps in front of " + who->query_objective() + " barking"
      + " loudly!\n\n", who);

    who->catch_tell("As you turn to leave, the fluffy brown dog leaps"
      + " in front of you, barking loudly! She points with her nose at"
      + " the poster that is on the table. It seems she wants to make"
      + " sure you <exa poster> before moving on.\n");

    return 1;
} /* crier_exit_check */
