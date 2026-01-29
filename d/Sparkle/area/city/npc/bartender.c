/*
 *  /d/Sparkle/area/city/npc/bartender.c
 *
 *  This is the bartender of the Sparkle Pub. I am working to see if
 *  I can try to create an effectively non-gendered npc to appeal to
 *  any prospective players who are hungry for that sort of
 *  representation in Genesis. S/he is a friendly, androgenous
 *  halfling. This is also the quest npc for another fun little quest
 *  for new players in Sparkle.
 *
 *  Created August 2018, by Cooper Sherry (Gorboth)
 *
 *  (minor addition of dialogue for Iron Delving Brewery functionality
 *     "@@ask_bartender|export@@"  ... by Vitwitch April 2021)
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
#define         MY_CURRENT_JUG   "_quest_current_jug_prop"
#define         BAR_CAT          "_sparkle_bar_hellcat"
#define         FRESH_METER      "_got_fresh_with_sparkle_bartender"
#define         TAVERN_BAN_LOG   (LOG_DIR + "tavern_ban_log")
#define         BLANK_SPACE   tell_room(environment(this_object()), "\n")
#define         GEYSER_ROOM      ("/d/Genesis/start/human/wild2/geyser")
#define         JUG_MASTER       (OBJ_DIR + "jug_master")


/* Global Variables */
public mapping     Jug_Assignments = ([]);
public mapping     Name_Assignments = ([]);
public int         Jug_Number = 0;
public int         Busy  = 0;
public object      Cat;
public string     *Bartender_Acts = ({
                       "emote cleans a nearby table with a damp towel.",
                       "emote pulls a book from beneath the bar, reads"
                     + " for a few minutes, then gets interrupted.",
                       "emote dusts a few of the bottles on the top"
                     + " shelf of the bar.",
                       "emote hears a 'snap!' and reaches under the"
                     + " bar. A dead mouse is tossed up to the"
                     + " hellcat, who catches it in its mouth.",
                       "emote leans against the bar and giggles"
                     + " as the hellcat begins to ruffle his/her"
                     + " hair with its tail.",
                       "emote smiles, looking around the tavern with"
                     + " satisfaction.",
                       "emote runs back to check on the lounge, and"
                     + " quickly returns.",
                       "emote walks briefly into the parlor, and"
                     + " returns with a few empty glasses.", });


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
public void        intro_check(object who);
public string      ask_bartender(string question);
public void        check_cat();
public void        react_spitting();
public void        react_rudeness();
public void        react_freshness();
public void        enter_env(object dest, object old);
public void        kick_out_of_bar(object who, string reason);
public string      query_pronoun();
public string      query_objective();
public string      query_possessive();
public string      check_tours(object who);
public void        assign_jug(object who, object jug);
public void        jug_return(object jug, object who, int not_quester);
public void        jug_accounting(int j_number);
public string      jug_listing(object who);


