/*
* /d/Sparkle/area/jade/npc/runaway.c
* The Runaway, modeled on Varian's /d/Genesis/start/human/wild2/bandit/ban1.c
* Created 2017-01-25 by Martin Berka on Genesis MUD
*/

#include "../defs.h"

inherit "/d/Sparkle/area/bandit/npc/bandit";
inherit OBJ_DIR + "shared_functions"; //Common knowledge for quest
inherit OBJ_DIR + "burden"; //Speed limited for quest gauntlet

#include "../bandit_quest_constants.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <math.h>
#include "/d/Shire/common/make_money.h"
#include <wa_types.h> //For holding

/* Prototypes */
int     alarm_id,
        delayed_action,
        quest_mode; //States affecting NPC availability to other players:
        //0 - in bandit area, anyone can talk to them
        //1 - following player, unresponsive
        //2 - in gauntlet mode, unresponsive
        //3 - quest completed, happy and unavailable
string  quest_owner; //Name of player for quest_mode values 1-3
object  origan; //Copy of the bandit chief for gauntlet interaction

void add_introduced(string str);
void catch_say(string say_text);
void offer_evil_option(string player_name = "", int reentry = 0,
    object origan = 0);
void fail_token_test(object token);
void start_gauntlet();

/*
 * Function name: create_monster
 * Description  : NPC constructor
 */
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name(banname());
    add_name(QUEST_RUNAWAY);
    set_race_name("human");
    set_adj( ({emotelook(),physlook()}));
    set_stats( ({55, 55, 55, 45, 45, 55}), 40);
    MAKE_MONEY;
    set_alignment(-200);

    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_PARRY,40);
    set_skill(SS_DEFENCE,40);

    set_gender(G_MALE);

    delayed_action = 0;

    set_chat_time(18);

    add_chat("Give me all your money! Or else!");
    add_chat("Those idiots in Sparkle think they are so smart!");
    add_chat("What are you looking at!");
    add_chat("Don't get any funny ideas now!");
    add_chat("I work smarter, not harder! Now give me all that money you "
        + "worked so hard for!");
    add_chat("A bandit's life for me!");

    //Standard bandit responses appropriate for a runaway.
    add_ask( ({"task","tasks"}),
        "@@ask_task");
    add_ask( ({"help", "job"}),
        "@@ask_help");
    add_ask( ({"quest","quests"}),
        "@@ask_quest");
    add_ask( ({"money","coins","copper"}),
        "@@ask_money");
    add_ask( ({"sparkle","people"}),
        "@@ask_sparkle");
    add_ask( ({"adventurer","adventurers"}),
        "@@ask_adventurers");
    add_ask( ({"live","living","life"}),
        "@@ask_live");
    add_ask( ({"doctor", "mother"}),
        "@@ask_mother");
    add_ask( ({"bandit", "thief", "highwayman"}),
        "@@ask_bandit");

    add_ask( ({"female", "gender", "girl", "lady", "she", "sister", "daughter",
        "granddaughter", "woman"}),
        "@@ask_gender");


    set_act_time(20);

    add_act("stab sword");
    add_act("emote swings his hands in the air, attempting to swat a fly.");
    add_act("emote squints his eyes, looking at you suspiciously.");
    add_act("cough");
    add_act("laugh");

    set_alarm(0.5, 0.0, "arm_me");

    quest_mode = 0;

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    set_slots(W_BOTH);
}

/*
 * Function name: add_introduced
 * Description  : If player introduces, introduce back with "real" name
 */
void
add_introduced(string str)
{
    //DISABLED FOR TESTING
    /*if (!interactive(TP) || TP->query_met(query_name()))
    {
        return;
    }*/

    // IF QUEST NOT COMPLETED
    string player_name = query_living_name(TP);
    set_name(runaway_name(player_name));
    add_name(lower_case( runaway_name(player_name) ));

    set_alignment(0);
    command("introduce me to " + player_name + "");
}

/*
 * Function name: ask_gender
 * Description  : For half of players, the Runaway is female, while bandits are
 *      all male. If asked about gender, the "he" offers some very specific
 *      speculation.
 */
