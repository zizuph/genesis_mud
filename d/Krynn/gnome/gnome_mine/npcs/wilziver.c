/*
	Crazy old miner gnome
	Wilziver Quodon

    Quest giver for the miner pickaxe that enables you to mine any rocky terrain.

    Made by: Maelstrom, 2016/05/18


    TODO
    add 500 exp when completed. (check)
    if quest is already solved and you ask for pickaxe again, he asks to be paid for one.

*/


inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <files.h>

#include <cmdparse.h>

#include "../defs.h"

/* Prototypes */
public void        show_hook(object ob);
public void        react_items(object obj, object to);
public void        introduce(object who);

string
gnome_speak(string str)
{
    string * data;
    string newStr = "";

    data = explode(str, " ");
    for (int i = 0; i < sizeof(data); ++i)
    {
        newStr = newStr + capitalize(data[i]);
    }
    return newStr;
}

int
player_solved_quest(object tp)
{
    int questIsDone = 0;
    if (tp->test_bit("Krynn", PICKAXE_GROUP, PICKAXE_BIT))
    {
        questIsDone = 1;
    }
    return questIsDone;
}

int
player_has_pickaxe(object tp)
{
    object *obSearch = FIND_STR_IN_OBJECT("miner_pickaxe", tp);
    return sizeof(obSearch) > 0;
}

/*
 * Function name:        intro_check
 * Description  :        Lets shorten the spam by having him intro if
 *                       the player doesn't know him yet.
 * Arguments    :        object who - the player
 * Made by      :        Gorboth
 */
void
intro_check(object who)
{
    if (!IN_ARRAY(this_object()->query_real_name(),
         m_indices(who->query_introduced())))
    {
        command("say " + gnome_speak("First, introductions are in order.\n"));
        command("introduce myself");
        command("\n\n");
    }
}

void
create_monster() 
{
    if (!IS_CLONE)
        return;
    set_name("wilziver");
    set_living_name("wilziver");
    add_name("miner");
    set_race_name("gnome");
    set_adj(({"crazy","old"}));
    set_title("Quodon the Guru Miner");
    set_long("Wilziver Quodon has lived most of his life underground, " +
            "looking for valuable treasure and adventures. " +
            "It came with a price though, since he lost more than time " +
            "in the old tunnels, he lost his sanity. " +
            "He now toils away in rememberance of old days, being the world greatest expert on " +
            "mining, and a great tinkerer in itself too; he's always scheming plans for a new invention.\n"); 

    default_config_npc(100);
    set_base_stat(SS_STR,300);
    set_base_stat(SS_INT,175);
    set_base_stat(SS_WIS,175);
    set_hp(5000);
    set_skill(SS_UNARM_COMBAT, random(20) + 60);
    set_skill(SS_DEFENCE, random(10) + 50);
    set_skill(SS_AWARENESS, random(10) + 90);
    set_alignment(50 + random(100));


    add_ask( ({ "quest", "mining", "pickaxe", "mine", "task", "help", "treasure", "adventures", "components" }),
        "@@reply_pickaxe", 1);

    add_ask( ({ "bit_clear" }),
        "@@bit_clear", 1);

    add_ask( ({ "clockwork", "clockwork parts" }),
        "say " + gnome_speak("You might find some in my junk pile, lots of spare parts there; but you will " +
        "have to <disarm> them to get the clockwork.\n"), 1);

    add_ask( ({ "pencil", "shovel", "abacus", "toothbrush" }),
        "say " + gnome_speak("Broken beyond repair; but you can <disarm> it to get clockwork parts.\n"), 1);

    add_ask( ({ "tubes", "tube", "diamond reinforced tubes", "diamond reinforced tube" }),
        "say " + gnome_speak("I don't think I have any left here, but if you find some tubes, " +
        "you can use my tube reinforcer, along with a diamond, to make them.\n"), 1);

    add_ask( ({ "pickaxe head", "shaft" }),
        "say " + gnome_speak("No idea, there should be some around here though.\n"), 1);

    add_ask( ({ "miniature lava engine", "lava engine", "engine" }),
        "say " + gnome_speak("I first created that as means to power my inventions, specially my figurines. " +
        "But i don't have any in stock right now.\n"), 1);

    add_ask( ({ "lava tank", "tank" }),
        "say " + gnome_speak("I invented that as means to safely store lava, VERY popular on weapons, now that i think about it. " +
        "But i don't have any in stock right now.\n"), 1);

    add_ask( ({ "old carpet", "carpet" }),
        "say " + gnome_speak("What? that piece of fabric? ahhh, to make a long story short, a sultan from a far away land " +
        "gifted me this old carpet, I helped him with some contraptions of mine, and I got it in return, " +
        "supposedly it can fly if you wish it; Reminds me I should make deals on pen & paper beforehand.\n"), 1);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    add_prop(OBJ_M_NO_ATTACK, "@@attack_gnome");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "@@attack_gnome");

    set_act_time(40);
    set_chat_time(60);
    add_act("emote draws schematics for a new invention.");
    add_act("emote looks through the pile of junk, saerching for something.");
    add_act("emote tinkers with a few clockwork components.");
    add_act("emote laughs crazily.");
    add_chat("If only i had more components!");
    add_chat("Maybe you can help me with something?");
    add_chat("That's the best you can do Raswin? you can only copy my work!");

    setuid();
    seteuid(getuid());
}