/* 
 * Function name:       create_sparkle_npc
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sparkle_npc()
{
    mixed  j_assign;
    mixed  n_assign;

    set_living_name("ellingnor");
    set_name("ellingnor");
    add_name( ({ "bartender", "owner",
                 "_sparkle_pub_bartender" }) );
    set_race_name("halfling");
    set_gender(G_NEUTER);
    add_adj( ({ "cheerful", "brown-skinned", "brown",
                "clever", "clever-eyed" }) );

    npcsize(this_object(), "short", "of normal width");

    set_title("Suretop, Bartender of the Boar's Head Tavern");

    set_short("cheerful halfling bartender");
    set_long("Brown skinned and clever-eyed, this cheerful halfling"
      + " clearly runs the place, moving around with harmless"
      + " swagger and good-natured authority. She (or is it a"
      + " he? A bit hard to tell ...) smirks at you as your"
      + " eyes meet and you sense that you could probably"
      + " <order> something if s/he is around.\n");

    set_stats( ({ 100, 70, 300, 100, 400, 50 }) );
    set_alignment(0); /* Serves no cause but his/her own. */
    set_whimpy(0); /* S/he would never abandon the bar! */

    add_ask( ({ "task", "tasks", "help", "help with tasks",
                "task help", "helping", "helping with tasks",
                "tasks you may need help with",
                "tasks he may need help with",
                "quest", "quests", "help", "tour", "tours" }),
        "say " + "@@ask_bartender|tasks@@", 1);

    add_ask( ({ "export brew", "iron delving brew", 
                "iron delving export brew",
                "iron delving" }),
        "say " + "@@ask_bartender|export@@", 1);
    add_ask( ({ "church", "first church of sparkle", "sparkle church",
                "church of sparkle", "table" }),
        "say " + "@@ask_bartender|church@@", 1);
    add_ask( ({ "orc", "orcs" }),
        "say " + "@@ask_bartender|orcs@@", 1);
    add_ask( ({ "reward" }),
        "say " + "@@ask_bartender|reward@@", 1);
    add_ask( ({ "kiki", "cat", "pet", "hellcat",
                "massive hellcat", "massive cat", "hell cat" }),
        "say " + "@@ask_bartender|cat@@", 1);
    add_ask( ({ "carlsan", "town crier", "crier" }),
        "say " + "@@ask_bartender|carlsan@@", 1);
    add_ask( ({ "ellingnor", "bartender", "you" }),
        "say " + "@@ask_bartender|myself@@", 1);
    add_ask( ({ "genesis", "donut", "realm" }),
        "say " + "@@ask_bartender|genesis@@", 1);
    add_ask( ({ "geyser", "geysers" }),
        "say " + "@@ask_bartender|geyser@@", 1);
    add_ask( ({ "jug", "funnel", "funnel jug", "funnel-jug" }),
        "say " + "@@ask_bartender|jug@@", 1);
    add_ask( ({ "giant", "giants" }),
        "say " + "@@ask_bartender|giants@@", 1);
    add_ask( ({ "drink", "brew", "special brew", "alcohol",
                "beer", "booze", "wine", "spirits", "whiskey" }),
        "say " + "@@ask_bartender|drink@@", 1);
    add_ask( ({ "list", "jug list", "list of jugs", "funnel jug list",
                "funnel-jug list", "list of funnel jugs",
                "list of funnel-jugs" }),
        "say " + "@@ask_bartender|list@@", 1);
    add_ask( ({ "dock", "docks", "genesis shiplines", "ships",
                "ship", "vessels", "genesis shiplines sign",
                "genesis shipline signs", "genesis shiplines company" }),
        "say " + "@@ask_bartender|docks@@", 1);
    add_ask( ({ "faerun", "home", "faerun domain" }),
        "say " + "@@ask_bartender|faerun@@", 1);
    add_ask( ({ "bar", "pub", "here", "boars head", "boar's head",
                "tavern", "boars head tavern", "boar's head tavern" }),
        "say " + "@@ask_bartender|bar@@", 1);
    add_ask( ({ "carlsan", "crier", "town crier", "laziest man",
                "laziest man in town" }),
        "say " + "@@ask_bartender|carlsan@@", 1);
    add_ask( ({ "karkadelt", "enchanter" }),
        "say " + "@@ask_bartender|enchanter@@", 1);
    add_ask( ({ "nikolon", "librarian" }),
        "say " + "@@ask_bartender|nikolon@@", 1);
    add_ask( ({ "library" }),
        "say " + "@@ask_bartender|library@@", 1);
    add_ask( ({ "session", "sessions" }),
        "say " + "@@ask_bartender|session@@", 1);
    add_ask( ({ "fire", "fireplace", "fire out", "light fire",
                "fire place", "chimney" }),
        "say " + "@@ask_bartender|fire@@", 1);
    add_ask( ({ "elixer" }),
        "say " + "@@ask_bartender|elixer@@", 1);
    add_ask( ({ "ingredient", "secret ingredient", "spray",
                "geyser spray", "spray from the geyser" }),
        "say " + "@@ask_bartender|spray@@", 1);
    add_ask( ({ "recipe", "secret recipe", "family secret",
                "secret" }),
        "say " + "@@ask_bartender|recipe@@", 1);
    add_ask( ({ "skoot" }),
        "say " + "@@ask_bartender|skoot@@", 1);
    add_ask( ({ "wrestling", "arm wrestling", "arm-wrestling",
                "tournament", "tournaments" }),
        "say " + "@@ask_bartender|wrestling@@", 1);
    add_ask( ({ "lounge" }),
        "say " + "@@ask_bartender|lounge@@", 1);
    add_ask( ({ "parlor", "parlour" }),
        "say " + "@@ask_bartender|parlor@@", 1);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(NPC_I_NO_LOOKS, 1);           /* no beauty words */

    add_prop(OBJ_M_NO_ATTACK, "Sensing your intentions, the massive"
      + " hellcat rises from its perch above the bar and peers"
      + " down at you with death in its eyes. As you falter, it"
      + " slowly sits back down, tail swishing, and stares at you"
      + " without blinking.\n");

    set_skill(SS_UNARM_COMBAT, 50);      /* S/he runs a bar ...   */
    set_skill(SS_AWARENESS, 100);        /* With help from Kiki!  */
    set_skill(SS_ANI_HANDL, 80);         /* S/he's a pet owner.   */

    setuid();
    seteuid(getuid());

    JUG_MASTER->short();
    j_assign = JUG_MASTER->query_jug_assignments();
    n_assign = JUG_MASTER->query_name_assignments();

    if (mappingp(j_assign))
    {
        Jug_Assignments = j_assign;
    }

    if (mappingp(n_assign))
    {
        Name_Assignments = n_assign;
    }
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
        "say " + "@@ask_bartender|sparkle@@", 1);
    add_ask( ({ "job", "occupation", "work", "career" }),
        "say " + "@@ask_bartender|job@@", 1);
    add_ask( ( Swear_Words ),
        "say " + "@@ask_bartender|cuss@@", 1);
        
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
        command("emote scratches his/her head and shrugs.");
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
        write_file(LOG_DIR + "bartender_asks", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " questions the Sparkle Bartender: '"+
            ((question != OrigQuestion) ? OrigQuestion+"' -> '" : "")+
                question+"'\n");
    }

    command("say " + ask_bartender("no_info"));
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
    command("say Back for more, " + who->query_name() + "?");
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
    command("peer determin");
    command("say You'll never get me out of the bar!");

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
    arm->set_name("washcloth");
    arm->set_short("damp washcloth");
    arm->set_adj( ({ "damp" }) );
    arm->set_long("Though damp, this thing smells fresh enough. It"
      + " has a few stains, as if it has been used to clean tables.\n");
    arm->set_hit(10);
    arm->set_pen(1);
    arm->add_prop(OBJ_I_WEIGHT, 5);
    arm->add_prop(OBJ_I_VOLUME, 10);
    arm->move(this_object());

    command("wield all");
} /* arm_me */