void
ask_gender()
{
    command("say What are you talking about? Us bandits are rough, tough "
        + "and very male! No place for a lady, not that one would not "
        + "be extremely welcome here.");
    if (runaway_gender( query_living_name(TP) ) == G_MALE)
    {
        return;
    }
    if(!TP->DID_RUN_QUEST())
    {
        return;
    }
    switch(random(4))
    {
    case 0:
        command("blush nervously");
        break;
    case 1:
        command("emote tries to chuckle, but fails.");
        break;
    case 2:
        command("emote gives a strangled laugh.");
        break;
    default:
    }
    command( "say Anyway, I haven't seen any around here - perhaps "
        + "if a strong one with an ambiguous name fell in love with the idea "
        + "of bandit life, cut her "
        + "hair and disguised herself, she could pass for one of us. If so, "
        + "she must really be wondering what she is doing here. "
        + (random(1) ? "A new recruit can't leave for three years."
        : "No one washes even though we're right by a river!" ) );
    switch(random(2))
    {
    case 0:
        command("emote catches himself and says no more.");
        break;
    case 1:
        command("say Anyway, off with you! And give me all your money!");
        break;
    default:
        command("Not that this happened! Now hand over your valuables "
            + "before I stab you!");
    }
}


/*
 * Function name: burden_release_effect
 * Description  : Override the burden.c dummy: When released, collapses and
 *      bandits recapture.
 * Arguments    : (int) 0 - optional parameter unused
 */
void
burden_release_effect(int repeat = 0)
{
    add_prop(OBJ_M_NO_GET, 1); //Player has to start over to carry again
    //Consider blocking chats

    helper->remove_object(); //Remove the paralysis

    if (quest_mode == 2) //If the gauntlet is active, this is a failure
    {
        tell_room(environment(),
            QCTNAME(TO) + " collapses. Bandits arrive and carry " + QTNAME(TO)
                +  " away.\n",
            TO);
        mob_return(1); //
        remove_object(); //Needs time to rest; unavailable for a while
        return;
    }
    mob_return(1);
    //Otherwise, sticks around.
}


/*
 * Function name: burden_started_hook
 * Description  : Set up recurring attack by Origan when burden is activated
 */
void burden_started_hook()
{
    set_alarm(4.0, 0.0, "recurring_injury");
}


/*
 * Function name: catch_say
 * Description  : Player may say things to the Runaway and receive responses.
 *      After delivering Token, player must say yes or no in response to
 *      question about identity of Dearest. After that, may deliver approximate
 *      message from Regrets. Finally, may return from delivering message to
 *      Hurt with final "come home" command. Quest stages are tracked via the
 *      Token.
 * Arguments    : string say_text - whatever came after "say"
 */
