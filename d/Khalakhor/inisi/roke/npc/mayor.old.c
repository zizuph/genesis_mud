/*
 * mayor.c
 *
 * Used in nyreese/cadu_m.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/******************************************

This is the mayor of Re Albi. He also (strangely
enough :)) happens to be a questmaster!!!

Created by Gresolle in december 1992.

QUESTS:

0 - birdquest          40  xp
1 - snailquest         50  xp
2 - campquest         498  xp
3 - elementquest     6000  xp 
4 - transformquest   10000 xp

*******************************************/

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

#define BIRDXP 40
#define SNAILXP 50
#define CAMPXP 498
#define ELEMENTXP 6000
#define TRANSFORMXP 10000

#define QD(ob, x) (ob->test_bit(DOMAIN, MAYORGROUP, x))
#define QS(ob, x) (ob->set_bit(MAYORGROUP, x))
#define QC(ob, x) (ob->clear_bit(MAYORGROUP, x))

int
query_quest_nr(object ob) /* return current quest number of player */
{
    return (8 * QD(ob, MAYORBIT1) + 
            4 * QD(ob, MAYORBIT2) +
            2 * QD(ob, MAYORBIT3) +
            QD(ob, MAYORBIT4));
}

int
set_quest_number(int num, object ob)
{
    int *base, i;

    if (num < 0)
        return -1;

    base = ({ 1, 2, 4, 8, 16, 32, 64, 128, 256 }); /* Just add if needed */

    for (i = 3; i >= 0; i--)
        if (num >= base[i])
        {
            QS(ob, MAYORBIT4 - i);
            num -= base[i];
        } 
        else
        {
            QC(ob, MAYORBIT4 - i);
        }

    return query_quest_nr(ob);
}

int
quest_done(object ob)
{
    return set_quest_number(query_quest_nr(ob) + 1, ob);
}

void
create_monster()
{
    set_name("mayor");
    set_short("mayor of Cadu");
    set_long("This is the Mayor of Cadu. Perhaps he has a job for you.\n");
    set_adj("Cadu");

    set_alignment(200);
    default_config_npc(85);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
  
    add_prop(CONT_I_WEIGHT, 100000);  /* 100 Kg ever seen a thin politician? */
    add_prop(CONT_I_HEIGHT, 187);     /* 187 cm */
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_cchat_time(3);
    add_cchat("I'll *never* give you any assignments!!!");
    add_cchat("I am defenseless!");

    seteuid(getuid(TO));

    add_ask(({"assignment", "help", "task", "job", "reward"}),
            "say Have you read the sign?", 1);
    set_default_answer("emote looks a bit confused.", 1);

    set_chat_time(5);
    add_chat("So many worries...");
    add_chat("I saw a seagull today!");
    add_chat("Hmmm... You look like a strong person...");
    add_chat("The Turtle Brings Wheat at Dawn.");
    add_chat("The earthquake shook my house last night.");

    trig_new("%w 'fetches' 'something' 'from' 'another' 'dimension.\n' %s",
             "react_clone");
    trig_new("%w 'patched' 'the' 'internals' 'of' %s", "react_Call");
}

int query_knight_prestige(){return -1;}


void
xpea(int i)
{
    quest_done(TP);
  
    write("You feel more experienced!\n");

    if (TP->query_exp() > i)
        TP->add_exp_quest(i);
    else
        TP->add_exp_quest(TP->query_exp());
}