/*
 * Function name:       alert_hour_change_hook
 * Description  :       This function gets called whenever the hour
 *                      hour changes in the City of Sparkle
 *                      NPCs can use this to act upon the hour,
 *                      to provide the semblance of a daily routine.
 *                      In the case of the bartender, we use this to
 *                      trigger acts, rather than using add_act().
 * Arguments    :       hour - current hour in Sparkle time
 */
public void
alert_hour_change_hook(int hour)
{
    /* Make sure the cat is in place */
    check_cat();

    if (is_busy())
    {
        /* Don't participate in routines when interacting. */
        return;
    }

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
        if (!random(3))
        {
            command(one_of_list(Bartender_Acts));
        }
        break;
    case 23:
        command("$emote stretches tiredly.");
        command("$say Sheesh, already nighttime?");
        command("$say I'd better pep up a bit with this elixer I"
          + " got from Karkadelt!");
        command("$emote drinks from a jeweled black flask, and"
          + " blinks rapidly, looking completely refreshed.");
        break;
    default:
        break;
    }

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

    if (obj->id("_sparkle_tour_food"))
    {
        command("say Is that for you, or is it for that fat lazy"
          + " bum Carlsan?");

        return;
    }

    if (obj->id("_sparkle_tour_quest_drink"))
    {
        command("say If you've met the Town Crier, he just loves"
          + " these. But, I bet you already know that!");

        return;
    }

    if (obj->id(PUB_QUEST_ITEM))
    {
        command("say Oh, has that been filled up yet? Please <give> it"
          + " to me if it is!");

        return;
    }

    if (obj->id(SCRUB_BRUSH))
    {
        command("say Ah, so Carlsan's got a new buddy to do all"
          + " his work for him, has he?");
        command("laugh merr");

        return;
    }

    if (obj->id(FEATHER_DUSTER))
    {
        command("say Oh, I suppose you're doing Carlsan's work for"
          + " him? Hee hee. The guy is lazy, but you can't say he"
          + " isn't clever!");

        return;
    }

    command("say I haven't got much to tell you about that, I'm afraid.");
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
    if (obj->id("coin"))
    {
        command(one_of_list( ({
            "say Heh ... thanks! I appreciate tips!",
            "say Tips are always appreciated, thanks!",
            "say Another tip? Wow ... this is turning out to be a good"
          + " day, thanks!",
            "say Thanks, you come back anytime!",
            }) ));

        return;
    }
    else if (obj->id(PUB_QUEST_ITEM))
    {
        if (to->test_bit("Sparkle",
            SPARKLE_PUB_GROUP,
            SPARKLE_PUB_BIT))
        {
            jug_return(obj, to, 2);
            return;
        }

        if (!to->query_prop(PUB_QUESTING_PROP))
        {
            jug_return(obj, to, 1);
            return;
        }

        jug_return(obj, to, 0);
        return;
    }
    else
    {
        command("say Nah, you keep that.");
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
        command("say Oh, hey! Have I seen you in here before?");
        command("introduce myself");
    }
}


/*
 * Function name:        ask_bartender
 * Description  :        Make a particular query to Ellingnor
 * Arguments    :        string question - the subject of the ask
 * Returns      :        The response
 */