void
finish_pondering()
{
    this_player()->catch_msg("After taking a minute, you decide you no longer wish to attack the gnome.\n");
}

string
attack_gnome()
{
    object paralyze;
    int ponder_alarm;

    seteuid(getuid());
    paralyze = clone_object("/std/paralyze");
    paralyze->set_stop_verb("stop_being_a_jackass");
    paralyze->set_combat_stop(1);
    paralyze->set_stop_message("You stop pondering.\n");
    paralyze->set_remove_time(60);
    paralyze->set_fail_message("You are pondering on your acts. " +
        "Act like it!\n");
    paralyze->move(this_player(),1);

    ponder_alarm = set_alarm(60.0, 0.0, &finish_pondering());

    return "You just can't bring yourself to do it, " +
            "you pity the old gnome, he has nothing of value on him and " +
            "looks as frail as a statue of dust.\n" +
            "Suddenly you have an epifany and realize how much time " +
            "you have wasted doing pointless acts like this one in the past.\n" +
            "You take a minute to ponder on your acts.\n";
}

/* 
  Reply if someone's asking about the pickaxe
*/
string
reply_pickaxe()
{
    object tp = this_player();
    
    if (!tp)
    {
        return "";
    }

    intro_check(tp);

    if (!player_solved_quest(tp))
    {
        if (tp->query_prop(GNOME_MINE_QUEST))
        {
            return("say " + gnome_speak("I need: a pickaxe head, a shaft, a miniature lava engine, a lava tank, diamond reinforced " +
                    "tubes and four piles of clockwork parts. Ask me about each particular part if you have further inquiries about them. " +
                    "If you can find and bring all this to me, I'll make sure you get your pickaxe.\n"));
        }
        else
        {
            tp->add_prop(GNOME_MINE_QUEST, 1);

            command("say " + gnome_speak("Ahhhh, so we have a novice miner here, do we? did you come looking for my famous pickaxe? " +
                    "It's the only way to really do anything on your own, the common pickaxe is just obsolete, " +
                    "who has years to dig anymore? But you are too late, I'm all sold out. Sorry.\n"));
            command("emote looks into the horizon, pondering.\n");
            return("say " + gnome_speak("Wait. Perhaps there's a way; I think I got the spare parts to make one around here, " +
                    "you would need: a pickaxe head, a shaft, a miniature lava engine, a lava tank, diamond reinforced " +
                    "tubes and four piles of clockwork parts. Ask me about each particular part if you have further inquiries about them. " +
                    "If you can find and bring all this to me, I'll make sure you get your pickaxe.\n"));
        }
    }
    else
    {
        if (!player_has_pickaxe(tp)){
            string *random_phrases =
                ({ 
                    "rub your nose against the wall",
                    "lick your shoes",
                    "drag you around in my backpack",
                    "drink lemonade",
                    "rob a bank",
                    "salute you",
                    "praise the lord",
                    "launch a counter offensive",
                    "run againt the wall repeteadly",
                    "use you as a coffee machine"
                });

            return("say " + gnome_speak("Hey, you lost Ramona! I should "+one_of_list(random_phrases)+" for that! " +
                    "Lucky for you, I found the parts to make a new one, but it's going to cost you! " +
                    "5 platinum for a brand new lava-powered pickaxe! you can <pay> me if you have the coin. " +
                    "I like shiny things, so i only accept platinum coins.\n"));
        }
        else
        {
            return("say " + gnome_speak("You already have my pickaxe, what else could you need from me?\n"));
        }
    }
}

string
bit_clear()
{
    object tp = this_player();
    
    if (!tp)
    {
        return "";
    }

    tp->clear_bit(PICKAXE_GROUP, PICKAXE_BIT);
    return("say Bit cleared");
}

