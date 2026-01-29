/*
 * angler.c
 *
 * Fisherman standing on the Cadu pier fishing, cadu_pier5.c'
 * Asking for baits from Khalakhor as quest.
 *
 * Treacher, Sept 2021
 */
#pragma strict_types

#include <macros.h>
#include <files.h>
#include <math.h>
#include "defs.h"

inherit ROKEDIR + "lib/monster";
inherit "/d/Khalakhor/common/npc/quest-npc";

#define QUEST_BAITS_NAME       "Cadu baits"
#define QUEST_EG_ENTRANCE_NAME "Eil-Galaith Entrance" 
#define QUEST_RAN_SEED         9598534
#define QUEST_RAN_RANGE        3

#define I_TOTAL_BAITS_REQUESTED            5
#define I_LARGE_BAITS_REQUESTED            1
#define QUEST_I_ROKE_ANGLER_QUEST_ACTIVE   "_quest_i_roke_angler_quest_active"
#define QUEST_I_ROKE_ANGLER_TOTAL_BAITS    "_quest_i_roke_angler_total_baits"
#define QUEST_I_ROKE_ANGLER_LARGE_BAITS    "_quest_i_roke_angler_large_baits"

string *baits = ({"grugg limb", "white maggot", "catalpa worm"});
string *baits_big = ({"long grugg limb", "fat white maggot", "fat catalpa worm"});
string *fish = ({"cariscan devilfish", "silvery herring", "nyreesean bass"});
string *responses_option0 = ({ 
    "say I heard some fishing stories about the cariscan " +
        "devilfish, very rare and only found near Carisca." ,
    "smile",
    "say But it rumours they only bite on bait of leftovers " +
        "from some creature called grugg on Carisca island. "+
        "Apparently their limbs are tasteful for the devilfish.",
    "say And from what I've heard about that island, I'm not " +
        "sure I dare to go there myself to try and fetch some " +
        "of those limbs.",
    "say So if you could bring me some grugg limbs I would " +
        "be very grateful. I think five should be enough.",
    "say Oh, bring me at least one long limb! "+
        "Just to be safe."});
string *responses_option1 = ({ 
    "say I ate some barbecued herrings here at the local " +
        "Inn and they were very delicious." ,
    "smile",
    "say So I thought I would try and catch some herrings " +
        "here and bring home.",
    "say But it seems they don't like my bait. I got some nice " +
        "info from a fellow angler that white maggots are good bait " +
        "for the herrings. And that they can be found in the forest " +
        "of Eil-Galaith.",
    "say So if you could bring me some white maggots I would " +
        "be very grateful. I think five should be enough.",
    "say Oh, bring me at least one fat maggot! "+
        "Just to be safe."});
string *responses_option2 = ({ 
    "say I came here to try and catch the nyreesean bass, "+
        "which can only be found in these waters. And I " +
        "brought my lucky bait with me from home in Port Macdunn, " +
        "some catalpa worms.",
    "sigh",
    "say But I couldn't resist trying some deep sea fishing " +
        "from the ship while sailing here. So I used them all up.",
    "say And now it seems I am all out of luck.",
    "say If you could bring me some catalpa worms I would be "+
        "very grateful. Five should be enough, being my lucky bait " +
        "and all.",
    "say Oh, actually bring me at least one fat worm! "+
        "I reckon I have never failed with a fat catalpa."});

mapping quest_responses = ([0: responses_option0, 1: responses_option1, 2: responses_option2]);

string *
my_quests ()
{
  return ({ QUEST_BAITS_NAME });
}

int
get_quest_option()
{
    string name = TP->query_real_name();
    int q_option = NAME_TO_RANDOM(name, QUEST_RAN_SEED, QUEST_RAN_RANGE);

    // If the player gets the white maggot in Eil-Galaith forest
    // check if the player has done the entrance quest.
    // If not, change option to the last option
    if(q_option == 1 &&
       !quest_done(QUEST_EG_ENTRANCE_NAME))
    {
        q_option = 2;
    }

    return q_option;
}

void
answer_bait()
{
    command("say There are many good baits to be found. One of my favourites is " +
        "the catalpa worm. Maybe not necessarily the best one around, but my " +
        "lucky bait that I've caught some of my biggest fish with. You can " +
        "find them in the forests north of Port Macdunn, if you are lucky. " +
        "Just search the trees.");
    set_alarm(4.0, 0.0, &command("say Then of course the white maggots, they are " +
        "quite good as well. Can also be found in the trees, but in the forest " +
        "of Eil-Galaith."));
    set_alarm(8.0, 0.0, &command("say Oh and recently I heard about some creature " +
        "called grugg, that's supposed to be found on Carisca island. Their " +
        "limbs are nice bait, I was told."));
}

