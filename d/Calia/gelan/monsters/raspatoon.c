
/*
   Raspatoon Goldiloon, the alchemist of Gelan
   This npc hands out potions for the alchemist quest in Gelan.
   He is also part of the polymorph quest, giving advice about how
   to defeat the creature and mixing a brew for the player that
   is for use in the quest.

   This guy can also "expand your consciousness" for a price,  
   he gives you a potion which, when quaffed, adds a double emote 
   object. 

   Coder: Maniac

   Revision history:
        5/08/03    added routine for accepting ore           Jaacar
                   and giving bullion for Thalassian
                   Staff quest                               
        13/6/97    added reply to box, pink potion           Maniac
        08/2/97    Added reply_hand, reply_moss,
                   and reply_recharge support for the
                   Calian Sup. Guru Quest.                   Khail
        31/5/96    trigs removed                             Maniac
        24/9/95    typo corrected                            Maniac 
        28.2.95               Created                        Maniac

*/

#undef PINK_POTION
#pragma save_binary
#pragma strict_types

inherit "/std/monster";
inherit "/lib/trade";
inherit "/d/Genesis/lib/intro";
inherit "/d/Calia/std/npc_receive";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <files.h>
#include "/d/Calia/gelan/monsters/monster.h"
#include "/d/Calia/eldoral/guru_quest.h"

inherit STD_AIDED;
#include HAUNT_CODE
#include ALCHEMIST_QUEST
#include POLYMORPH_QUEST

#define LIVE_I_GOT_ORE     "_live_i_got_ore"
#define LIVE_I_GOT_BULLION "_live_i_got_bullion"
#define LEFTOVER_BELT      "/d/Calia/std/leftover_pack"

int has_side_effect(object tp);

string uselab = 
          "say You may use my laboratory to find a cure for " +
          "yourself! Good luck! Now I must try to find " +
          "out where I went wrong in my mixing of that potion."; 


/* These globals are for the alchemist quest */
mapping given_potion = ([ ]);
int busy = 0;
int reacting = 0;
string last_guinae_pig = ""; 


/* This global is for the polymorph quest */
string *given_brew = ({ });


void
create_monster() 
{
  if (!IS_CLONE)
    return;
  set_name("raspatoon");
    set_living_name("raspatoon");
  add_name("alchemist");
  add_name(ALCHEMIST_NAME);
  add_name("shopkeeper");
  set_race_name("human");
  set_adj(({"ancient","inscrutable"}));
  set_title("Goldiloon the Alchemist");
  set_long("Raspatoon Goldiloon has reached the remarkable age of " +
       "1035 years, and boy, he looks it.. if dust could take " +
       "human shape it would describe Raspatoon perfectly. " +
       "Because of his great age, he is the town's greatest " +
       "source of wisdom on many matters, but prefers to keep quiet " +
       "about it, because he is as naturally helpful as an untamed camel. " +
       "He is the town alchemist and has survived every single one of "+
       "his numerous experiments, a real feat considering the power " +
       "of some of the explosions that have rocked his " +
       "laboratory. Raspatoon is usually either on the look out " +
       "for new guinea-pigs to use in his experiments or trying to " +
       "work out why his latest experiment went horribly or " +
       "comically wrong.\n"); 

  default_config_npc(60);
  set_base_stat(SS_INT,175);
  set_base_stat(SS_WIS,175);
  set_hp(5000);
  set_skill(SS_UNARM_COMBAT, random(20) + 35);
  set_skill(SS_DEFENCE, random(10) + 50);
  set_skill(SS_AWARENESS, random(10) + 50);
  set_alignment(50 + random(100));
  add_act("@@ras_chat1");
  add_act("@@ras_chat2");
  add_act("@@ras_chat3"); 
  add_act("@@ras_chat4");
  add_act("@@ras_chat5");
  add_act("emote says: I can turn ore into bullion!");
  add_act("emote says: This belt of pouches works great!");
  set_act_time(5);

  add_ask(({"assistant", "experiment", "latest experiment", "potion", 
            "green potion", "assistant in an experiment", "interested"}),
            VBFC_ME("reply"), 1);
  add_ask(({"advice", "for advice", "demon", "about demon", 
            "polymorph demon", "about polymorph demon", "polymorph", 
            "about polymorph" }), 
            VBFC_ME("reply_advice"), 1);
  add_ask( ({ "belt", "pouch", "belt of pouches", "components", 
              "leftovers", "component", "leftover" }),
            VBFC_ME("reply_belt"), 1);
  add_ask( ({ "amjal" }),
            "@@reply_academic", 1);
                      
#ifdef PINK_POTION
  add_ask(({ "tin box", "box", "pink potion", "slot", "tube" }), 
            VBFC_ME("reply_box"), 1); 
#endif

#ifdef GURU_OPEN
  add_ask(({"hand of the king", "about hand of the king",
            "about the hand of the king", "king's hand",
            "about king's hand", "about the king's hand",
            "hand of a king", "about hand of a king",
            "about the hand of a king"}), VBFC_ME("reply_hand"), 1);
  add_ask(({"vampiric moss", "about vampiric moss"}),
            VBFC_ME("reply_moss"), 1);
  add_ask(({"recharge", "to recharge", "recharge gauntlet",
            "to recharge gauntlet", "recharge king's hand",
            "to recharge king's hand", "recharging",
            "about recharging"}),
            VBFC_ME("reply_recharge"), 1);
#endif

  set_default_answer(VBFC_ME("default_reply"));
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
  
  // Initialize the parameters for /lib/trade.c
  config_default_trade();
  setuid();
  seteuid(getuid());  
}


