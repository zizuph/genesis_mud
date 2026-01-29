/*
 * Dima - boy in love 
 * Boreaulam, Oct 2013
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";
inherit "/d/Sparkle/lib/quest_reward";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

/* prototypes */
void arm_me();
void give_object(object ob, object player);
void remove_the_object(object ob);
void drop_the_object(object ob);

/*
 * Function name:        create_monster
 * Description  :        constructor for the object
 */
void
create_monster()
{

    string adj = "adolescent";
    set_adj(adj);
    add_adj("male");
    set_name("dima");
    set_living_name("dima");
    add_name("boy");
    set_race_name("goblin");

    set_long("The goblin boy is an elder son of a goblin family living " +
             "here. He seems to be worried.\n");
    set_short(adj + " goblin boy");

    set_base_stat(SS_STR, 45 + random(10));
    set_base_stat(SS_DEX, 35 + random(10));
    set_base_stat(SS_CON, 45 + random(10));
    set_base_stat(SS_INT, 25 + random(10));
    set_base_stat(SS_WIS, 35 + random(10));
    set_base_stat(SS_DIS, 25 + random(10));

    add_prop(OBJ_M_NO_ATTACK, "Suddenly you understand that you would " +
                              "prefer to help this boy.");
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 0);

    add_chat("I wish she will love me as much as I do.");
    add_chat("She is the only one.");

    set_chat_time(60);
    set_act_time(60);

    add_act("emote sobs sadly.");
    add_act("emote think about his love.");

    add_ask( ({ "task", "help", "quest", "love"}),
        "say I met a girl and I am trying to win her love. " +
        "She lives not far from here. But I am afraid of her mother " +
        "who thinks she knows better who suits her daughter. " +
        "Probably her mother convinced that I am not worthy. " +
        "So this beautiful girl doesn't believe that my love is true. " +
        "I need to prove it to her.", 1);
    add_ask( ({ "girl", "girlfriend", "marina"}),
        "say She is just perfect. I love her so much. Her name is Marina. " +
        "She lives not far from here. She is THE ONE!", 1);
    add_ask( ({ "flower", "black flower", "lotus", "black lotus", "flowers"}),
        "@@ask_flower@@", 1);
    add_ask( ({ "gem", "black gem", "diamond", "black diamond", "gems"}),
        "@@ask_gem@@", 1);
    add_ask( ({ "prove", "proof", "proofs"}),
        "@@ask_prove@@", 1);

} /* create_monster */

/*
 * Function name:        arm_me
 * Description  :        equip goblin
 */
void
arm_me()
{
    clone_object(EQUIP_DIR + "l2_boystick")->move(TO);

    command("wield all");
} /* arm_me */

/*
 * Function name:        ask_prove
 * Description  :        result for ask "prove"
 */
string
ask_prove()
{

    if(this_player()->test_bit("Sparkle",
    GOBLIN_LOVE_GROUP,
    GOBLIN_LOVE_BIT)) {
        return "say You've helped me already. Thanks.";
    } else {
        command("sob");
        int prop = this_player()->query_prop(GCL2_QUEST_PROP);
        if(prop == 0) {
            this_player()->add_prop(GCL2_QUEST_PROP, 1);
            command("say I wrote a letter to my girlfriend. " +
                    "I believe that after reading these warm words she " +
                    "will definitely fall in love with me. " +
                    "Please deliver it to her. Not to mother or sister. " +
                    "Just to her.");
            command("say Here it is.");
            object letter = clone_object(OBJS_DIR + "l2_letter");
            letter->set_letter_name("Marina");
            give_object(letter, this_player());
            return "smile";
        } else if(prop < 4) {
            return "say I already gave you a letter.";
        } else if(prop < 5) {
            return "say Go find a black lotus.";
        } else {
            return "say Go find a black diamond.";
        }
    }
} /* ask_prove */

/*
 * Function name:        ask_flower
 * Description  :        answer for flowers
 */
string
ask_flower()
{
    if(this_player()->test_bit("Sparkle",
    GOBLIN_LOVE_GROUP,
    GOBLIN_LOVE_BIT)) {
        return "say You've helped me already. Thanks.";
    } else {
        int prop = this_player()->query_prop(GCL2_QUEST_PROP);
        if(prop < 3) { 
            return "say Why do you ask?";
        } else if(prop == 3) {
            return "say Black lotus is a rare flower and loves water. Probably " +
            "you will find some near the lake.";
        } else if(prop == 3) {
            return "say Did you give her the flowers yet?";
        } else {
            return "say Thanks for bringing her flowers although it didn't work.";
        }
    }
} /* ask_flower */

/*
 * Function name:        ask_gem
 * Description  :        answer for gem
 */