public string
ask_bartender(string question)
{
    intro_check(this_player());

    switch(question)
    {
        default:
        case "no_info":
            command(one_of_list( ({ "think", "confused", "hmm" }) ));
            return(one_of_list( ({
                "Guess I'm no help to you on that one.",
                "Wish I knew more about that, but I don't!",
                "Huh ... you'd probably want to ask someone else.",
                "I'm clueless on that one, sorry!",
                }) ));
            break;
        case "tasks":
            return check_tours(this_player());
            break;
        case "export":
            return "Iron Delving! Across the Sea and over the Plain,"
              + " there it lies with its Brewery under the Hill. Their"
              + " export brew comes in fresh and tasty. If you venture"
              + " out there, you should try your hand, maybe you got"
              + " the knack.";
            break;
        case "parlor":
            return "I like the parlour! It is very cozy and quiet"
              + " in there compared with the bar, and I will admit"
              + " I sometimes sneak in there when things get slow.";
            break;
        case "lounge":
            return "People really have a blast in the lounge. You"
              + " should check it out! Skoot will no doubt try to"
              + " get you to do some arm-wrestling.";
            break;
        case "skoot":
            return "Skoot ... that crusty old salt! He and I met"
              + " a long time ago in Faerun where he used to hold"
              + " tournaments on the wharf. When he heard I was"
              + " coming to Sparkle, he hit me up with a business"
              + " proposition, and we've been here together ever"
              + " since.";
            break;
        case "wrestling":
            return "That is Skoot's thing. You can go have a bunch"
              + " of fun with it in the lounge if you want to roll"
              + " up your sleeves or risk some coin!";
            break;
        case "orcs":
            return "Those idiots keep attacking the city!";
            break;
        case "reward":
            switch(this_player()->query_prop(PUB_QUESTING_PROP))
            {
                case 0:
                    return "Reward? For what? Are you looking for"
                      + " work or something? If"
                      + " so, just <ask> me about tasks.";
                    break;
                default:
                    return "You'll need to bring me back that geyser"
                      + " spray, first. You still have your funnel-jug"
                      + " don't you? If you're not sure, just <ask>"
                      + " me about tasks again and we'll get it"
                      + " sorted out.";
                    break;
            }
            break;
        case "sparkle":
            return "I came to Sparkle from Faerun not too long ago."
              + " This place is where all the action is for commerce"
              + " and selling beer!";
            break;
        case "job":
            return "Do I really have to explain it? I sell booze!";
            break;
        case "cuss":
            return "You talk like a sailor! I like sailors!";
            break;  
        case "cat":
            return "Kiki is the best cat in the whole world!";
            break;  
        case "church":
            return "It is right in the center of town, north of the"
              + " library.";
            break;
        case "myself":
            command("eyebrow");
            return "You're looking at the real thing, right here!";
            break;    
        case "genesis":
            return "Genesis, the donut we inhabit, has been floating"
              + " around in the oven of the Maker for quite a while"
              + " now. You can know more with <help history>.";
            break;
        case "docks":
            return "They are right outside the door.";
            break;
        case "faerun":
            return "Faerun is great and all, but I didn't get enough"
              + " visitors in my pub there. I'm liking it so much"
              + " more here in Sparkle.";
            break;
        case "bar":
            return "Welcome! Hope you stay long and drink lots!";
            break;
        case "drink":
            return "I'll sell you as much of that as you want to buy!";
            break;
        case "sailor":
            return "Sailors drink a lot. C'mon ... be a sailor!";
            break;
        case "carlsan":
            return "The laziest man in town. Also, our Town Crier."
              + " If he did more than snore, maybe the town would"
              + " be alerted to things now and then. Typically, I"
              + " just step over him if I am trying to get into the"
              + " church.";
            break;
        case "enchanter":
            return "The Enchanter? Oh, he's amazing! He makes the"
              + " best stuff to keep me awake, so I owe him big"
              + " time. He comes in now and then and I give him"
              + " a free session.";
            break;
        case "nikolon":
            return "Nikolon's our librarian. Kind of a nerd.";
            break;
        case "jug":
            return "The funnel-jug is a special tool I perfected"
              + " for collecting spray from the nearby geyser. I've"
              + " made a ton of 'em, and they all have a number"
              + " scratched into the bottom to keep track of them."
              + " I keep a list!";
            break;
        case "list":
            return jug_listing(this_player());
            break;
        case "library":
            return "If you can find the church, you can find the"
              + " library. It is just south of it.";
            break;
        case "geyser":
            return "The geyser is a real landmark in this region!"
              + " If you find it, just wait around a while and it will"
              + " erupt sending a bunch of spray all over! It is"
              + " a ways northwest of town, but be careful of the"
              + " giants up there!";
            break;
        case "giants":
            return "I don't know what you've heard, but I can tell"
              + " you right now that the giants that have been"
              + " living up near the geyser are NOT to be fooled with.";
            break;
        case "session":
            return "Sessions? Oh, that's what we're famous for"
              + " here at the Boar's Head! People come from all over"
              + " Genesis just to hang out here and enjoy a good"
              + " session. Check our menu - you can order one"
              + " yourself! It tends to get people a lot more in"
              + " the mood for experience in the real world, makes"
              + " it more profitable!";
            break;
        case "elixer":
            return "Hoo, this stuff is a life saver! I saw Karkadelt"
              + " himself chugging it one time, and we struck a deal."
              + " He made me promise never to tell what I gave him"
              + " for it, though ... ahem ...";
            break;
        case "fire":
            command("emote glances at the chimney and nods.");
            environment(this_object())->reset_room();
            return "";
            break;
        case "spray":
            return "Lots of people know I use spray from the local"
              + " geyser when I brew up the drink we use in our"
              + " sessions here at the Boar's Head. What they don't"
              + " know is the recipe! I am always looking for"
              + " people to help me out with my quest to get more.";
            break;
        case "recipe":
            return "That's a family secret! I'd never share it!";
            break;
    }

    /* Should never happen, but just in case. */
    return "What? Sorry, I seem to be confused.";
} /* ask_bartender */