/* Default reply */
string
default_reply()
{
   if (reacting) return "";

   if (this_player()->query_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON)) {
       command("say Hmm? What you're asking does not make sense to me.");
       return "";
   }

   if (has_side_effect(this_player())) {
       command("say Don't expect me to help you find a cure, " +
               "I'm busy with other things! You'll have to " +
               "work it out for yourself in my lab.");
       return "";
   }
   if (busy) {
       command("say I'm busy. And you're not making any sense."); 
       return "";
   }
   else {
       command("say Hmm, I hope your babbling at me means " +
               "that you might be interested in being my " +
               "assistant in an experiment.");
       return "";
   }
}


/* React to player having gender change side-effect */
void
g_change_react(object tp, int i)
{
    if (!present(tp, environment(this_object()))) {
         reacting = 0; 
         return; 
    }

    switch (i) { 
        case 0: command("emote looks extremely crestfallen.");
                break;
        case 1: command("say Yet another experiment gone badly " +
                    "wrong, " + tp->query_name() + "!");
                break;
        case 2: command("say You seem to be having a serious " + 
                  "gender identity problem after drinking " +
                  "that potion, " + tp->query_name() + ".");
                break;
        case 3: command(uselab);
                break;
    }
    if (i < 3) 
        set_alarmv(4.0, 0.0, "g_change_react", ({tp, i+1}) );
    else 
        reacting = 0;
}


/* React to player having weakened stat side-effect */
void
weaken_react(object tp, int i)
{
    if (!present(tp, environment(this_object()))) {
         reacting = 0;
         return; 
    }

    switch (i) { 
        case 0: command("emote jumps up and down in frustration!");
                break;
        case 1: command("say Another failed experiment, another " +
                    "silly side-effect, " + tp->query_name() + "!");
                break;
        case 2: command("say My powers of observation tell me " + 
                  "that you aren't quite the person you were, " +
                  tp->query_name() + ", after drinking that " +
                  "potion.");
                break;
        case 3: command(uselab);
                break;
    }
    if (i < 3) 
        set_alarmv(4.0, 0.0, "weaken_react", ({tp, i+1}) );
    else
        reacting = 0;
}


/* React to player having stutter side-effect */
void
stutter_react(object tp, int i)
{
    if (!present(tp, environment(this_object()))) {
         reacting = 0;
         return; 
    }

    switch (i) { 
        case 0: command("ack");
                break;
        case 1: command("say Well, the potion certainly doesn't " +
                  "seem to have done what it was supposed to " +
                  "do, " + tp->query_name() + ".");
                break;
        case 2: command("say By the nervous contortions of your " + 
                  "jaw muscles, " +  tp->query_name() + ", it " +
                  "would appear that you have a bad case " +
                  "of stuttering as a result of drinking that " +
                  "potion.. hmm.."); 
                break;
        case 3: command(uselab);
                break;
    }

    if (i < 3) 
        set_alarmv(4.0, 0.0, "stutter_react", ({tp, i+1}) );
    else
        reacting = 0;
}



/* React to player having been cured */
void
cure_react(object tp, int i)
{
    if (!present(tp, environment(this_object()))) {
         reacting = 0;
         return; 
    }

    switch (i) { 
        case 0: command("say Ah, " + tp->query_name() + 
                        " you're cured! Congratulations!");
                break;
        case 1: command("grin");
                break;
    }

    if (i < 1) 
        set_alarmv(2.0, 0.0, "cure_react", ({tp, i+1}) );
    else
        reacting = 0;
}