void catch_say(string say_text)
{
    if (TP->DID_RUN_QUEST())
    {
        return;
    }
    if (!delayed_action)
    {
        set_alarm(0.2, 0.0, &catch_say(say_text));
        delayed_action = 1;
        return;
    }
    else
    {
        delayed_action = 0;
    }

    int f_index;
    string f_role, f_gen;

    string player_name = query_living_name(TP);
    object token = present(QUEST_TOKEN + "_from_" + player_name, TP);
    if (!token)
    {
        return;
    }

    string test_value = token->query_prop("TOKEN_I_TEST");
    switch (test_value)
    {
    case "fail":
        fail_token_test(token);
        return;

    case "dearest":
        /* parse for apology; using wildmatch due to the large variety of
         * things players could put before or after the message.
         */
        /*string test_regrets;
        if (parse_command(say_text, environment(TP),
            "[your] %s [says] [he] [she] [is] 'sorry'", test_regrets))
        */

        say_text = lower_case(say_text);
        if (!wildmatch(regret_message(player_name , 1), say_text))
        {
            command("say Huh?");
            return;
        }

        token->add_prop("TOKEN_I_TEST", "regrets"); //"Regrets" phase done

        /* Provide message for Hurt */
        f_index = runaway_role_index(player_name, HURT);
        f_role = runaway_relation(player_name, f_index);
        command("say Really? I could almost go back. But to be sure, I "
            + "need to make things right with my " + f_role + ".");
        f_gen = (f_index % 2 ? "him" : "her");
        command("say Tell " + f_gen + " that " + hurt_message(player_name)
            + ". That's an awful message, I know, but we can talk properly in "
            + "person - if "
            + (f_gen == "him" ? "he" : "she") + " can stand to see me.");

        set_alarm(2.5, 0.0, &offer_evil_option(query_living_name( TP )) );
        return;

    case "regrets":
        f_index = runaway_role_index(player_name, HURT);
        f_role = runaway_relation(player_name, f_index);
        f_gen = (f_index % 2 ? "his" : "her");
        command("say Please tell my " + f_role + " that "
            + hurt_message(player_name) + ". After some of the things I "
            + "said, I feel I need " + f_gen + " permission to go back.");
        return;

    case "hurt":
        say_text = lower_case(say_text);
        if (wildmatch("come home*", say_text)
            || wildmatch("go home*", say_text)
            || wildmatch("come back*", say_text)
            || wildmatch("go back*", say_text)
            || wildmatch("come with me*", say_text)
            || wildmatch("follow me*", say_text))
        {
            command("say Alright.");
            TP->team_join(TO);
            TP->catch_msg(query_The_name(TP)
                + " starts to follow you.\n");
            quest_mode = 1;
            quest_owner = query_living_name(TP);

            start_gauntlet();
        }
        else
        {
            int h_index = runaway_role_index(player_name, HURT);
            string h_role = runaway_relation(player_name, h_index);
            command("say I don't understand - do you have an answer from my "
                + h_role + "?");
        }
        return;

    default:
        //The default (test knowledge of Dearest)
        say_text = lower_case(say_text);
        if (strlen(say_text) && say_text[strlen(say_text)-1]=='.')
            //Strip out end punctuation
        {
            say_text=say_text[..strlen(say_text)-2];
        }
        if (strlen(say_text) && say_text[strlen(say_text)-1]=='?')
        {
            say_text=say_text[..strlen(say_text)-2];
        }
        if (strlen(say_text) && say_text[strlen(say_text)-1]=='!')
        {
            say_text=say_text[..strlen(say_text)-2];
        }

        switch (lower_case(say_text))
        {
        case "affirmative":
        case "correct":
        case "definitely":
        case "i did":
        case "indeed":
        case "right":
        case "sure":
        case "true":
        case "yeah":
        case "yep":
        case "yes":
            if (test_value == token->query_prop("TOKEN_I_FROM")
                && member_array(QUEST_TOKEN + "_from_" + player_name,
                    token->query_names()) > - 1)
            {
                token->add_prop("TOKEN_I_TEST", "dearest");
                //("Dearest" phase is done

                command("emote relaxes, yet looks troubled.");

                int d_index = runaway_role_index(player_name, DEAREST);
                command("say Of course. I miss " + (d_index % 2 ? "him" : "her")
                + " too, not that I would want to see "
                + (d_index % 2 ? "him" : "her") + " here. Since you've spoken "
                + "to my family - anything else to pass along?");
            }
            else
            {
                command("shout Ha! A likely story!");
                fail_token_test(token);
                return;
            }
            break;
        case "did not":
        case "false":
        case "i didn't":
        case "i did not":
        case "nah":
        case "negative":
        case "no":
        case "not":
        case "nope":
        case "wrong":
            if ( test_value == token->query_prop("TOKEN_I_FROM") )
            {
                if (member_array(QUEST_TOKEN + "_from_" + player_name,
                    token->query_names()) > - 1)
                {
                    command("say Then where did you get it?");
                    fail_token_test(token);
                    return;
                }
                else
                {
                    command("say That's what I thought.");
                    return;
                }
            }
            else
            {
                if (member_array(QUEST_TOKEN + "_from_" + player_name,
                    token->query_names()) > - 1)
                {
                    command("emote relaxes, yet looks troubled.");

                    token->add_prop("TOKEN_I_TEST", "dearest");

                    int d_index = runaway_role_index(player_name, DEAREST);
                    command("say Of course not, this could only come from my "
                        + token->query_prop("TOKEN_I_FROM") + ". I miss "
                        + (d_index % 2 ? "him" : "her") + " too. "
                        + (d_index % 2 ? "He" : "She") + "'d be disappointed "
                        + "to see me here... I don't know if I'm cut out for "
                        +"this.");
                    command("say So you've spoken to my family - do they have "
                        + "anything else to <say>?");
                }
                else
                {
                    command("say That's what I thought. Well, run along! You "
                        + "can keep your valuables this time.");
                    return;
                }
            }
            break;
        default:
            int d_index = runaway_role_index(player_name, DEAREST);
            command("say Yes or no, was this given to you by my "
                + token->query_prop("TOKEN_I_TEST") + "?");
        }
    }
}