/*
 * Function name:        check_cat
 * Description  :        Make sure Ellingnor's cat is here.
 */
public void
check_cat()
{
    if (!environment(this_object()))
    {
        return;
    }

    if (!objectp(Cat = present(BAR_CAT, environment(this_object()))))
    {
        Cat = clone_object(NPC_DIR + "kiki");
        Cat->add_name(BAR_CAT);
        Cat->move(environment(this_object()));
    }
} /* check_cat */


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
    if (emote == "spit")
    {
        react_spitting();
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
 * Function name:        react_spitting
 * Description  :        We'll give some likely responses to rude
 *                       behavior
 */
public void
react_spitting()
{
    command(one_of_list( ({ "ack", "gasp", "blink", "glare" }) ));

    command(one_of_list( ({
        "say Read the sign! NO SPITTING IN MY BAR! Out!",
        "say Kiki! Another spitter! Sic 'em!",
        "say We've never allowed that, and we won't start now!",
        "say Get this spitting jackass out of here!",
        }) ));

    kick_out_of_bar(this_player(), "spitting");
    return;
} /* react_spitting */


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
        "say What the?! Kiki! Get this idiot out of here!",
        "say We've got standards here, and you can get lost!",
        "say Okay, so you're gonna be one of those types! Kiki!",
        "say You take that sort of idiocy elsewhere!",
        "say Alright, a lesson in manners, coming right up!",
        "say Lars' sakes! I'm running a decent pub here, fool!",
        "say Oh, you think I put up with that, do you?",
        "say I fed the last person who did that to Kiki, you scumbag!",
        "say Okay, now I'm not in a good mood!",
        "say So, you wanted to see my mean streak? Fine. KIKI!",
        "say I'm just through with this crap. Out you go!"
        }) ));

    kick_out_of_bar(this_player(), "rudeness");
} /* react_rudeness */


/*
 * Function name:        react_freshness
 * Description  :        We'll give some likely responses to fresh
 *                       behavior
 */
public void
react_freshness()
{
    int    freshness = this_player()->query_prop(FRESH_METER);

    if (freshness > 2)
    {
        command("say Alright. This one gets the boot. Kiki!! Let's"
          + " take out the trash!");
        kick_out_of_bar(this_player(), "being fresh");

        return;
    }

    if (!random(3))
    {
        command(one_of_list( ({ "ack", "glare", "blink", "facepalm" }) ));
    }

    command(one_of_list( ({
        "say Look, I've got a type, but it isn't your type!",
        "say Nice try, but you're not cute enough.",
        "say This smile on my face will change if you keep that up.",
        "say Um ... no.",
        "say That will be enough of that, grabbypants!",
        }) ));

    freshness++;
    this_player()->add_prop(FRESH_METER, freshness);
} /* react_freshness */


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

    check_cat();
} /* enter_env */


/*
 * Function name:        kick_out_of_bar
 * Description  :        Kick this player out of the bar
 * Arguments    :        object - the player to boot out
 *                       string reason - why they got booted
 */
public void
kick_out_of_bar(object who, string reason)
{
    object  street_room =
                find_object("/d/Genesis/start/human/town/pier2");

    if (environment(who) != environment(this_object()))
    {
        command("shout Good! Run on out of here, you loser!");
        return;
    }

    if (who->query_wiz_level())
    {
        command("say What?? Kiki, since when have you been scared"
          + " of wizards?! Pfff ... fine, I guess we have to let"
          + " this jerk stay in here.");
        return;
    }

    tell_room(environment(this_object()), "\nRRRROOOAAAAR!!!\n\n"
      + "The massive hellcat leaps down from her perch!\n");

    who->catch_tell("Huge teeth grab you roughly by the neckline"
      + " and you are dragged swiftly to the entrance and thrown"
      + " out into the street!\n\nAaaargh!!\n");

    tell_room(street_room, "\n" + QCTNAME(who)
      + " comes flying out the door of the tavern and crashlands"
      + " just beside you with a painful thud! A massive hellcat"
      + " in the doorway growls and spits a bit of torn clothing"
      + " out of her teeth before returning back inside.\n\n");

    who->move_living("M", street_room, 1, 1);

    tell_room(environment(this_object()), QCTNAME(who)
      + " is grabbed roughly by the neckline and hauled by the"
      + " powerful jaws of the beast to the door where "
      + who->query_pronoun() + " is thrown out into the street!\n");

    environment(this_object())->ban_patron(who);

    write_file(TAVERN_BAN_LOG, 
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") " + " -- "
      + capitalize(who->query_name())
      + " booted from the tavern for " + reason + "\n");

    return;
} /* kick_out_of_bar */


/*
 * Function name:   query_pronoun
 * Description:     Returns the pronoun that goes with the gender of this
 *                  living.
 * Returns:         "he", "she" or "it", depending on gender.
 *
 * Note: We mask this from the mudlib to create the proper gender
 *       neutral "s/he"
 */