/* Control reaction to a player who has a side effect caused by 
   potion or who has been successfully taken a cure. 
*/
void
react(object tp)
{
    mixed s;

    if (tp->query_prop(AQ_CURE_SUCCESS)) {
        tp->remove_prop(AQ_CURE_SUCCESS);
        reacting = 1;
        set_alarmv(1.0, 0.0, "cure_react", ({tp, 0}));
        if (last_guinae_pig == tp->query_name())
            last_guinae_pig = "";
    }
    else {
        s = tp->query_prop(AQ_EXPERIMENT_FAILURE);
        if (!s) return;
        last_guinae_pig = tp->query_name();
        tp->remove_prop(AQ_EXPERIMENT_FAILURE); 
        reacting = 1;
        busy = 1;
        set_alarm(itof(AQ_BUSY_PERIOD), 0.0, "stop_busy");
        if (s == "stutter")
            set_alarmv(1.0, 0.0, "stutter_react", ({tp, 0}));
        else if (s == "weaken")
            set_alarmv(1.0, 0.0, "weaken_react", ({tp, 0}));   
        else if (s == "g_change")
            set_alarmv(1.0, 0.0, "g_change_react", ({tp, 0}));
    }
}



/* Stop being busy */
void
stop_busy()
{
    command("say Eureka! I think I see where I went wrong!");
    command("emote quickly mixes a new potion.");
    busy = 0;
    given_potion = ([ ]);
}

/* Reply if someone's asking about the belt of pouches */
string
reply_belt()
{
    object tp = this_player();
    
    if (!tp)
    {
        return "";
    }
    
    return ("say I have just the thing you are looking for! I've been "
          + "experimenting with a way to sort and store my more ... umm "
          + "... gruesome components. If you want one, just <pay> me, and "
          + "I'd be happy to sell you one.");
}

/* Reply if someone's asking for advice about the polymorph demon. */
string
reply_advice()
{
    object tp = this_player();

    if (!tp)
        return "";

    if (tp->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT)) {
         return "ponder wasting one's time.";
    }

    if (present(CORPSE_NAME, tp))
        return ("say I see that you have the polymorph's corpse on you! " +
                "So what the hell do you want my advice about defeating it " +
                "for?");

    if (member_array(tp->query_real_name(), given_brew) > -1) 
        return ("say Didn't I make a brew for you a while ago? Your " +
                 "progress seems to be rather backward! " +
                 "And I don't feel like repeating free advice to " + 
                 "dimwits!");

    if (tp->query_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON)) 
         return ("say Ah, I see, you want advice about defeating a " +
             "polymorph demon. Not so easy, that. Vicious " +
             "buggers, they are, and incredibly smart too. " +
             "Anyway, if you want to defeat " +
             "one you'll have to nullify all its strengths. You'll " +
             "need a shield that is forged from a steel ore mixed with " +
             "a magical brew. Such a shield will protect you from the " +
             "creature's magical attacks. I can make such a brew for you, " +
             "but you'll need to bring me the residues from each of " +
             "the demon's attacks, and a chipping from a magical stone " +
             "(to provide an intense magic source). Return to me " +
             "when you are <ready>.");

   if (has_side_effect(tp)) 
       return ("say Don't expect me to help you find a cure, " +
               "I'm busy with other things! You'll have to " +
               "work it out for yourself in my lab.");
   if (busy) 
       return ("say Don't bother me now! Can't you see I'm busy?" + 
               " Please come back later!");
   else 
       return "shrug"; 
}


#ifdef PINK_POTION
string
reply_box()
{
    if (reacting) 
        return ""; 

    return ("say Oh my tin box dispenses a type of potion I knocked " +
            "together a while ago. Its effects are quite consciousness " +
            "expanding, and not at all dangerous!"); 
}
#endif


/*
 * Function name: reply_hand
 * Description  : Reacts to someone asking about the hand of the 
 *                king for the calian sup. guru quest. Uses guru
 *                quest defines
 *                    LIVE_I_GURU_QUESTING
 *                    C_GURU_DRAGON
 *                    C_GURU_KROM
 *                    C_GURU_RASPATOON
 * Arguments    : n/a
 * Returns      : A string, the command to perform in response.
 */
public string
reply_hand()
{
    object who;
    int state;
    string name; 

    who = this_player();
    state = who->query_prop(LIVE_I_GURU_QUESTING);
    name = lower_case(who->query_real_name());

    if (reacting)
        return "";

  /* Do nothing if the player isn't a calian. */
    if (!IS_GURU_CALIAN(who))
        return "";

  /* Say nothing if the player hasn't been to the dragon yet.*/
    if (!state)
    {
        return ("whisper " + name + " Ahh, an interesting item " +
            "indeed, but that's a story for another time.");
    }

  /* Say no more if the player has talked to Raspatoon already. */
    if (state & C_GURU_RASPATOON)
    {
        return ("whisper " + name + " I've already told you " +
            "all I can. When you've gathered what you need, " +
            "return to me and ask me to recharge it.");
    }

  /* Has the player been to Krom yet? */
    if (!(state & C_GURU_KROM))
    {
        return ("whisper " + name + " Hmm, it sounds familiar, " +
            "but I can't quite put my finger on it. Maybe " +
            "someone else could give you some details to " +
            "clarify it for me?"); 
    }

  /* The real response, if a player has been to the dragon and */
  /* Krom both. */
    if (state & (C_GURU_KROM | C_GURU_DRAGON))
    {
        who->add_prop(LIVE_I_GURU_QUESTING, state | C_GURU_RASPATOON);
        command("whisper " + name + " It sounds familiar, " +
            "do you know any details about it?");
        who->command("$whisper raspatoon Krom told me it was " +
            "some sort of gauntlet with special powers.");
        command("brighten");
        return ("whisper " + name + " Ahh, of course, the " +
            "King's Hand! It's a little-known piece of " +
            "legend, a gauntlet that could be used to " +
            "crush almost any metal. If you're looking for " +
            "it, you should know it will require recharging " +
            "after all this time. If you bring the gauntlet " +
            "and a special herb called vampiric moss, I " +
            "should be able to do it for you.");
    }

    return "";
}