int
reward()
{
    int succ = 0;
    object ob;

    switch (query_quest_nr(TP))
    {
    case 0: 
        if (TP->query_prop(MQ1PROP))
        {
            command("say Thank you! Well done!");
            xpea(BIRDXP);
            QLOG("Bird quest", BIRDXP);
            TP->remove_prop(MQ1PROP);
            succ = 1;
        }
        break;
    case 1:
        if (ob = present("snail", TP))
        {
            ob->remove_object();
            command("say Thank you! They will be very pleased!");
            QLOG("Snail quest", SNAILXP);
            xpea(SNAILXP);
            succ = 1;
        }
        break;
    case 2: 
        if (TP->query_prop(MQ3PROP))
        {
            TP->remove_prop(MQ3PROP);
            QLOG("Camp Quest", CAMPXP);
            command("say Hmmm.... Thank you for the information.");
            xpea(CAMPXP);
            succ = 1;
        }
        break;
    case 3:
        if (ob = present("he-he-quest-thingy", TP))
        {
            if (ob->query_prop("_roke_given_by_spirit") != TP)
            {
                command("laugh");
                command("say You better return that thing to its owner!");
                break;
            }

            ob->remove_object();
            command("say Ahhhh! You have brought me a stick of magic wood!");
            command("say I will reward you handsomely for this!");
            QLOG("Element quest", ELEMENTXP);
            xpea(ELEMENTXP);
            succ = 1;
        }
        break;
    case 4:
        if (ob = present("gemejminexpe", TP))
        {
            if (ob->query_prop("_the_transformer") != TP)
            {
                command("laugh");
                command("say You havn't done that yourself!");
                break;
            }
            ob->remove_object();
            command("say Gee! Thanks! You made it!\n");
            QLOG("Transform quest", TRANSFORMXP);
            xpea(TRANSFORMXP);
            succ = 1;
        }
        break;
    default:
        break;
    }
    if (succ == 0)
    {
        write("You cannot get a reward for something you haven't done!\n");
    }
    return 1;
}

int
assign()
{
    object obob;

    if (!CAN_SEE(this_object(), this_player()))
    {
        write("The mayor can't see you.\n");
        return 1;
    }

    switch (query_quest_nr(TP))
    {
      case 0:
        command("say to " + OB_NAME(TP) + " You must travel to " +
                "the bird of wisdom and grovel in front of it. " +
                "We must please him, or else he will leave us.");
        return 1;
      case 1: 
        command("say to " + OB_NAME(TP) +
        " I have a small problem... I'm having my girlfriends for " +
        "dinner tonight, but they demand a gourmet dinner, and " +
        "unfortunately I have eaten all my snails! Could you go " +
        "to the forest and catch one for me?");
        return 1;
    case 2:
        command("say to " + OB_NAME(TP) +
        " There are rumours that some warriors from the evil island " +
        "Golbar have encamped in the forest. I want you to travel " +
        "up there and spy in their camp.");
        TP->add_prop(MQ2PROP, 1);
        return 1;
    case 3:
        command("say to " + OB_NAME(TP) +
                " I want you to travel to the bird of wisdom and ask " +
                "him what should be done with those warriors... " +
                "Then do as he says.");
        TP->add_prop(MQ4PROP,1);
        return 1; 
    case 4:
        command("say to " + OB_NAME(TP) +
                " You helped me very much when you brought that stick. "+
                "Unfortunately I haven't been able to have it transformed, "+
                "and if you could fix that for me I would become very happy. "+
                "I believe that there is an old monk that still hangs " +
                "around the monastery ruins. " +
                "Give it to him, and he will help you.");
        write("\nThe mayor gives you a wooden stick.\n");
        
        if (present("ha-ha-given-by-mayor", TP))
            return 1;

        obob = clone_object(ROKEDIR + "obj/strange");
        obob->move(TP);
        obob->remove_name("he-he-quest-thingy");
        obob->add_name("ha-ha-given-by-mayor");
        return 1;
    case 5: 
        write("Hmm... There are no more quests here!\n");
        return 1;
    default:
        write("There are no more quests right now, but if you " +
              "return tomorrow there may be a few new ones.\n");
        return 1;
    }
}

int
ask(string s)
{
    NF("I have never heard of anyone asking for " + s + " here before!\n");

    if (s == "reward")
        return reward();
    if (s == "assignment")
        return assign();
  
    return 0;
}

void
init_living()
{
    add_action(ask, "ask");
}

/********************************************************************
 *
 * Player commands
 */


string
hint_chat()
{
    int ran;

    ran = random(4);
    
    switch (ran)
    {
    case 0: return "Nice weather today!";
    case 1: return "You are sure a honest-looking fellow!";
    case 2: return "The Turtle Brings Wheat At Dawn.";
    case 3: return "Buy an ale in the outdoor cafe!";
    }
}

