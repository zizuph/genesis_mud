/*
 * Living room daughter
 * Boreaulam, September 2012
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"
void arm_me();
void reject_letter(object ob, object player);
void reject_flower(object ob, object player);
void accept_gem(object ob, object player);
void drop_the_object(object ob);
void remove_the_object(object ob);

/*
 * Function name:        create_monster
 * Description  :        constructor for the object
 */
void
create_monster()
{

    string adj = "adolescent";
    set_adj(adj);
    add_adj("female");
    set_name("marina");
    set_living_name("marina");
    add_name("girl");
    set_race_name("goblin");

    set_long("The goblin girl is an elder daughter of a goblin family " +
             "living here. She seems to be distracted.\n");
    set_short(adj + " goblin girl");

    set_base_stat(SS_STR, 40 + random(10));
    set_base_stat(SS_DEX, 30 + random(10));
    set_base_stat(SS_CON, 40 + random(10));
    set_base_stat(SS_INT, 20 + random(10));
    set_base_stat(SS_WIS, 30 + random(10));
    set_base_stat(SS_DIS, 20 + random(10));

    add_prop(OBJ_M_NO_ATTACK, "Suddenly you understand that you will break " +
                              "someone's heart by killing this girl.");
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 0);
    set_gender(G_FEMALE);
        
    add_chat("Dima is a nice boy.");
    add_chat("Does he really love me?");

    set_chat_time(60);
    set_act_time(60);

    add_act("emote makes her hair.");

    add_ask( ({ "dima", "Dima"}),
        "say Oh, Dima is a nice boy who lives nearby. My mother thinks it is " +
            "just puppy love, but I do like him. He would really have to " +
            "prove himself in order to convince my mother to let him " +
            "court me.", 1);
    add_ask( ({ "love", "proof", "prove"}),
        "say True love requires a proof.", 1);
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
    clone_object(EQUIP_DIR + "l2_girltoy")->move(TO);

    command("wield all");
    command("wear all");
} /* arm_me */

/*
 * Function name:        enter_inv
 * Description  :        check gifts
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    object player = this_player();
    
    if(ob->id(LEVEL2_QUEST_LETTER))
    {
        if(interactive(from))
        {
            command("thank " + TP->query_name());
            set_alarm(1.0, 0.0, &reject_letter(ob, player));
        }
    }
    else if(ob->id(LEVEL2_QUEST_FLOWER))
    {
        if(interactive(from))
        {
            if(this_player()->query_prop(GCL2_QUEST_PROP) == 3)
            {
                command("thank " + TP->query_name());
                set_alarm(1.0, 0.0, &reject_flower(ob, player));
            }
            else
            {
                command("thank " + TP->query_name());
                command("say I love black lotus flowers.");
                set_alarm(1.0, 0.0, &remove_the_object(ob));
            }
        }
    }
    else if(ob->id("black_diamond"))
    {
        if(interactive(from))
        {
            if(this_player()->query_prop(GCL2_QUEST_PROP) == 5)
            {
                set_alarm(1.0, 0.0, &accept_gem(ob, player));
            }
            else
            {
                command("thank " + TP->query_name());
                command("say I love precious gems.");
                set_alarm(1.0, 0.0, &remove_the_object(ob));
            }
        }
    }
    else
    {
        if(interactive(from))
        {
            set_alarm(2.0, 0.0, &drop_the_object(ob));
        }
    }
} /* enter_inv */

/*
 * Function name:        reject_letter
 * Description  :        return quest letter
 */
void
reject_letter(object ob, object player)
{
    command("emote reads the letter.");
    command("say Oh! This is a beautiful letter! But, it is just words. My " +
                "mother will never be convinced his love is true just from " +
                "a love letter. Please return this letter to Dima and let " +
                "him know that I need better proof of his love!");
    
    player->add_prop(GCL2_QUEST_PROP, 2);
    command("drop " + OB_NAME(ob));
} /* reject_letter */

/*
 * Function name:        reject_flower
 * Description  :        return quest letter
 */
void
reject_flower(object ob, object player)
{
    command("emote smells the flower and smiles.");
    command("say Oh! A black lotus! This is my favourite flower, and it is " + 
                 "so rare too! I'm sure Dima must have strong feelings for " + 
                 "me to remember this, but I'm afraid it won't convince my " + 
                 "mother. Please return this flower to him and ask him to " + 
                 "show proof that even my mother can't ignore.");
    
    player->add_prop(GCL2_QUEST_PROP, 4);
    command("give " + OB_NAME(ob) + " to " + player->query_name());
} /* reject_flower */

/*
 * Function name:        give_object
 * Description  :        giving object to player
 */
void 
give_object(object ob, object player)
{
    if(!ob->move(player))
    {
        player->catch_tell("The girl gives you a " + 
            ob->query_short() + ".\n");
    }
    else
    {
        ob->move(this_object());
        player->catch_tell("The girl puts a " + 
            ob->query_short() + " on the floor.\n");
        command("say You cannot hold it. I will place it here.");
    }
} /* give_object */

/*
 * Function name:        accept_gem
 * Description  :        accept black diamond
 */
void
accept_gem(object ob, object player)
{
    command("thank " + TP->query_name());
    command("say A black diamond? Oh my goodness! No goblin in our clan " +
        "has ever given so precious a courting gift! Even my mother could " +
        "not object to Dima now!");
    command("emote quickly writes a letter.");
    command("say Please give this letter to Dima.");
    player->add_prop(GCL2_QUEST_PROP, 6);
    object letter = clone_object(OBJS_DIR + "l2_letter");
    letter->set_letter_name("Dima");
    give_object(letter, this_player());
} /* accept_gem */

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