/*
 * Function name: reply_moss
 * Description  : Reacts to being asked about vampiric moss.
 *                Uses guru quest defines
 *                    LIVE_I_GURU_QUESTING
 *                    C_GURU_DRAGON
 *                    C_GURU_KROM
 * Arguments    : n/a
 * Returns      : A string containing the command string to
 *                execute in response.
 */
public string
reply_moss()
{
    object who;
    int state;
    string name;

    if (reacting)
        return "";

    who = this_player();
    name = lower_case(who->query_real_name());
    state = who->query_prop(LIVE_I_GURU_QUESTING);

  /* Do nothing if the player isn't calian. */
    if (!IS_GURU_CALIAN(who))
        return "";

  /* Is the player doing the guru quest? */
    if (!(state & C_GURU_DRAGON))
        return ("whisper " + name + " Ahh, an interesting " +
            "story, but for another time.");

  /* Player's just asking about the moss, so it won't matter */
  /* whether he's been to Krom or not. Just for the sake of */
  /* convenience, don't worry about checking to see if the */
  /* player's already asked about the moss, either. */
    return ("whisper " + name + " Vampiric moss? Afraid I " +
        "don't know much about it, really, but perhaps someone " +
        "who's more familiar with that could tell you more.");
}


/*
 * Function name: reply_recharge
 * Description  : What to do when Raspatoon is asked to recharge
 *                the gauntlet in the calian guru quest.
 *                Uses guru quest defines
 *                    LIVE_I_GURU_QUESTING
 *                    C_GURU_GAUNTLET_NAME
 *                    C_GURU_MOSS_NAME
 * Arguments    : n/a
 * Returns      : String to execute as a command() in response.
 */
public string
reply_recharge()
{
    object who,
           gauntlet,
           moss;
    string name;
    int state;

    if (reacting)
        return "";

    who = this_player();
    name = lower_case(who->query_real_name());
    state = who->query_prop(LIVE_I_GURU_QUESTING);
    gauntlet = present(C_GURU_GAUNTLET_NAME, who);
    moss = present(C_GURU_MOSS_NAME, who);

  /* Do nothing if the player isn't calian. */
    if (!IS_GURU_CALIAN(who))
        return "";

  /* Of course, do nothing if the player is missing either the */
  /* gauntlet or moss. */
    if (!gauntlet || !moss)
    {    
        return ("whisper " + name + " I'm sorry, but you don't " +
            "have the things I need for that.");
    }

  /* Make sure the moss can be taken from the player. */
    if (moss->move(TO, 1))
        return ("whisper " + name + " I can't seem to get " +
            "the moss from you for some reason.");

  /* Ok, player has gauntlet and moss, time to recharge. */
    command("whisper " + name + " Amazing, so that's the " +
        "King's Hand? And vampiric moss, too. You've been " +
        "busy! Well, let's get to work. The process is " +
        "simple, it will only take a moment.");
    write(query_The_name(TP) + " carefully takes the moss from " +
        "your possession with a long pair of tweezers.\n");
    say(QCTNAME(TO) + " takes something from " + QTNAME(who) +
        " with a long pair of tweezers.\n");
    tell_room(environment(), QCTNAME(TO) + " drops it in a " +
        "small flask full of a clear liquid, tamping it " +
        "with the tweezers until the liquid turns blood red.\n");
    write(query_the_name(TP) + " takes the gauntlet from you.\n");
    say(QCTNAME(TO) + " takes something else from " + 
        QTNAME(who) + ".\n");
    tell_room(environment(), QCTNAME(TO) + " holds it over a " +
        "flame for a moment, then quickly pours the red liquid " +
        "over it. The room fills with the stench of blood as " +
        "the liquid evaporates into a red steam that soon " +
        "fades.\n");
    write(query_The_name(TP) + " gives you back the gauntlet.\n");
    say(QCTNAME(TO) + " gives it back to " + QTNAME(who) + ".\n");
    moss->remove_object();
    gauntlet->set_charged();
    command("smile " + name);
    return ("whisper " + name + " There you go, good luck with "+
        "whatever you're trying to do with it!");
}