void
setup_acting()
{
    set_act_time(5);
    add_act("say Mornin'!");
    add_act("say Nice day for fishing, aint it?");
    add_act("chuckle");
    add_act("emote looks over his fishing rod that everything is in order.");

    add_ask(({"help", "task", "quest"}),
            "@@answer_quest");
    add_ask(({"bait", "baits"}), answer_bait, 1);

    add_ask(({"worm", "worms", "catalpa worm", "catalpa worms"}),
            "say The catalpa worm is one of my favourite baits, I am always lucky " +
            "using it. I usually find them in the forests at home, north of " +
            "Port Macdunn. Just search the trees and you might find some if " +
            "you are lucky.", 1);
    add_ask(({"maggot", "maggots", "white maggot", "white maggots"}),
            "say The white maggots are nice bait. They can be found in the forest " +
            "of Eil-Galaith. Just search the trees and you might find some if " +
            "you are lucky.", 1);
    add_ask(({"grugg", "gruggs", "limb", "limbs", "grugg limb", "grugg limbs"}),
            "say I was recently told about the gruggs, supposedly they can be found " +
            "on the island Carisca. Their limbs are said to be a nice bait. But " +
            "I assume they don't just drop limbs freely.", 1);
    set_default_answer("say Oh sorry, my mind is focused on the fish at the moment.", 1);
}

/*
 * Stops the fisherman from acting and responding to questions while
 * busy with longer conversations.
 */
void
pause_acting()
{
    clear_act(); 
    remove_asks();
    set_default_answer("The fisherman seems busy at the moment to answer any questions.");
}

string
answer_quest()
{
    if(!quest_done(QUEST_BAITS_NAME))
    {
        int q_option = get_quest_option();

        if(!TP->query_prop(QUEST_I_ROKE_ANGLER_QUEST_ACTIVE)) 
        {
            mixed quest = get_quest_by_name(QUEST_BAITS_NAME);
            
            pause_acting();
            command("say Yes, actually I could use some help!");
            set_alarm(2.0, 0.0,  &command(quest_responses[q_option][0]));
            set_alarm(5.0, 0.0,  &command(quest_responses[q_option][1]));
            set_alarm(8.0, 0.0,  &command(quest_responses[q_option][2]));
            set_alarm(12.0, 0.0, &command(quest_responses[q_option][3]));
            set_alarm(16.0, 0.0, &command(quest_responses[q_option][4]));
            set_alarm(20.0, 0.0, &command(quest_responses[q_option][5]));  

            TP->add_prop(QUEST_I_ROKE_ANGLER_QUEST_ACTIVE, 1);
            log_quest(quest["bit"], TPQN, "Started quest, option " + q_option);
            
            set_alarm(21.0, 0.0, &setup_acting()); 
        }
        else
        {
            int total_delivered = TP->query_prop(QUEST_I_ROKE_ANGLER_TOTAL_BAITS);
            int large_delievered = TP->query_prop(QUEST_I_ROKE_ANGLER_LARGE_BAITS);
            if(total_delivered < I_TOTAL_BAITS_REQUESTED && large_delievered < I_LARGE_BAITS_REQUESTED)
            {
                command("say Yes, I believe you agreed to bring me " + 
                        LANG_NUM2WORD(I_TOTAL_BAITS_REQUESTED - total_delivered) + 
                        " more " + LANG_PWORD(baits[q_option]) + ". Of which at least one " +
                        "should be big.");
            }
            else if(total_delivered < I_TOTAL_BAITS_REQUESTED)
            {
                command("say Yes, I believe you agreed to bring me " + 
                        LANG_NUM2WORD(I_TOTAL_BAITS_REQUESTED - total_delivered) + 
                        " more " + LANG_PWORD(baits[q_option]) + ". A big one I already got.");
            }
            else
            {
                command("say Yes, I got all but a big one.");
            }
        }
    }
    else
    {
        command("say Yes thank you, I very much appreciate you helping me out before!");
    }
}

void
give_back(object what, object who, string say)
{
    command("say " + say);

    if (!command("give " + what->query_pname() + " to " + OB_NAME(who)))
        command("drop " + what->query_pname());
}