/*
 * Function name: check_good_completion
 * Description	: Checks that the player has completed quest by returning
 *      runaway
 */
void check_good_completion()
{
    object player = find_player(quest_owner);
    if (player->DID_RUN_QUEST())
    {
        return;
    }

    object new_room = environment(player);
    object family = present(QUEST_FAMILY, new_room);
    if (!family) //If player rushed out?
    {
        return;
    }
    quest_mode = 3; //Set quest state to "delivered"
    burden_release_effect();

    //Announce that runaway is feeling better and meeting family member
    tell_room(new_room, QCTNAME(TO) + ", who was leaning on " + QTNAME(player)
        + " stands up straight.\n", player);
    player->catch_msg(query_The_name(player) + " seems to feel better and "
        + "stands up straight, no longer leaning on you.\n");
    tell_room(new_room, QCTNAME(family) + " sees " + QTNAME(TO)
        + " and rushes forward.\n", TO);

    object token = present(QUEST_TOKEN + "_from_" + query_living_name(player),
        player);

    if (token && token->query_prop("TOKEN_I_TEST") == "hurt")
    {
        family->command("say You have our thanks for bringing "
            + runaway_name(query_living_name(player))
            + " back safely. We'll make sure the way back is safe. "
            + "Money is tight, but please accept these.\n");
        clone_object(OBJ_DIR + "jade_pear")->move(TP);
        clone_object(OBJ_DIR + "neh_fruit")->move(TP);
        write(family->query_The_name(TP) + " gives you a hard green fruit and "
            + "a grey shriveled fruit.\n");
        tell_room(new_room, QCTNAME(family) + " gives " + QTNAME(TP) +
            " some fruits.\n", TP);
        write(family->query_The_name(TP) + " whispers in your ear: "
            + "Not that I recommend you eat them, neither is "
            + "good for the mind. Still, quite popular! Also, feel free to "
            + "hang around the orchard - enter through the house and one of us "
            + "will let you in.\n");

        //Add quest bit and XP
        player->set_bit(RUN_Q_GROUP, RUN_Q_BIT);
        player->add_exp_quest(100);

        token->remove_object();
    }

    tell_room(new_room, QCTNAME(family) + " leads " + QTNAME(TO)
        + " away to rest.\n", TO);
    family->move(ROOM_DIR + "jade_attic", 1);
    remove_object(); //Moving to attic would require substantial complications
}


/*
 * Function name: enter_env
 * Description  : Wrapper for burden.c
 * Arguments    : (object) the destination
 *                (object) the old location
 */
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    burden_enter_env(dest, old);
}



/*
 * Function name: enter_inv
 * Description  : React to object entering inventory. Keep the ::
 *      (from the auction tent, /d/Sparkle/area/city/auction/npc/auctioneer.c
 * Arguments    : object given - the object entering our inventory.
 *                object old - wherever 'given' came from. This can be 0.
 */