/* Reply to someone asking about the experiment */
string
reply()
{
    object tp = this_player();

    if (reacting) return "";
    if (busy) {
        command("say Don't bother me now! Can't you see I'm busy " +
               "trying to work out why my last experiment failed " +
               "and how my assistant, " + last_guinae_pig +  
               ", ended up with silly side-effects? " +
               "Please come back later!");
        return "";
    }
    else {
        command("say Ah, I'm glad you ask, dear " + tp->query_name() +
          ". I am currently testing a potion that I have " + 
          "been developing for quite a while (and I've faced " +
          "quite a few hitches I can tell you). But I think " +
          "I've perfected " +
          "it now, touch wood. The intention of the potion " +
          "is that it will permanently give the drinker " +
          "three times his or her normal strength. Yes, I " +
          "know this sounds ambitious, but if anyone can " +
          "do it, Raspatoon can! If you would like to " +
          "be my guinea-pig, er I mean assistant, in the " +
          "experimental testing, just `accept assistantship'."); 
          return "";
     }
}


string
ras_chat1()
{
    if (reacting) return "";
    if (!busy)
        return "say I've been working on this darn potion for " +
                "ages now, it had better work this time!"; 
    else 
        return "emote seems to be pondering something deeply, " +
                "with a worried expression on his face."; 
}

string
ras_chat2()
{
    if (reacting) return "";
    if (!busy)
        return "say I am looking for an assistant for my latest " +
                "experiment.";
    else if (last_guinae_pig != "")
        return "emote mutters to himself: " + last_guinae_pig + 
                " got some embarassing side-effects " +
                "when i screwed up last time.";
}

string
ras_chat3()
{
    if (reacting) return "";
    if (!busy)
        return "say My latest potion should be able to triple the " +
                "strength of whoever drinks it!";
    else 
        return "emote scribbles some alchemical symbols in a " +
               "notebook.";
}

string
ras_chat4()
{
    if (reacting) return "";
    if (!busy)
        return "say Hmm, I wonder whether green is such " +
                "a good colour for that potion if I want it " +
                "to sell well.";
    else
        return "emote frowns in deep concentration."; 
}

string
ras_chat5()
{
    if (reacting) return "";
    if (!busy)
        return "emote stirs a green potion with a thin glass rod.";
    else
        return "emote ponders whether the planets are in correct " +
               "alignment."; 
}


int
has_side_effect(object tp)
{
    if (present(STUTTER_NAME, tp) ||
        tp->has_weaken_stat_shadow() ||
        tp->has_g_change_shadow())
        return 1;
    else
        return 0;
}


/* Accept assistantship */
int
do_accept(string str)
{
    object tp = this_player();
    string nm = tp->query_name();
    string *things = ({});
    object p;

    if (str != "assistantship") { 
        notify_fail("Accept what? Assistantship?\n");
        return 0;
    }

   tell_room(environment(this_object()), QCTNAME(tp) + " tells " +
             QTNAME(this_object()) + " that " + tp->query_pronoun() +
             " would like to work as an assistant.\n", tp);
   tp->catch_msg("You tell " + QTNAME(this_object()) + " that " +
                 "you would like to work as an assistant.\n");
  
   if (this_object()->query_attack()) {
       command("say Er, as you can see, I'm a little tied up now, " +
               nm + "."); 
       return 1;
   }
            
   if (busy) {
       command("say I'm not looking for assistants right " +
               "now, can't you see I'm busy? Please come back " +
               "later.");
       return 1;
    }

    if (tp->test_bit(AQ_DOM, AQ_GROUP, AQ_BIT)) {
        command("say Ah, but now I remember that you've helped me " +
                "before, " + nm + ", and I never accept the same " +
                "assistant twice. The last time I did he.. er.. " +
                "well I'd best not go into that.");
        return 1;
    }

    if (tp->query_stat(SS_CON) < AQ_MIN_CON) {
        command("say Actually, now that I think about it " +
                nm + ", you look a little on the feeble side, " +
                "thus I think your constitution might " +
                "not take kindly to drinking a powerful " + 
                "potion. Please do come back when you're " +
                "somewhat tougher and I may still have some " +
                "work for you!");
        return 1;
    }

    if (has_side_effect(tp)) {
        command("say Er.. " + nm + ", you're currently suffering " +
             "from side-effects from the last potion you drank, " +
             "I don't think it would be wise to drink a new one " +
             "just yet, even if this one probably will work."); 
        return 1;
    }

    int last_time_given = given_potion[nm];
    if (time() - last_time_given < 3600) {
        command("say " + nm  + ", I've given you a potion " +
                "very recently, I don't give these things " +
                "out like candy you know!");
        return 1;
    }

    if (tp->query_soaked() > AQ_MAX_SOAKED)
        things += ({"drink"});
    if (tp->query_stuffed() > AQ_MAX_STUFFED) 
        things += ({"food"});
   
    if (sizeof(things)) {
        command("say Well, " + nm + ", at a guess " +
                "I would say that you have too much " + 
                COMPOSITE_WORDS(things) + " in your belly, " +
                "since this potion is meant to be drunk on an " +
                "empty stomach. Please come back and re-accept " +
                "when you have a fairly empty belly.");
        return 1;
    }
    else {
        command("say Excellent, " + nm + ", " +
                "I think you will make a fine assistant!");
        seteuid(getuid());   
        p = clone_object(GELAN_OBJECTS + "green_potion");
        p->move(this_object());
        if (!command("give potion to " + lower_case(nm))) {
            command("say I can't seem to give this potion to " +
                    "you, " + nm + ".");
            p->remove_object();
            return 1;
        }
        else {
            given_potion[nm] = time();
            command("say I really hope it works this time!");
            return 1;
        }
    }
}