void
thank_chat(object *arr)
{
    object from, what;
    int ran;

    ran = random(4);
    
    from = arr[0];
    what = arr[1];
    switch (ran)
    {
    case 0:
        command("say Ah, thank you. Now let me see...");
        break;
    case 1:
        command("say " +
                capitalize(LANG_ADDART(check_call(what->short()))) +
                ", what a coincidence...");
        break;
      case 2:
          command("say " +
                  capitalize(LANG_ADDART(check_call(what->short()))) +
                  ", how interesting...");
          break;
      case 3:
          command("say I will examine this, " + from->query_race_name() + ".");
    }
}

void
give_back_immediately(mixed return_arr)
{
    command("say I am already busy with one of your objects, " +
            return_arr[1]->query_race_name() + ".");
    command("give " + OB_NAME(return_arr[0]) + " to " +
            return_arr[1]->query_real_name());
}

void
give_back(object what)
{
    command("say I never asked for this thing!");
    command("drop " + OB_NAME(what));
}

void
enter_inv(object what, object from)
{
    int ran;

    ::enter_inv(what, from);

    if (!from) /* Perhaps it was cloned and moved to me... */
        return;

    set_alarm(itof(3 + random(4)), 0.0, &give_back(what));

    set_alarm(1.0, 0.0, &thank_chat( ({ from, what }) ));
}


/********************************************************************
 *
 *  Some trigger feelings to make the alchemist more vivid.
 *  The feelings are split in two parts: the part that is called by
 *  a trigger function, and a part that is called after a random time.
 *  This is done to get a feeling of reality in the game.

OK, so I stoled this part of him... I confess! :)

 */


void
return_sigh(object who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say Why are you depressed, " + obj->query_nonmet_name() +
                    "?");
        if (ran == 1)
            command("comfort " + OB_NAME(obj));
        if (ran == 2)
            command("say Is life tough for you, " + obj->query_nonmet_name() +
                    "?");
    }
}

void
return_smile(object who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say Life is great, isn't it, " + 
                    obj->query_nonmet_name() + "?");
        if (ran == 1)
            command("smile at " + OB_NAME(obj));
        if (ran == 2)
            command("say It is great to see you smiling, " +
                    obj->query_nonmet_name() + ".");
    }
}

void
return_smirk(object who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say I sense irony, " + obj->query_nonmet_name() +
                    "...");
        if (ran == 1)
            command("smirk");
        if (ran == 2)
            command("grin at " + OB_NAME(obj));
    }
}

void
return_grin(mixed who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say What cunning plan have you forged, " +
                    ((obj->query_gender() == G_MALE) ? "master" : "lady") +
                    "?");
        if (ran == 1)
            command("grin");
        if (ran == 2)
            command("say Get that grin off your face, " + obj->query_race_name() +
                    ".");
    }
}

void
return_introduce(mixed who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
        {
            command("say Nice to meet you, " + obj->query_name() + ".");
            command("bow to " + OB_NAME(obj));
        }
        if (ran == 1)
        {
            command("bow to " + OB_NAME(obj));
        }
        if (ran == 2)
        {
            command("say Be welcome, " + obj->query_race_name() + ".");
            command("bow to " + OB_NAME(obj));
        }
    }
}

int
add_introduced(string who)
{
    if (who)
    {
        who = lower_case(who);
        set_alarm(3.0, 0.0, &return_introduce(who));
        return 1;
    }
}

void
return_nod(mixed who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say I'm glad you agree, " +
                    ((obj->query_gender() == G_MALE) ? "master" : "lady") +
                    ".");
        if (ran == 1)
            command("pat " + OB_NAME(obj) + " on head");
        if (ran == 2)
            command("say Indeed, " + obj->query_race_name() + ".");
    }
}

void
return_shake(mixed who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say So you disagree, " + obj->query_race_name() + "?");
        if (ran == 1)
            command("say I agree with you, " +
                    ((obj->query_gender() == G_MALE) ? "master" : "lady") +
                    ".");
        if (ran == 2)
            command("say Why do " + LANG_PWORD(obj->query_race_name()) +
                    " always disagree?");
    }
}

void
return_laugh(mixed who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say Very funny indeed...");
        if (ran == 1)
            command("laugh");
        if (ran == 2)
            command("giggle");
    }
}

void
return_growl(mixed who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say You frighten me with your growling, " + 
                    obj->query_race_name() + "...");
        if (ran == 1)
            command("say Why so hostile, " + obj->query_race_name() + "?");
        if (ran == 2)
            command("frown");
    }
}