public string
query_pronoun()
{
    return "s/he";
} /* query_pronoun */


/*
 * Function name:   query_objective
 * Description:     Returns the objective that goes with the gender of this
 *                  living.
 * Returns:         "him", "her" or "it", depending on gender.
 *
 * Note: We mask this from the mudlib to create the proper gender
 *       neutral "him/her" (randomized order)
 */
public string
query_objective()
{
    return one_of_list( ({ "him/her", "her/him" }) );
} /* query_objective */


/*
 * Function name:   query_possessive
 * Description:     Returns the possessive that goes with the gender of this
 *                  living.
 * Returns:         "his", "her" or "its", depending on gender.
 *
 * Note: We mask this from the mudlib to create the proper gender
 *       neutral "his/her" (randomized order)
 */
public string
query_possessive()
{
    return one_of_list( ({ "his/her", "her/his" }) );
} /* query_possessive */


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
    mixed  on_quest = who->query_prop(PUB_QUESTING_PROP);
    mixed  current_jug = who->query_prop(MY_CURRENT_JUG);
    mixed  q_item   = current_jug->get_this_object();
    int    jugs_given;

    BLANK_SPACE; /* for player readability */

    if (!who->test_bit("Sparkle",
            SPARKLE_PUB_GROUP,
            SPARKLE_PUB_BIT))
    {   
        if (on_quest)
        {
            if (objectp(q_item))
            {
                if (environment(q_item) == find_object(GEYSER_ROOM))
                {
                    return "Oh, you left the funnel-jug at the geyser?"
                      + " Good! Nice work finding it! Be sure to go back"
                      + " and check on it soon. That thing blows pretty"
                      + " often, so it shouldn't take too long to fill it"
                      + " up.";
                 }

                if (environment(q_item) == environment(this_object()))
                {
                    return "Looks like you've set your funnel-jug on the"
                      + " floor here. Let's not be careless with it!"
                      + " Pick it up and finish the task I gave you!";
                }
            }

            if (!present(PUB_QUEST_ITEM, who))
            {
                jugs_given = sizeof(
                    Name_Assignments[who->query_real_name()]);

                if (jugs_given > 1)
                {
                    return "What?? Lost another one? Forget it."
                      + " I'm not giving you any more right now. Find"
                      + " and bring one of yours back! Or, who knows?"
                      + " maybe you'll get lucky and someone will turn"
                      + " one of the ones you lost in for you! You"
                      + " can <ask> me about the list I keep if you"
                      + " forgot which ones you had.";
                }

                q_item = clone_object(OBJ_DIR + "funnel_jug");
                who->add_prop(PUB_QUESTING_PROP, 1);
                who->add_prop(MY_CURRENT_JUG, q_item);
                q_item->move(who);

                command("say Hey, did you lose the jug??? Hmmm ... ");
                command("grumble");
                BLANK_SPACE; /* for player readability */

                write(this_object()->query_The_name(who) + " gives you"
                  + " another funnel-jug.\n");
                tell_room(environment(this_object()), QCTNAME(this_object())
                  + " gives a funnel-jug to " 
                  + QTNAME(who) + ".\n", who);
                BLANK_SPACE; /* for player readability */
                command("say You keep track of it this time, I don't"
                  + " like those being lost!");
                BLANK_SPACE; /* for player readability */
                command("emote writes down some info on a parchment.");
                BLANK_SPACE; /* for player readability */

                assign_jug(who, q_item);
            }

            return "See if you can get that funnel-jug filled with"
              + " spray from the geyser. You'll have to travel northwest"
              + " of town to find it. But, be careful about the VERY"
              + " DANGEROUS giants up there. The geyser is just a bit"
              + " south of them.";
        }

        TELL_G(capitalize("\n\n\t" + who->query_name()) + " begins the"
          + " pub GEYSER quest! !!! *** !!!!\n");

        command("say Yep! I've got something you can help with.");
        BLANK_SPACE; /* for player readability */
        command("say We're always trying to get enough of our special"
          + " session drink made, and the key ingredient is very very"
          + " specific - spray collected from our local geyser!");
        BLANK_SPACE; /* for player readability */
        command("say I need as many people as possible to help me get"
          + " that collected, so if you can help, that would be great."
          + " Here, take this ...");
        BLANK_SPACE; /* for player readability */

        q_item = clone_object(OBJ_DIR + "funnel_jug");
        who->add_prop(PUB_QUESTING_PROP, 1);
        who->add_prop(MY_CURRENT_JUG, q_item);
        q_item->move(who);

        write(this_object()->query_The_name(who) + " gives you a"
          + " funnel-jug.\n");
        tell_room(environment(this_object()), QCTNAME(this_object())
          + " gives a funnel-jug to " + QTNAME(who) + ".\n", who);
        BLANK_SPACE; /* for player readability */
        command("say See if you can get that funnel-jug filled with"
              + " spray from the geyser. You'll have to travel northwest"
              + " of town to find it. But, be careful about the VERY"
              + " DANGEROUS giants up there. The geyser is just a bit"
              + " south of them.");
        BLANK_SPACE; /* for player readability */
        command("emote writes down some info on a parchment.");
        BLANK_SPACE; /* for player readability */

        assign_jug(who, q_item);

        write_file(LOG_DIR + "quest_begin", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(who->query_name())
          + " began the pub geyser quest.\n");

        return "";
    }

    return "Looking for quests? Well, you've helped me out"
      + " enough. If you haven't already, check with Carlsan in front"
      + " of the church. Maybe Nikolon in the library has"
      + " a few. And I myself have helped Karkadelt the"
      + " enchanter out a few times! Of course, Skoot has a bunch"
      + " of rewards in the lounge if you want to get involved in"
      + " all that arm-wrestling.";
} /* check_tours */