/* Player is ready with ingredients to make magical brew for 
   polymorph quest */
int
do_ready()
{
    object tp = this_player();
    object acid, ice, fire, chipping, brew;

    if (!tp)
        return 0;

    tp->catch_msg("You proclaim: `Ready!'\n"); 
    tell_room(environment(this_object()), QCTNAME(tp) + " proclaims: " +
              "`Ready!'\n", tp);

    if (tp->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT)) {
         command("ponder wasting one's time.");
         return 1;
    }

    if (present(CORPSE_NAME, tp)) {
        command("say You are more than ready, you've killed the damn " +
                "thing!");
        return 1;
    }

    if (tp->query_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON))  {
        acid = present(ACID_NAME, tp);
        ice = present(ICICLE_NAME, tp);
        fire = present(CHARCOAL_NAME, tp);
        chipping = present(CHIPPING_NAME, tp); 

        if (member_array(tp->query_real_name(), given_brew) > -1)  {
            command("scratch");
            command("say Didn't I make a brew for you a while ago?");
        }

        if ((!objectp(acid)) || (!objectp(ice)) ||
            (!objectp(fire))) {
            command("say Hmm, I said _all_ the residues, remember.");
            return 1;
        }

        if (!objectp(chipping)) {
            command("say You don't have a chipping from a magical stone!");
            return 1;
        }

        seteuid(getuid());
        brew = clone_object(PQ_BREW);
        brew->move(tp);
        if (!present(BREW_NAME, tp)) {
            command("say You're carrying too much to receive the brew " +
                    "when I make it, dummy.");
            brew->remove_object();
            return 1;
        }

        tell_room(environment(this_object()), QCTNAME(this_object()) + 
                 " takes the ingredients from " + QTNAME(tp) + ".\n", tp);
        tp->catch_msg(QCTNAME(this_object()) + " takes the ingredients " +
                      "from you.\n");
        acid->remove_object();
        ice->remove_object(); 
        fire->remove_object();
        chipping->remove_object();
    
        command("emote skilfully mixes a strange brew."); 
        tp->catch_msg(QCTNAME(this_object()) + " gives " + LANG_ASHORT(brew) +
                      " to you.\n");
        tell_room(environment(this_object()), QCTNAME(this_object()) + 
                      " gives " + LANG_ASHORT(brew) +
                      " to " + QTNAME(tp) + ".\n", tp);
            
        command("say When the shield is made it must have a special jewel " +
              "called a `sapphire of draining' set in its centre. The " +
              "jewel will drain the creature of its transformational " +
              "energies " +
              "while the shield protects you. I'm not sure where you " +
              "can obtain such a jewel, they are extremely rare and " +
              "extremely valuable. " +
              "Anyway, once you have got this s.o.d, take it, along " +
              "with the brew, to someone skilled in forging shields, " +
              "and ask him for help.");
        command("ponder");
        command("say Well, that's about it, you may as well s.o.d off.");
        if (member_array(tp->query_real_name(), given_brew) == -1)
            given_brew += ({tp->query_real_name()});
        return 1;
    }
        
    command("peer " + tp->query_real_name());
    return 1;
}

int
do_pay()
{
    object tp, belt;
    mixed  results;
    
    tp = this_player();
    
    results = pay(100);
    if (!pointerp(results) || sizeof(results) != 9)
    {
        // When someone correctly pays, the pay function returns an
        // array of 9.
        command("say You can't seem to afford this belt. I put in a lot "
              + "work to make it. Can't just give it away for free, you "
              + "know!");
        command("say Come back when you have more money.");
        return 1;
    }
    
    write("You pay Raspatoon for the belt of pouches.\n");
    // If the player successfully paid, then we give them the belt
    belt = clone_object(LEFTOVER_BELT);
    belt->move(this_object(), 1);
    command("give belt to " + tp->query_real_name());
    if (environment(belt) == this_object())
    {
        command("hmm");
        command("say Well, I can't seem to give this belt to you. Let "
              + "me drop this on the ground for you to pick up later.");
        command("drop belt");
    }
    
    return 1;
}