void
enter_inv(object given, object old)
{
    if (!delayed_action)
    {
        ::enter_inv(given, old);
        set_alarm(0.1, 0.0, &enter_inv(given, old));
        delayed_action = 1;
        return;
    }
    else
    {
        delayed_action = 0;
    }

    if (!objectp(old) || !interactive(old)) //If not given by living
    {
        return;
    }
    if (given->query_prop(HEAP_I_IS) && given->num_heap()>1) //Receive 1 item
    {
        command("say What is this heap of stuff? Oh well, more for the loot "
            + "pile!");
        return;
    }
    string player_name = query_living_name(old);
    string *all_object_names = given->query_names();
    int player_token_index = token_index(player_name);
    string *tokens = TOKEN_NAMES;

    if (member_array(QUEST_TOKEN, all_object_names) > -1 &&
        member_array(tokens[player_token_index], all_object_names) > -1)
    {
        command("emote looks surprised.");
        command("emote glances around nervously, then leans toward you.");

        int d_index = runaway_role_index(player_name, DEAREST);
        string test_relation;

        if (random(3))
        {
            test_relation = runaway_relation(player_name, random(FAMILY_RANGE));
        }
        else
        {
            test_relation = given->query_prop("TOKEN_I_FROM");
        }
        given->add_prop("TOKEN_I_TEST", test_relation);

        command("say This old "
            + tokens[player_token_index] + "... Did my " + test_relation
            + " give this to you?");
        switch(random(2))
        {
        case 0:
            command("emote listens to what you have to <say>.");
            break;
        default:
            command("emote waits for you to <say> something.");
        }

        /* Make the token invisible and keep it with the player.
         * It serves as the status tracker for the remainder of the quest.
         * The player is less killable than the NPC, and this makes it easy for
         * all NPC's to see the state without managing some central file.
         * However, may need to enable saving, unless players can manage in
         * one sesssion. */
        given->add_prop(OBJ_I_INVIS, 1);
        given->add_prop(OBJ_I_NO_GIVE, 1);
        given->add_prop(OBJ_I_NO_DROP,1);
        given->add_prop(OBJ_I_NO_STEAL, 1);
        given->add_prop(OBJ_I_VOLUME, 0);
        given->add_prop(OBJ_I_WEIGHT, 0);
        given->add_prop(OBJ_I_VALUE, 0);
        given->set_no_show();
        given->move(TP, 1); //NO_GIVE and NO_DROP block regular move
    }
    else
    {
        command("say I have no idea what this is. Oh well, more for the loot "
            +"pile!");
    }
}

/*
 * Function name: init_living
 * Description  : When a living enters the environment: add_action for
 *      parsed <say>. Keep the ::init_living()
 */
void
init_living()
{
	 ::init_living();
	 //notify_player_entered();
     add_action(catch_say, "say");
     //init_burden();
}

/*
 * Function name: fail_token_test
 * Description  : Attack players who lie about who gave them the token.
 * Arguments    : object token - the token that was given (store failure)
 */
void
fail_token_test(object token)
{
    write("\n" + query_The_name(TP)
        + " attacks you!\n\n");
    tell_room(environment(TO), QCTNAME(TO)
        + " attacks " + QTNAME(TP) + ".\n", TP);
    attack_object(TP);
    token->add_prop("TOKEN_I_TEST", "fail");
}



/*
 * Function name: leave_env
 * Description  : Wrapper for burden.c
 * Arguments    : (object) the destination
 *                (object) the old location
 */
void
leave_env(object dest, object old)
{
    ::leave_env(old, dest);
    burden_leave_env(old, dest);
}


/*
 * Function name: offer_evil_option
 * Description  : Summon bandit leader and offer the evil version of the quest
 * Arguments    : (string) name of player to receive offer
 *                (int) Reentrant flag to spread out Origan's message
 *                (object) Origan object
 */