/*
 * Function name:        assign_jug
 * Description  :        Ellingnor keeps track of the jugs s/he has
 *                       given out, making sure she knows which players
 *                       have had which jugs loaned to them.
 * Arguments    :        object who - the player
 *                       object jug - the jug
 */
public void
assign_jug(object who, object jug)
{
    string  who_name = who->query_real_name();
    int    *assigned_so_far = Name_Assignments[who_name];

    Jug_Number++;

    if (sizeof(assigned_so_far))
    {
        assigned_so_far += ({ Jug_Number });
    }
    else
    {
        assigned_so_far = ({ Jug_Number });
    }

    Name_Assignments[who_name] = assigned_so_far;
    Jug_Assignments[Jug_Number] = who_name;

    jug->set_j_number(Jug_Number);

    JUG_MASTER->set_jug_assignments(Jug_Assignments);
    JUG_MASTER->set_name_assignments(Name_Assignments);

    return;
} /* assign_jug */


/*
 * Function name:        jug_return
 * Description  :        Handle when players return the jug to the
 *                       bartender, whether they are on the quest or not.
 * Arguments    :        object jug - the jug object
 *                       object who - the player returning the jug
 *                       int not_quester 0: the player is on the quest
 *                                       1: the player is not on the quest
 *                                       2: the player already did the quest
 */
public void
jug_return(object jug, object who, int not_quester)
{
    int     filled = jug->query_filled();
    int     j_number = jug->query_j_number();
    mixed   j_assigned = Jug_Assignments[j_number];
    string  say_txt = "Oh, you found one of my funnel-jugs, did you? ";
    object  reward;

    if (not_quester)
    {
        if (not_quester == 1)
        {
            say_txt += "You might want to <ask> me about tasks so I"
              + " can give you a bit of a job with one of these.";
        }
        else
        {
            say_txt += "I remember when you did this job for me yourself"
              + " a while ago.";
        }

        BLANK_SPACE; /* for player readability */
        command("say " + say_txt);
        BLANK_SPACE; /* for player readability */
        command("emote pulls out a piece of parchment and writes"
          + " something down on it.");
        BLANK_SPACE; /* for player readability */

        command("hmm");

        if (j_number)
        {
            command("say Let's see, this is jug number " + j_number + ".");
        }
        else
        {
            command("say I thought I scratched numbers on all of these!"
              + " How strange ...");
        }

        if (strlen(j_assigned))
        {
             command("say Ah, this was one I gave out originally to "
               + capitalize(j_assigned) + ". I wonder how they lost"
               + " track of it.");
        }
        else
        {
            command("say Did I forget to write down who I assigned"
              + " this one to? Oh well, silly me.");
        }

        BLANK_SPACE; /* for player readability */
        command("say In any case, thanks for returning this!");
        BLANK_SPACE; /* for player readability */

        jug_accounting(j_number);
        jug->remove_object();

        return;
    }

    BLANK_SPACE; /* for player readability */

    if (!filled)
    {
        command("say Oh, looks like you haven't filled it yet. You"
          + " go ahead and keep it. Return it to me when it is nice"
          + " and full of geyser spray!");

        command("give " + OB_NAME(jug) + " to " + OB_NAME(who));
        if (environment(jug) == this_object())
        {
            command("drop " + OB_NAME(jug));
        }

        return;
    }
    
    command("say Ah, you got the thing filled, did you? Let's take"
      + " a look!");
    BLANK_SPACE; /* for player readability */

    if (filled > 1)
    {
        command("emote smells the funnel-jug and frowns.");
        command("say Um, I don't know WHAT you put in this, but it"
          + " most definitely is NOT from the geyser. Who do you"
          + " think you are trying to fool??");
        command("emote empties the jug into a nearby trough, in"
          + " annoyance.");

        jug->set_filled(0);

        BLANK_SPACE; /* for player readability */

        command("give " + OB_NAME(jug) + " to " + OB_NAME(who));
        if (environment(jug) == this_object())
        {
            command("drop " + OB_NAME(jug));
        }

        BLANK_SPACE; /* for player readability */

        command("say Now get serious!! Go get it filled properly!");

        return;
    }

    command("emote smells the funnel-jug and smiles broadly.");
    command("say Right on! This is a great batch you've collected!");

    BLANK_SPACE; /* for player readability */

    command("emote pulls out a piece of parchment and writes"
      + " something down on it.");
    BLANK_SPACE; /* for player readability */

    if (strlen(j_assigned))
    {
        command("say Okay, so ... let's see ... jug " + j_number
          + " ...");

        if (j_assigned != who->query_real_name())
        {
            command("say Ah, this was one I gave out originally to "
              + capitalize(j_assigned) + ". I wonder how they lost"
              + " track of it. And, what happened to the one I gave"
              + " to you???");
        }
        else
        {
            command("say Yep! That's the one I gave you. Good, good."
              + " You wouldn't believe how many people end up losing"
              + " these!!");
        }
    }
    else
    {
        command("say Did I forget to write down who I assigned"
          + " this one to? Oh well, silly me.");
    }

    jug_accounting(j_number);

    BLANK_SPACE; /* for player readability */
    command("say In any case, GREAT WORK! Here's a small reward for"
      + " helping me with this.");
    jug->remove_object();
    BLANK_SPACE; /* for player readability */

    reward = MONEY_MAKE_PC(1);
    reward->move(this_object());
    command("give platinum coin to " + OB_NAME(who));

    if (environment(reward) == this_object())
    {
       command("drop platinum coin");
    }

    BLANK_SPACE; /* for player readability */

    give_reward(who,
            SPARKLE_PUB_GROUP,
            SPARKLE_PUB_BIT,
            SPARKLE_PUB_EXP,
            "sparkle_pub_geyser");  

    who->remove_prop(PUB_QUESTING_PROP);
    return;
} /* jug_return */