void
accept_ore(object ore, object tp)
{
    object bullion;
    string name;

    name = tp->query_real_name();

    command("smile");
    command("emote says: Yes, I can do something with this!");
    ore->add_prop(OBJ_M_NO_STEAL,1);
    if (tp->query_prop(LIVE_I_GOT_BULLION))
    {
        command("emote says: I already gave you bullion.");
        return;
    }
    command("emote drips some chemicals on the ore. In a brilliant "+
        "flash of light it becomes a cylinder of bullion.");
    bullion = clone_object(GELAN_OBJECTS+"silver_bullion");
    bullion->move(TO);
    command("emote says: Here you go. Perhaps you can find a smithy "+
        "that would like that.");
    command("give bullion to "+name);
    tp->remove_prop(LIVE_I_GOT_ORE);
    tp->add_prop(LIVE_I_GOT_BULLION,1);
    // Remove the ore now.
    ore->remove_object();
}

void
drop_stuff(object ob)
{
     if (!objectp(ob))
         return;

     command("emote looks curiously at " + LANG_THESHORT(ob) + "."); 
     command("shrug");
     command("emote says: What would I want this for?");
     if (IS_HEAP_OBJECT(ob) && ob->num_heap() > 1)
     {
        command("drop " + sprintf("%d", ob->num_heap()) + " " + ob->plural_short());
     }
     else
     {
        command("drop " + OB_NAME(ob));
     }
}

void
do_smile()
{
    command("smile");
}

void
do_give_pouch()
{
    command("smile broadly");
    command("say Do come back and tell me how it works for you!");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    // The npc_receive module handles receiving multiple items.    
    receive_enter_inv(ob, from);
    
    if (!objectp(from))
    {
        // To give these items out, they are first cloned and brought into
        // Raspatoon's inventory
        if (ob->id("_cylinder_of_silver_bullion_"))
        {
            set_alarm(1.0, 0.0, &do_smile());
        }
        else if (ob->id("_raspatoon_leftovers_belt"))
        {
            set_alarm(1.0, 0.0, &do_give_pouch());
        }    
    }     
}

/* add action for players  */
void
init_living()
{
    ::init_living();
    add_action(do_accept, "accept");
    add_action(do_ready, "ready");
    add_action(do_pay, "pay");
}

// Handle Academy of Elemental Arts Task 3

// Defines for Academics
#define ACADEMIC_MANAGER     "/d/Calia/guilds/academics/lib/academy_manager"
#define IS_ACADEMIC(x)       ACADEMIC_MANAGER->query_is_member(x)
#define TASK_THREE_GIVEN       "_academic_task_three_given"
#define RASPATOON_ACADEMIC_TASK_GIVEN   "_raspatoon_academic_task_given"

/*
 * Function:    should_accept_item
 * Description: Returns whether the item should be accepted at this time.
 */
public int
should_accept_item(object obj, object from)
{
    if (from->query_prop(RASPATOON_ACADEMIC_TASK_GIVEN))
    {
        // Special exception for the potion task for Academics
        // Academics need to bring back an eye (leftover), drudgeworth (herb),
        // and ouzo (alcohol/drink).
        if (IS_LEFTOVER_OBJECT(obj) && obj->id("eye"))
        {
            return 1;
        }
        if (IS_HERB_OBJECT(obj) && obj->query_herb_name() == "drudgeworth")
        {
            return 1;
        }
        if (IS_DRINK_OBJECT(obj) && obj->id("ouzo"))
        {
            return 1;
        }
    }
    else if (obj->id("_raw_silver_ore_"))
    {
        return 1;
    }
    
    return 0;
}

public void
report_task_3_progress(object player)
{
    string * parts = ACADEMIC_MANAGER->query_potion_parts_collected(player);
    string * all_parts = ({ "eye", "drudgeworth", "ouzo" });
    string * remaining_parts = all_parts - parts;
    
    if (!sizeof(remaining_parts))
    {
        command("say Ahh, you've brought me everything now.");
        command("say So, normally you might need a mortar and pestle to grind "
            + "the herb and perhaps the leftover, as well as an empty vial to "
            + "mix the resulting powder with the ouzo.");
        command("say Since you do not have those items or the skill to really "
            + "do anything with them... Allow me. Pay attention.");
        command("emote puts the herb and the leftover into the pestle "
            + "and continues to grind it into a pungent black gooey mixture.");
        command("emote pours the mixture into the vial followed by the ouzo.");
        command("emote grins as he shakes the vial rapidly.");
        
        object potion = clone_object("/d/Calia/guilds/academics/objs/task_3_potion");
        potion->set_owner_name(player->query_real_name());
        potion->move(player, 1);
        player->catch_msg(QCTNAME(this_object()) + " gives you a white-black "
            + "bubbly potion.\n");
        command("say Now then. You can taste or smell potions to get an idea "
            + "of what they are.");
        command("say The rest.. you'll figure out if you ever become talented "
            + "enough for such features, student.");
        command("say Go give that to Amjal, and leave me to my work.");
        // Reset the components collected in case they need to get the potion again
        ACADEMIC_MANAGER->set_potion_parts_collected(player, ({ }));
    }
    else
    {
        command("say You are still missing these items for your task: " 
            + COMPOSITE_WORDS(remaining_parts) + ".");
    }
}