void
offer_evil_option(string player_name = "", int reentry = 0, object origan = 0)
{
    if (!reentry)
    {
        object origan = summon_origan(environment(TO));
        set_alarm(0.2, 0.0, &offer_evil_option(player_name, 1, origan));
        return;
    }

    string run_name = runaway_name(player_name); //Used in multiple statements
    int d_index = runaway_role_index(player_name, DEAREST);
    string dearest_relation = runaway_relation(player_name, d_index);
    object player = find_player(player_name);

    switch (reentry)
    {
    case 1:
        origan->set_title("the Bandit Chief");
        origan->command("introduce me to " + player_name);
        break;
    case 2:
        player->catch_msg(QCTNAME(origan) + " whispers in you ear: "
            + " Don't think I haven't heard of you, wandering around our turf. "
            + "Business with " + run_name + ", eh? No doubt to do with his "
            + "scum-skinned family. I couldn't believe my luck when he came "
            + "to us - one more bandit, one less bow shooting at us from the "
            + "trees. Knows all their secrets... in time, we could have a camp "
            + "in those woods again.\n");
        break;
    case 3:
        player->catch_msg(QCTNAME(origan) + " whispers in you ear: "
            + " Anyway, I don't need you "
            + "doing those fruitpickers any "
            + "favours - do one for me instead. Get this " + dearest_relation
            + " that he's so fond of and bring " + (d_index % 2 ? "him" : "her")
            + " here. We could always use some labour, and leverage both "
            + "against those pushy farmers and to keep " + run_name
            + " motivated. I'll pay you cash - I doubt "
            + "they can do the same when we have them cut off.\n");
        break;
    case 4:
    default:
        string kidnap_method = " It won't be easy - none of that "
            + "family would come here by choice. If I were you, I would ";
        switch (kidnap_index(player_name))
        {
        case K_CHOKE:
            kidnap_method += "choke " + (d_index % 2 ? "him" : "her")
                + ". Rather intimate, but it's worked for me. ";
            break;
        case K_KNOCK:
            kidnap_method += "whack " + (d_index % 2 ? "him" : "her")
                + ". Simple as that. ";
            break;
        case K_PEAR:
        default:
            kidnap_method += "throw one of those weird pears at "
                + (d_index % 2 ? "him" : "her") + ". That farm is too far from a "
                + "bar if you ask me. ";
        }
        player->catch_msg(QCTNAME(origan) + " whispers in you ear: "
            + kidnap_method + "Just make sure you get the dear "
            + dearest_relation + " and not some other that " + run_name
            + " could consider leaving behind!\n");
    }


    if (reentry < 4)
    {
        set_alarm(0.3, 0.0, &offer_evil_option(player_name, reentry + 1,
            origan));
    }
    else
    {
        set_alarm(0.5, 0.0, &remove_origan(origan));
    }
}


/*
 * Function name: new_room_hook
 * Description  : Checks each time player enters new room while carrying runaway
 *      - if outside Jade, summons bandits
 * Arguments    : (object) The player with the burden
 *                (object) The previous room
 *                (object) The newly entered room
 */
void
new_room_hook(object last_room, object new_room, object player)
{
    if (!wildmatch("*jade*", file_name(new_room) ))
    {
        set_alarm(0.5, 0.0, &mob_me( ({WILD_DIR + "bandit/npc/bandit.c",
                WILD_DIR + "bandit/npc/bandit2.c"
            }), query_living_name(player), 5, 3 ));
        return;
    }
    if (!wildmatch("*jade*", last_path ))
    {
        if (m_sizeof(mob_members))
        {
            object shouter = find_object(one_of_list( m_indexes(mob_members) ));
            tell_room(last_room, QCTNAME(shouter) + "shouts: Blast, that's a "
                + "tough one! "
                + "Alright boys, stay out of range!\n");
            player->catch_msg("Someone in the mob shouts: Blast, that's a "
                + "tough one! "
                + "Alright boys, stay out of range!\n");
        }
    }
    if (present(QUEST_FAMILY, new_room))
    {
        check_good_completion();
    }
}


/*
 * Function name: recurring_injury
 * Description	: Bandit leader periodically attacks the player during good gauntlet
 */