/*
 * Function name:        complete_payment
 * Description  :        See if the player has the right number of
 *                       platinum coins for the transaction. If not,
 *                       we let them know.
 * Arguments    :        string skill - the name of the skill to adapt,
 *                       object who - the player trying to pay
 *                       int needed - the number of plats it will cost
 * Returns      :        int 1 - successful payment made
 *                           0 - not able to pay
 * Made by      :        Gorboth
 */
public int
complete_payment(object who, int needed)
{
    object  *inv_items = all_inventory(who);
    object  coin;
    object  temp_location;
    object  npc = this_object();

    foreach (object inv_item: inv_items)
    {
        if (inv_item->query_coin_type() == "platinum" &&
           (MASTER_OB(inv_item)) == "/std/coins")
        {
            coin = inv_item;
        }
    }

    if (!coin)
    {
        command("peer annoy " + who->query_real_name());
        command("say I said I need " + LANG_NUM2WORD(needed) + " platinum coins."
          + " You do not have any,"
          + " come back with shiny things in your pockets or dont come back at all!");
        return 0;
    }

    if (coin->num_heap() < needed)
    {
        command("peer patient " + who->query_real_name());
        command("say I said I need " + LANG_NUM2WORD(needed) + " platinum coins."
          + " Your " + LANG_NUM2WORD(coin->num_heap())
          + ((coin->num_heap() == 1) ? " coin is" : " coins are" )       
          + " not enough for such a marvelous invention!");
        return 0;
    }

    who->catch_tell("You pay " + needed + " platinum coins to "
      + npc->query_the_name(who) + ".\n");
    tell_room(environment(who), QCTNAME(who) + " pays some platinum"
      + " coins to " + QTNAME(npc) + ".\n", who);
    command("emote grins greedily.");
    command("say Perfect! Here's your trinket... I mean... THE best pickaxe ever made!");

    temp_location = clone_object("/std/room");
    coin->split_heap(needed);
    coin->move(temp_location);
    /* Clean up afterward. */
    temp_location->remove_object();

    return 1;
} /* complete_payment */

int
do_pay_pickaxe()
{
    object tp = this_player();
    object pick;
    
    if (!tp)
    {
        return 1;
    }

    if (player_solved_quest(tp))
    {
        if (!player_has_pickaxe(tp))
        {
            if (complete_payment(tp, PICKAXE_PRICE))
            {
                pick = clone_object(WEP_DIR + "miner_pickaxe");
                pick->move(tp);
                tp->catch_msg("You recieve THE pickaxe.\n");
            }
        }
        else
        {
            command("say " + gnome_speak("You already have my pickaxe, what else could you need from me?\n"));
        }
    }
    else
    {
        command("say " + gnome_speak("Pay me for what?\n"));
    }

    return 1;
}

/*
 * function name: show_hook
 * description  : this hook is called whenever an item is 'shown' to this
 *                living. It is shown by this_player().
 * arguments    : object ob - the object shown.
 * Made by      : Gorboth
 */
public void
show_hook(object ob)
{
    set_alarm(1.0, 0.0, &react_items(ob, this_player()));
} /* show_hook */

void
delayed_command(string txt)
{
    command(txt);
}

void
delayed_msg(string txt, object tp)
{
    tp->catch_msg(txt);
}

void
delayed_reward(object tp)
{
    object reward;
    reward = clone_object(WEP_DIR + "miner_pickaxe");
    reward->move(tp);
}