/*
 * Function:    hook_process_accept_items
 * Description: Redefine this to process all the accepted items
 * Arguments:   mapping items - this is a mapping of the person who gave
 *                              the item to the objects that they gave.
 *                              eg. ([ player : ({ sword }) ])
 */
public void
hook_process_accept_items(mapping items)
{
    foreach (object player, mapping objs : items)
    {
        string * parts = ACADEMIC_MANAGER->query_potion_parts_collected(player);
        object * duplicate = ({ });
        object * used_parts = ({ });
        foreach (object obj : m_indexes(objs))
        {   
            if (!objectp(obj))
            {
                continue;
            }
            if (obj->id("_raw_silver_ore_"))
            {
                // This is for the staff of Aeria quest
                set_alarm(1.0, 0.0, &accept_ore(obj, player));                
                continue;                
            } 
            if (IS_LEFTOVER_OBJECT(obj) && obj->id("eye"))
            {
                if (IN_ARRAY("eye", parts))
                {
                    duplicate += ({ obj });
                }
                else
                {
                    parts += ({ "eye" });
                    used_parts += ({ obj });
                }
            }
            if (IS_HERB_OBJECT(obj) && obj->query_herb_name() == "drudgeworth")
            {
                if (IN_ARRAY("drudgeworth", parts))
                {
                    duplicate += ({ obj });
                }
                else
                {
                    parts += ({ "drudgeworth" });
                    used_parts += ({ obj });
                }
            }
            if (IS_DRINK_OBJECT(obj) && obj->id("ouzo"))
            {
                if (IN_ARRAY("ouzo", parts))
                {
                    duplicate += ({ obj });
                }
                else
                {
                    parts += ({ "ouzo" });
                    used_parts += ({ obj });
                }
            }            
        }
        if (sizeof(duplicate))
        {
            command("say You've already brought me enough of these. I don't "
                + "need any more.");
            duplicate->move(environment(this_object()), 1);
            command("emote drops " + COMPOSITE_DEAD(duplicate) + ".");
        }
        if (sizeof(used_parts))
        {
            ACADEMIC_MANAGER->set_potion_parts_collected(player, parts); 
            report_task_3_progress(player);
            used_parts->remove_object();
        }
    }
}

/*
 * Function:    hook_process_unaccept_items
 * Description: Redefine this to process all the unaccepted items
 * Arguments:   mapping items - this is a mapping of the person who gave
 *                              the item to the objects that they gave.
 *                              eg. ([ player : ({ sword }) ])
 */
public void
hook_process_unaccept_items(mapping items)
{
    foreach (object player, mapping objs : items)
    {
        foreach (object obj : m_indexes(objs))
        {
            set_alarm(0.5, 0.0, &drop_stuff(obj));
        }
    }
}

public string
reply_academic()
{
    object player = this_player();
    // Academics who are working on their second task should get a proper
    // respons. Everyone else should get the default response
    if (ACADEMIC_MANAGER->query_completed_task_3(player))
    {
        command("say I certainly hope you learned a lot from Amjal since. You "
            + "did a mighty fine job with the task that I gave you.");
        return 0;
    }
    else if (!IS_ACADEMIC(player)
             || !ACADEMIC_MANAGER->query_completed_task_2(player)
             || !player->query_prop(TASK_THREE_GIVEN))
    {
        return default_reply();
    }
    
    if (!player->query_prop(RASPATOON_ACADEMIC_TASK_GIVEN))
    {
        player->add_prop(RASPATOON_ACADEMIC_TASK_GIVEN, time());        
        command("say Another one of you students eh?");
        command("say Think you can learn anything about potion making? Well.");
        command("say You don't have the skill for anything potent, but just to get "
            + "you started... let's see.");
        command("say Come back here with an eye, which is a leftover, a "
            + "drudgeworth, a herb found on the moorlands and buy me some "
            + "ouzo from Argos.");
        command("say Now go. Stop bothering me until you get these items and "
            + "give them to me.");
    }
    else if (present("academic_raspatoon_potion", player))
    {
        command("say You've already completed your task! Go give the potion "
            + "to Amjal.");
    }
    else
    {
        command("say Have you collected everything you need? Give them "
            + "to me if you have.");
        report_task_3_progress(player);
    }
    
    return 0;
}