/*
 * Function name:        jug_accounting
 * Description  :        clean up the mappings when jugs are returned
 * Arguments    :        int j_number - the jug number
 */
public void
jug_accounting(int j_number)
{
    string    jug_owner  = Jug_Assignments[j_number];
    int      *owner_jugs = Name_Assignments[jug_owner];

    if (strlen(jug_owner))
    {
        owner_jugs -= ({ j_number });

        if (!sizeof(owner_jugs))
        {
            m_delkey(Name_Assignments, jug_owner);
        }
        else
        {
            Name_Assignments[jug_owner] = ({ owner_jugs });
        }
    }

    m_delkey(Jug_Assignments, j_number);

    JUG_MASTER->set_jug_assignments(Jug_Assignments);
    JUG_MASTER->set_name_assignments(Name_Assignments);
} /* jug_accounting */


/*
 * Function name:        jug_listing
 * Description  :        print a readout of the jug listing
 * Arguments    :        object who - the player asking
 * Returns      :        string
 */
public string
jug_listing(object who)
{
    int    *jug_numbers = sort_array(m_indices(Jug_Assignments));
    string  list_top;
    string  list_btm;
    string  l_item;
    int     pad_size;

    if (!sizeof(jug_numbers))
    {
        return "I don't have any jugs out right now. I need a few more"
          + " people to help me with the task I need doing, and then"
          + " I'm sure the list will start filling up again.\n";
    }

    list_top = "\n    _______________________\n"
             + "  /______________________/ \\\n"
             + "     \\                      \\\n"
             + "      | Jug #   Gave it to  |\n"
             + "      | ~~~~~~~~~~~~~~~~~~~ |\n";

    list_btm = "  ___/___________________   /\n"
             + "  \\______________________\\_/\n";

    who->catch_tell(list_top);

    foreach(int j_num: jug_numbers)
    {
        l_item = Jug_Assignments[j_num];
        pad_size = 14 - strlen(l_item);

        who->catch_tell("      |"
            + sprintf("%6d", j_num) + " - " + capitalize(l_item)
            + sprintf("%" + pad_size + "s", "|\n"));
    }

    who->catch_tell(list_btm + "\n");

    tell_room(environment(this_object()), QCTNAME(this_object())
      + " shows a list of some kind to " + QTNAME(who) + ".\n", who);

    return "That's who I've given jugs to at this point!";
} /* jug_listing */


/*
 * Function name:        generate_list
 * Description  :        this is just for testing purposes, to generate
 *                       some dummy data to test the list
 */
public void
generate_list()
{
    string *prefix = ({ "fel", "poo", "rub", "fin", "boon", "sar",
                        "chud", "fim", "too", "bor", "cla", "tren" });
    string *suffix = ({ "stan", "par", "cho", "flop", "bum", "tree",
                        "carp", "fee", "rand", "strel", "buff", "chi" });
    int     n = 20;
    string  this_name;

    while (n)
    {
        Jug_Number++;
        this_name = one_of_list(prefix) + one_of_list(suffix);
        Jug_Assignments[Jug_Number] = this_name;

        n--;
    }

    write("Generated!\n");

    JUG_MASTER->set_jug_assignments(Jug_Assignments);
    JUG_MASTER->set_name_assignments(Name_Assignments);

    return;
} /* generate_list */