void
create_pickaxe(object tp)
{

    float timeLapse = 1.0;

    set_alarm(timeLapse, 0.0, &delayed_command("say " + gnome_speak("Ahhh, I see you found the pieces, "
            + "hand them over please, and stand back.\n")));
    timeLapse += 5.0;

    set_alarm(timeLapse, 0.0, &delayed_msg("You give the parts to the gnome.\n\n",tp));
    timeLapse += 3.0;

    set_alarm(timeLapse, 0.0, &delayed_command("emote grabs a hammer and jolts the shaft and pickhead together.\n"));
    timeLapse += 4.0;

    set_alarm(timeLapse, 0.0, &delayed_command("emote attaches one end of the tubes to the lava engine " +
                "and the other to the lava tank.\n"));
    timeLapse += 6.0;

    set_alarm(timeLapse, 0.0, &delayed_command("emote grabs some of the left over diamond pieces from the tube reinforcer " +
                "and fuses them with a special torch to the pickaxe head.\n"));
    timeLapse += 8.0;
    
    set_alarm(timeLapse, 0.0, &delayed_command("emote attaches both the lava engine and lava tank to the shaft.\n"));
    timeLapse += 4.0;

    set_alarm(timeLapse, 0.0, &delayed_command("emote makes a complicated work of art with the clockwork, " +
                "almost fusing inside the shaft and pickhead.\n"));
    timeLapse += 8.0;

    set_alarm(timeLapse, 0.0, &delayed_command("emote adds a switch for easy control.\n"));
    timeLapse += 3.0;

    set_alarm(timeLapse, 0.0, &delayed_msg("After a few minutes that feel like an eternity, " +
                "he shows you his finished work.\n\n",tp));
    timeLapse += 5.0;

    set_alarm(timeLapse, 0.0, &delayed_command("say " + gnome_speak("Diamond sharp, with 20 speeds, " +
            "and lava auto-loader tubes; more than a pickaxe, it's a beauty. This can take you a few " +
            "hundred meters underground in 10 seconds! Beat that Raswin!\n")));
    timeLapse += 11.0;

    set_alarm(timeLapse, 0.0, &delayed_command("emote throws a smoke bomb.\n"));
    timeLapse += 10.0;

    set_alarm(timeLapse, 0.0, &delayed_msg("But after the smoke dissipates, " +
            "he's still there; you wonder if that's how it was supposed to happen, or " +
            "he just forgot to escape.\n\n",tp));
    timeLapse += 8.0;

    set_alarm(timeLapse, 0.0, &delayed_command("say " + gnome_speak("Anywho, here! take it, it's yours, " +
            "free of charge, this time at least.\n")));
    timeLapse += 4.0;

    set_alarm(timeLapse, 0.0, &delayed_command("emote grins greedily.\n"));
    timeLapse += 3.0;

    set_alarm(timeLapse, 0.0, &delayed_msg("You recieve THE pickaxe.\n",tp));
    set_alarm(timeLapse, 0.0, &delayed_reward(tp));
    
}

/*
 * Function name:        react_items
 * Description  :        have the npc respond to a specific object
 * Arguments    :        object obj - the object that was shown
 *                       object tp  - the player who showed it
 */
public void
react_items(object obj, object tp)
{

    object  *phq;
    object  *sq;
    object  *leq;
    object  *ltq;
    object  *rtq;
    object  *cq;
    object  *ocq;

    object  *inv;


    if (obj->id("pickhead_quest") || obj->id("shaft_quest") || 
        obj->id("lava_engine_quest") || obj->id("lava_tank_quest") || 
        obj->id("reinforced_tubes_quest") || obj->id("clockwork_quest"))
    {
        phq = FIND_STR_IN_OBJECT("pickhead_quest", tp);
        sq = FIND_STR_IN_OBJECT("shaft_quest", tp);
        leq = FIND_STR_IN_OBJECT("lava_engine_quest", tp);
        ltq = FIND_STR_IN_OBJECT("lava_tank_quest", tp);
        rtq = FIND_STR_IN_OBJECT("reinforced_tubes_quest", tp);

        ocq = FIND_STR_IN_OBJECT("old_carpet_quest", tp);

        inv = all_inventory(tp);
        cq = filter(inv, &->id("clockwork_quest"));

        if (sizeof(phq) && sizeof(sq) && sizeof(leq) && sizeof(ltq) && sizeof(rtq) && sizeof(cq) > 3)
        {

            if (sizeof(ocq) > 0)
            {
                ocq[0]->remove_object();
            }

            phq[0]->remove_object();
            sq[0]->remove_object();
            leq[0]->remove_object();
            ltq[0]->remove_object();
            rtq[0]->remove_object();
            
            for (int i = 0; i < sizeof(cq); i++)
            {
                cq[i]->remove_object();
            }

            create_pickaxe(tp);

            tp->add_exp_quest(PICKAXE_QUEST_EXP);
            tp->set_bit(PICKAXE_GROUP, PICKAXE_BIT);
        }
        else
        {
            command("say " + gnome_speak("I see you found some of the pickaxe components, but you are still missing a few.\n"));
        }            
    }
}

/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 * Made by      :        Gorboth
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("emote narrows his eyes and goes back to his diagrams.");
        return;
    }

    command("introduce me");
} /* react_intro */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 * Made by      :        Gorboth
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */

/*
 * Function name:        init living
 * Description  :        set up some actions for the players who
 *                       enter the room
 */
public void
init_living()
{
    ::init_living();

    add_action(do_pay_pickaxe, "pay");
} /* init_living */