/*
 * Called to reward exp for the angler quest
 */
void
quest_reward()
{
    //EXP TIME
    //Double check that the player don't have the qbit set already
    if(!quest_done(QUEST_BAITS_NAME))
    {
        mixed quest = get_quest_by_name(QUEST_BAITS_NAME);

        if (!quest)
        {
            command("say Something strange happened. "+
                    "You should alert the authorities.");
            log_quest(-1, TPQN, "reward out of turn", "error");
            return;
        }
        do_reward_player(quest["bit"], quest["xp"], 0, "You feel a little more experienced!");
      }
}

/*
 * Fishing sequence after the angler has received all the requested baits
 */
void
lets_fish(int q_option)
{
    pause_acting();
    command("say Ok, the fish isn't waiting!");
    command("smile expectantly");
    set_alarm(1.0, 0.0, &command("emote slides a " + baits[q_option] + " on the hook of his long fishing rod."));
    set_alarm(2.0, 0.0, &command("emote cocks his arm back and then whips the long fishing rod " +
                                 "forward, casting his line."));

    set_alarm( 7.0, 0.0, &command("emote gives a small tug on his line."));
    set_alarm(12.0, 0.0, &command("emote continues to reel in his line."));
    set_alarm(17.0, 0.0, &command("emote reels in his line and it seems like " +
                                  "they've caught a spiky bloatfish!"));
    set_alarm(18.0, 0.0, &command("emote mumbles: Bloatfish.. Not was I was hoping for."));
    set_alarm(21.0, 0.0, &command("emote mumbles: Mustn't get my hopes up too high.. " +
                                  "I'll go with the bigger one right away."));

    set_alarm(22.0, 0.0, &command("emote slides a " + baits_big[q_option] + " on the hook of his long fishing rod."));
    set_alarm(23.0, 0.0, &command("emote cocks his arm back and then whips the long fishing rod " +
                                  "forward, casting his line."));

    set_alarm(28.0, 0.0, &command("emote gives a small tug on his line."));
    set_alarm(33.0, 0.0, &command("emote continues to reel in his line."));
    set_alarm(38.0, 0.0, &command("emote reels in his line and it seems like " +
                                  "they've caught a " + fish[q_option] + "!"));
    
    switch(q_option)
    {
    case 0:
        set_alarm(40.0, 0.0, &command("blink"));
        set_alarm(42.0, 0.0, &command("asay excitedly A cariscan devilfish!"));
        set_alarm(44.0, 0.0, &command("asay excitedly The stories were true!"));
        set_alarm(45.0, 0.0, &command("dance"));
        set_alarm(47.0, 0.0, &command("asay excitedly I did it, I caught a cariscan devilfish!"));
        set_alarm(49.0, 0.0, &command("say Those grugg limbs sure knew how to lure!"));
        break;

    case 1:
        set_alarm(40.0, 0.0, &command("smile"));
        set_alarm(42.0, 0.0, &command("say Ah what a lovely herring!"));
        set_alarm(44.0, 0.0, &command("say They will appreciate these when I get back home."));
        set_alarm(45.0, 0.0, &command("dance"));
        set_alarm(47.0, 0.0, &command("say A really nice catch!"));
        set_alarm(49.0, 0.0, &command("say Those maggots sure knew how to lure!"));
        break;

    default:
        set_alarm(40.0, 0.0, &command("blink"));
        set_alarm(42.0, 0.0, &command("say A nureesan bass?"));
        set_alarm(44.0, 0.0, &command("asay excitedly A nureesan bass!"));
        set_alarm(45.0, 0.0, &command("asay excitedly I did it, I caught a nureesan bass!"));
        set_alarm(47.0, 0.0, &command("dance"));
        set_alarm(49.0, 0.0, &command("say I knew the catalpa wouldn't fail me!"));
        break;
    }

    set_alarm(53.0, 0.0, &command("say Thank you so much for helping me."));
    set_alarm(54.0, 0.0, &command("smile"));
    //Quest done, reward exp
    set_alarm(55.0, 0.0, &quest_reward());
    set_alarm(55.0, 0.0, &setup_acting());

}