void
recurring_injury()
{
    if (quest_mode > 2) //Gauntlet has been finished
    {
        return;
    }
    set_alarm(6.0, 0.0, "recurring_injury");
    object target = find_player(burdened);
    object target_room = environment(target);
    if (wildmatch( "*jade*", file_name(target_room) ))
    {
        return;
    }

    int target_hp = target->query_hp();
    if (target_hp < 100) //No need for extra difficulty.
    {
        return;
    }

    switch (random(7))
    {
    case 0:
        tell_room(target_room, QCTNAME(target) + " staggers into a tree.\n",
            target);
        target->catch_msg("You stagger into a tree. "
            + "Branches stabber into you.\n");
        break;
    case 1:
        tell_room(target_room, QCTNAME(target) + " trips over a stone.\n",
            target);
        target->catch_msg("Off-balance, you find a loose stone that rocks your "
            + "world. Your world gains a few bruises.\n");
        break;
    case 2:
        tell_room(target_room, QCTNAME(target) + " accidentally knocks heads "
            + "with " + QTNAME(TO)+ ".\n", target);
        target->catch_msg(query_The_name(target) + " stands up straighter for "
            + "a moment, then his head flops down. "
            + "You stop it with your face.\n");
        break;
    case 3:
        tell_room(target_room, "One of " + QTNAME(target) + "'s wounds suddenly"
            + "tears open.\n", target);
        target->catch_msg("Your new exercise regimen is helping you lose weight "
            + "- red, liquid weight.\n");
        break;
    case 4:
        tell_room(target_room, QCTNAME(target) + " bleeds heavily.\n", target);
        target->catch_msg("Pain is weakness leaving the body, in liquid "
            + "form.\n");
        break;
    case 5:
        tell_room(target_room, QCTNAME(target) + " is favouring "
            + target->query_possessive() + " right leg.\n", target);
        target->catch_msg("You pull " + query_the_name(target)
            + " forward and succeed in pulling something else as well.\n");
        break;
    default:
        tell_room(target_room, QCTNAME(target) + " trips over " +
            QTNAME(TO) + " and slowly pulls the two of them to their feet.\n",
                target);
        target->catch_msg("You trip over " + query_the_name(target)
            + " (painfully) fall to the ground. You hurriedly rise and "
            + "(narrowly) avoid falling to your pursuers.\n");
    }

    if (target_hp < 500)
    {
        target->heal_hp(-min(25, target_hp/15));
    }
    else if (target_hp < 5000)
    {
        target->heal_hp(-min(400, target_hp/10));
    }
    else
    {
        target->heal_hp(-min(1000, target_hp/8));
    }
}


/*
 * Function name: start_gauntlet
 * Description  : Changes NPC state and immobilizes
 */
void
start_gauntlet()
{
    quest_mode = 2;
    object player = find_player(quest_owner);
    object this_room = environment();
    object origan = summon_origan(this_room);

    tell_room(this_room, QCTNAME(origan) + " quietly walks up and bashes "
     + QTNAME(TO) + " on the side of the head with "
     + "the flat of his unusual sword.\n", TO);

    tell_room(environment(), QCTNAME(TO) + " staggers and leans on "
        + QTNAME(player) + " for support.\n", player);
    player->catch_msg(query_The_name(TP) + " staggers and leans on you "
        + "for support. It takes all your concentration to walk while keeping "
        + "the two of you upright.\n");

    foreach (object tool: player->query_tool(W_BOTH))
    {
        empty_slot(tool); //Free hands to hold runaway
    }
    remove_prop(OBJ_M_NO_GET);
    TO->move(player); //burden.c will handle holding.
    set_this_player(player); //Following "hold" function relies on this_player
    command_hold();
    start_burden(quest_owner, 0.0, 120.0); //2 minutes to deliver

    origan->command("say Since you are so intent on taking him back, "
        + "I'll send you an honour guard!\n");
    set_alarm(0.5, 0.0, &remove_origan(origan));
    set_alarm(1.0, 0.0, &mob_me( ({WILD_DIR + "bandit/npc/bandit.c",
        WILD_DIR + "bandit/npc/bandit2.c"}), query_living_name(player), 5, 3 ));
}
