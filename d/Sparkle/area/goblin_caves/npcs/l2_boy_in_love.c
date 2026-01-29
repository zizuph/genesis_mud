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

    add_chat("I hope she will love me as much as I love her.");
    add_chat("She is the only one.");

    set_chat_time(60);
    set_act_time(60);

    add_act("emote sobs sadly.");
    add_act("emote thinks about his love.");

    add_ask( ({"task", "help", "quest", "love"}),
        "say I met a girl named Marina and I am trying to win her heart. She " +
        "does not live far from here, but it seems that her mother does not " +
        "feel I am a good match for her daughter and has convinced Marina " +
        "that I am not worthy! I need to show Marina my love for her is " +
        "true. If you still want to help me, I have some ideas about how I " +
        "can prove my love.", 1);
    add_ask( ({"girl", "girlfriend", "marina"}),
        "say She is just perfect and I love her so much! Her name is Marina, " +
        "and she does not live far from here. I just know that she is THE ONE!",
        1);
    add_ask( ({"flower", "black flower", "lotus", "black lotus", "flowers"}),
        "@@ask_flower@@", 1);
    add_ask( ({"gem", "black gem", "diamond", "black diamond", "gems"}),
        "@@ask_gem@@", 1);
    add_ask( ({"prove", "proof", "proofs", "idea", "ideas"}),
        "@@ask_prove@@", 1);
    set_default_answer(QCTNAME(TP)+" says: I'm not sure "+
        "what you are asking.\n");

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
            command("say I wrote a letter to Marina, pouring my heart out " +
                "to her. Her mother does not want to see me around there, " +
                "so do you think you could deliver it for me? But please " +
                "deliver it directly to Marina! Not to her mother or her " +
                "sister, I think they hate me.");
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
            return "say The black lotus is a very rare flower, and it needs " + 
                "lots of water. With some luck, you might be able to find " +
                "one near the lake.";
        } else if(prop == 4) {
            return "say Did you find a black lotus and give it to her?";
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
        if(prop < 5) { 
            return "say Why do you ask?";
        } else if(prop == 5) {
            return "say The black diamond is the rarest of gems! If you " +
                "could help me find one and give it to Marina, I'm sure " +
                "it would convince her mother to let us be together! " + 
                "However, I'm not sure that you could find one down here " + 
                "in our caves. I think you might have to go outside to " + 
                "find one.";
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
            ob->query_short() + ".\n");
    }
    else
    {
        ob->move(this_object());
        player->catch_tell("The boy puts a " + 
            ob->query_short() + " on the floor.\n");
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
    command("say  My love letter is not good enough for her? Can't she see " +
                "that I really love her?");
    command("sob");
    command("say Maybe some flowers? I know Marina loves the black lotus " +
                "flower, and it's very rare! Perhaps if we gave her one " +
                "she would see my love is true!");
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
    command("say What did she say?");
    player->catch_tell("You tell Dima what Marina said.\n");
    command("say She wants me to try harder? Something that even her " +
        "mother could not ignore?");
    command("say So that means there is hope!");
    command("say But what kind of gift could offer that kind of proof?");
    command("think");
    command("say I know! I will give her the most expensive bride " +
        "price in the history of our clan! A black diamond! Even " +
        "her mother could not ignore that!");
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
    command("shout Hooray! Marina loves me! AND her mother has given her " +
        "permission for me to court her!");
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