string
ask_gem()
{
    if(this_player()->test_bit("Sparkle",
    GOBLIN_LOVE_GROUP,
    GOBLIN_LOVE_BIT)) {
        return "say You've helped me already. Thanks.";
    } else {
        int prop = this_player()->query_prop(GCL2_QUEST_PROP);
        if(prop < 4) { 
            return "say Why do you ask?";
        } else if(prop == 4) {
            return "say Marina likes everything black. There are a few " + 
            "gems of black color but the most impressive is black diamond. " + 
            "Although I think you will not find any in these caves. You " + 
            "will have to seek for them outside.";
        } else {
            return "say Gems are great.";
        }
    }
} /* ask_gem */

/*
 * Function name:        give_object
 * Description  :        giving object to player
 */
void 
give_object(object ob, object player)
{
    if(!ob->move(player))
    {
        player->catch_tell("The boy gives you a " + 
            OB_NAME(ob) + ".\n");
    }
    else
    {
        ob->move(this_object());
        player->catch_tell("The boy puts a " + 
            OB_NAME(ob) + " on the floor.\n");
        command("say You cannot hold it. I will place it here.");
    }
} /* give_object */

/*
 * Function name:        reject_letter
 * Description  :        reject letter that was not given to Marina
 */
void reject_letter(object letter, object player)
{
    command("say I asked you to give this letter to Marina.");
    command("say Why did you bring it to me?");
    give_object(letter, player);
} /* reject_letter */

/*
 * Function name:        accept_letter
 * Description  :        accept letter that was returned from Marina
 */
void accept_letter(object letter, object player)
{
    command("say My love letter is not good for her. Words are empty to her.");
    command("sob");
    command("say Maybe flowers? I know Marina loves black lotus.");
    player->add_prop(GCL2_QUEST_PROP, 3);
    remove_the_object(letter);
} /* accept_letter */

/*
 * Function name:        reject_flower
 * Description  :        reject flower that was not given to Marina
 */
void reject_flower(object flower, object player)
{
    command("say Yes. These black flowers will be nice gift to Marina.");
    give_object(flower, player);
} /* reject_flower */

/*
 * Function name:        accept_flower
 * Description  :        accept flower that was returned from Marina
 */
void accept_flower(object letter, object player)
{
    command("say What did she say.");
    player->catch_tell("You tell Dima what Marina said.\n");
    tell_watcher(player->query_Name() + " tells something to Dima.\n");
    command("say Harder? So there is a hope.");
    command("say What else could be a great gift?");
    command("think");
    command("shout GEMS!!!");
    command("say Bring her black diamond. It will be a worthy " +
            "gift.");
    player->add_prop(GCL2_QUEST_PROP, 5);
    remove_the_object(letter);
} /* accept_flower */

/*
 * Function name:        reward_quest
 * Description  :        reward for quest
 */
void reward_quest(object letter, object player)
{
    command("emote reads the letter and his eyes spark brightly.");
    command("shout Hooray! She loves me!!!");
    command("dance");
    command("say Thank you!");
    give_reward(player,
            GOBLIN_LOVE_GROUP,
            GOBLIN_LOVE_BIT,
            GOBLIN_LOVE_EXP,
            "goblin_love");
    remove_the_object(letter);
} /* reward_quest */

/*
 * Function name:        enter_inv
 * Description  :        interacting on quest items
 */
public void
enter_inv(object ob, object from)
{
    object player = this_player();
    if(ob->id(LEVEL2_QUEST_LETTER))
    {
        if(interactive(from))
        {
            ::enter_inv(ob,from);
            if(this_player()->query_prop(GCL2_QUEST_PROP) == 1)
            {
                ::enter_inv(ob,from);
                set_alarm(1.0, 0.0, &reject_letter(ob, player));
            } 
            else if(this_player()->query_prop(GCL2_QUEST_PROP) == 2)
            { 
                ::enter_inv(ob,from);
                set_alarm(1.0, 0.0, &accept_letter(ob, player));
            }
            else if(ob->get_letter_name() == "Dima")
            {
                ::enter_inv(ob, from);
                
                set_alarm(1.0, 0.0, &reward_quest(ob, player));
            }
        }
    }
    else if(ob->id(LEVEL2_QUEST_FLOWER))
    {
        if(interactive(from))
        {
            ::enter_inv(ob, from);
            if(this_player()->query_prop(GCL2_QUEST_PROP) != 4)
            {
                set_alarm(1.0, 0.0, &reject_flower(ob, player));
            }
            else
            {
                set_alarm(1.0, 0.0, &accept_flower(ob, player));
            }
        }
    }
    else
    {
        if(interactive(from))
        {
            ::enter_inv(ob, from);
            set_alarm(2.0, 0.0, &drop_the_object(ob));
        }
    }
} /* enter_inv */

/*
 * Function name:        drop_the_object
 * Description  :        drop not quest letter
 */
void
drop_the_object(object ob)
{
    command("say I don't need this.");
    command("drop " + OB_NAME(ob));
} /* drop_the_object */

/*
 * Function name:        remove_the_object
 * Description  :        destruct quest letter
 */
void
remove_the_object(object ob)
{
    ob->remove_object();
} /* remove_the_object */