/*
* Called when checks have passed that the received object 
* is the correct bait.
*/
void
receive_worm(int amount, int is_large)
{
    int q_option = get_quest_option();
    int total_delivered = TP->query_prop(QUEST_I_ROKE_ANGLER_TOTAL_BAITS) + amount;

    string say, sayBig = "";
    if(amount == 1)
    {
        say = "Oh a " + baits[q_option] + ", thanks!";
        sayBig = "A big one even.";
    }
    else
    {
        say = "Oh some " + LANG_PWORD(baits[q_option]) + ", thanks!";
        sayBig = "And big ones at that.";
    }

    command("say " + say);
    if(is_large)
    {
        command("say " + sayBig);
        TP->inc_prop(QUEST_I_ROKE_ANGLER_LARGE_BAITS, amount);
    }
    command("smile");
    TP->add_prop(QUEST_I_ROKE_ANGLER_TOTAL_BAITS, total_delivered);

    //Check status if everything has been delivered
    if(total_delivered < I_TOTAL_BAITS_REQUESTED)
    {
        string sayBig = "";

        if(TP->query_prop(QUEST_I_ROKE_ANGLER_LARGE_BAITS) < I_LARGE_BAITS_REQUESTED)
        {
            sayBig = " But don't forget to bring me a large one.";
        }
        command("say Now I only need " + LANG_NUM2WORD(I_TOTAL_BAITS_REQUESTED - total_delivered) + " more!" + sayBig);
        return;
    }
    else if(TP->query_prop(QUEST_I_ROKE_ANGLER_LARGE_BAITS) < I_LARGE_BAITS_REQUESTED)
    {
        command("say Only missing a large one!");
        return;
    }
    else
    { 
        command("say That should be enough, now I can't fail to catch the " + fish[q_option] + "!");

        TP->remove_prop(QUEST_I_ROKE_ANGLER_QUEST_ACTIVE);
        TP->remove_prop(QUEST_I_ROKE_ANGLER_TOTAL_BAITS);
        TP->remove_prop(QUEST_I_ROKE_ANGLER_LARGE_BAITS);

        set_alarm(4.0, 0.0, &lets_fish(q_option));
        return;
    }
}

void
create_monster()
{
    set_name("fisherman");
    add_name("angler");
    set_adj("weatherbeaten");
    set_short("weatherbeaten fisherman");
    set_long("An old seasoned fisherman. His weatherbeaten face shows signs " +
             "of many days and nights fighting his pray, fish.\n" +
             "He is holding a long fishing rod in both hands.\n" +
             "He is wearing a bait satchel on his waist.\n" +
             "He is an expert fishing hobbyist.\n");
    set_race_name("human");

    default_config_npc(20);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    NEVERKNOWN;

    add_prop(OBJ_M_NO_ATTACK, "The fisherman holds up his fishing rod against you "+
            "and you get the feeling that this fisherman can not be beaten.\n");

    setup_acting();
}

public void
enter_inv(object ob, object from)
{
    int q_option = get_quest_option();

    ::enter_inv(ob, from);
    if (!objectp(ob) || !objectp(from))
        return;

    string ob_name = OB_NAME(ob);

    if(!ob->query_bait_value()) 
    {
        //Don't want items that isn't bait
        set_alarm(1.0, 0.0, &give_back(ob, from, "Thank you, but I'm trying to fish here."));
        return;
    }
    else if(!TP->query_prop(QUEST_I_ROKE_ANGLER_QUEST_ACTIVE))
    {
        //Give back the bait if quest is not active
        set_alarm(1.0, 0.0, &give_back(ob, from, "That is some nice bait, but I think you may need it more."));
        return;
    }
    else if( !( q_option == 0 && ob->id("_grugg_limb")) &&
             !( q_option == 1 && ob->id("_white_maggot")) &&
             !( q_option == 2 && ob->id("_catalpa_worm")) )
    {
        //Only want the correct option of bait
        set_alarm(1.0, 0.0, &give_back(ob, from, "Nice bait, but it ain't what I'm looking for now."));
        return;
    }
    else if(TP->query_prop(QUEST_I_ROKE_ANGLER_LARGE_BAITS) == 0 &&
            TP->query_prop(QUEST_I_ROKE_ANGLER_TOTAL_BAITS) >= (I_TOTAL_BAITS_REQUESTED-1) &&
            !ob->is_big())
    {
        //Received all normal worms, only waiting for a large one
        set_alarm(1.0, 0.0, &give_back(ob, from, "Thanks, but you have given me enough. Only need the large one now."));
        return;
    }
    
    set_alarm(1.0, 0.0, &receive_worm(ob->num_heap(), ob->is_big()));
    set_alarm(2.0, 0.0, &ob->remove_object());
}