void
return_cackle(mixed who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say You sound like a duck, " + obj->query_race_name() + ".");
        if (ran == 1)
            command("say " + capitalize(LANG_PWORD(obj->query_race_name())) +
                    " cackle very often.");
        if (ran == 2)
            command("giggle");
    }
}

void
return_shrug(mixed who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say Is there anything you " + 
                    LANG_PWORD(obj->query_race_name()) +
                    " do know?");
        if (ran == 1)
            command("say Don't look at me... I don't know either!");
        if (ran == 2)
            command("shrug");
    }
}

void
return_bow(mixed who) 
{
  object obj;

  if (obj = present(who, environment())) 
      command("bow " + OB_NAME(obj));
}

void
return_wave(mixed who)
{
    command("wave");
}

void
return_frown(mixed who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say Is something wrong, " + obj->query_race_name());
        if (ran == 1)
            command("say It wasn't my fault!");
        if (ran == 2)
            command("say I had nothing to do with it, I assure you!");
    }
}

void
return_spit(mixed who)
{
    object obj;
    int ran;
    
    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say Damn " + LANG_PWORD(obj->query_race_name()) + "!");
        if (ran == 1)
            command("say Hey! Don't do that! Don't spit in here!");
        if (ran == 2)
            command("say " + capitalize(LANG_PWORD(obj->query_race_name())) +
                    " are such rude people!");
   }
}

void
return_giggle(mixed who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("say Funny, eh " + obj->query_race_name() + "?");
        if (ran == 1)
            command("say Ah, " + LANG_PWORD(obj->query_race_name()) +
                    " are such merry people.");
        if (ran == 2)
            command("giggle");
    }
}

void
return_clone(string who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
            command("gasp");
        if (ran == 1)
        {
            command("say You are mightier than I am!");
            command("grovel " + OB_NAME(obj));
        }
        if (ran == 2)
        {
            command("say Honour to the great "
                    + obj->query_race() + " conjurer!");
            command("grovel " + OB_NAME(obj));
        }
    }
}

int
react_clone(string who, string dummy1)
{
    if (who)
    {
        who = lower_case(who);
        set_alarm(3.0, 0.0, &return_clone(who));
        return 1;
    }
}

void
return_Call(string who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
        ran = random(3);
        if (ran == 0)
        {
            command("grovel " + OB_NAME(obj));
            command("say Please leave me in one piece, mighty "
                    + obj->query_race_name() + " wizard!");
            command("shiver");
        }
        if (ran == 1)
        {
            command("say Hail to the mighty one!");
            command("grovel " + OB_NAME(obj));
        }
        if (ran == 2)
            command("gasp");
    }
}

int
react_Call(string who, string dummy1)
{
    if (who)
    {
        who = lower_case(who);
        set_alarm(3.0, 0.0, &return_Call(who));
        return 1;
    }
}

void
emote_hook(string emote, object actor, string adverb, object *oblist,
           int cmd_attr, int target)
{
    function f;

    switch(emote)
    {
      case "smile" : f=&return_smile(actor); break;
      case "smirk" : f=&return_smirk(actor); break;
      case "sigh"  : f=&return_sigh(actor); break;
      case "nod"   : f=&return_nod(actor); break;
      case "grin"  : f=&return_grin(actor); break;
      case "giggle": f=&return_giggle(actor); break;
      case "frown" : f=&return_frown(actor); break;
      case "bow"   : f=&return_bow(actor); break;
      case "growl" : f=&return_growl(actor); break;
      case "wave"  : f=&return_wave(actor); break;
      case "shrug" : f=&return_shrug(actor); break;
      case "spit"  : f=&return_spit(actor); break;
      case "cackle": f=&return_cackle(actor); break;
      case "laugh" : f=&return_laugh(actor); break;

        /*    case "shake": f=&return_shake(actor); break;  Ambigous emote */
      default: return;
    }
    set_alarm(3.0, 0.0, f);
}

void
emote_hook_onlooker(string emote, object actor, string adverb,
                    object *oblist, int cmd_attr)
{
    function f;

    switch(emote)
    {
      case "spit" : f=&return_spit(actor); break;
      case "laugh": f=&return_laugh(actor); break;
      case "growl": f=&return_growl(actor); break;
      default: return;
    }
    set_alarm(3.0, 0.0, f);
}
