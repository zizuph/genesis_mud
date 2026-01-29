#pragma strict_types
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* The taskmaster within the Citadel in the Central District of
Kabal */
/* by Antharanos */

void
create_monster()
{
    ::create_monster();
    set_name("hernan");
    add_name("sage");
    add_name("master");
    add_name("taskmaster");
    set_race_name("human");
    set_adj("short");
    add_adj("busy-looking");
    set_long("A man whose brow is extremely wrinkled. Judging by the "+
        "agitated expression that's characteristic of his face, you would "+
        "venture that he is under a great deal of stress. "+
        "It probably comes from all the tasks the High Lord "+
        "puts on his shoulders. Maybe you could help him?\n");
    set_stats(({75,50,60,100,90,60}));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(OBJ_M_NO_ATTACK,"You decide not to attack the Sage.\n");
    set_alignment(500);
    set_act_time(3);
    add_act("scratch");
    add_act("ponder");
    add_act("think");
    add_act("emote furrows his brow in concentration.");
    add_act("say A visit to the museum of my good friend, "+
       "is worth the effort. Quite an interesting place.");
    set_cact_time(3);
    add_cact("say You stinking bugger!");
    add_cact("say Damn you to the Nine Hells!!");
    add_cact("say You filthy, backstabbing foreigner!!! Die!!!");
    add_cact("scream");
    add_speak("I am the High Lords official 'problem-solver', " +
        "so I have hundreds of tasks to deal with. Maybe you could " +
        "do some of them for me, with a proper reward for you " +
        "if succesfully completed, of course.\n");
    set_default_answer("The taskmaster says: Pardon me?\n");
    add_ask(({"quests","quest"}),"The taskmaster says: Hmm...do " +
       " you mean tasks?\n");
    add_ask(({"help"}),"The taskmaster says: Maybe you can do some tasks "+
      "for me?\n");
    add_ask(({"tasks","task"}),"The taskmaster says: I have " +
       "several things in mind...more specifically, I've got " +
       "some tasks in need of completion. " +
      "You can ask me task1, task2, etc for details about each task.\n");
    add_ask(({"task1"}),"The taskmaster says: I need someone to " +
       "help clean the bronze bell within the bell tower that " +
       "keeps time here in the city. Apparently, the current " +
       "keeper of the bell tower is being lax in his duties. " +
       "Once you've completed this task I want you to give me " +
       "solid proof that you cleaned up the bell.\n");
    add_ask(({"task2"}),"The taskmaster says: I've been wanting " +
       "to buy myself some nice tanned leather pants, but my duties " +
       "here in the Citadel have kept me too busy. Why don't " +
       "you go down there to the Port District and get me " +
       "some pants? I heard they were cheap.\n");
    add_ask(({"task3"}),"The taskmaster says: Part of my " +
       "duties here in the Citadel is the collection of " +
       "taxes. I've noticed that lately, one of our citizens " +
       "in particular has been cheating the city of its taxes! " +
       "This pitiful excuse for a citizen is none other than " +
       "that thieving watchmaker in the Port District. Go " +
       "there and eliminate him for me. Of course, you should " +
       "bring back proof of his death to me.\n");
    add_ask(({"task4"}),"The taskmaster says: On a visit once " +
        "to a home in the Caravan District I chanced upon the " +
        "most sumptuous pie I have ever tasted. Unfortunately, " +
        "I cannot spare the time to journey there myself, as " +
        "my duties here keep me occupied. If you could go there " +
        "to that quaint little home...hmm...I believe its " +
        "somewhere along High Street, and bring me the pie " +
        "I would be very grateful! It would definitely give " +
        "me more energy to accomplish my daily duties here.\n");
    add_ask(({"task5"}),"The taskmaster says: In the last few " +
        "weeks, disturbing reports have been made of vicious " +
        "goblins raiding the good merchants and pilgrims that " +
        "travel upon the Caravan Route. I would send an experienced " +
        "warrior in your stead, but as it so happens, the goblins " +
        "would slay them horribly. As you may have already surmised, " +
        "I wish you to ask the Goblin King about a possible peace " +
        "treaty between us, that the raiding may stop. Do not worry " +
        "for your own health, as long as you don't make any " +
        "threatening gestures, the goblins will not harm you, " +
        "and since you are relatively inexperienced, they would " +
        "not consider you a threat. However, you must make sure " +
        "that you are very aware of your surroundings, as well " +
        "as skilled in climbing ability. There are traps leading " +
        "to their lair, and you may perish if you fail to notice " +
        "them. Now, go forth quickly, that the raiding may stop!\n");
    add_ask(({"task6"}),"Ohh, you have helped me more than enough. " +
        "Maybe later I will need your help again, but not now. " +
        "Still ... a friend of mine, the master cleric of the " +
        "citadel, told me he smelled something dirty in the "+
        "political situation here in Kabal. Visit him.\n");
   set_title("the Taskmaster of the Citadel");
   set_knight_prestige(-5);

   /*
   trig_new("%w 'gives' 'you' 'a'
       'smelly' 'rag.\n' %s","react_quest1");
   trig_new("%w 'gives' 'you' 'a' 'tanned'
       'leather' 'pants.\n' %s","react_quest2");
   trig_new("%w 'gives' 'you' 'a' 'bloody'
       'note.\n' %s","react_quest3");
   trig_new("%w 'gives' 'you' 'a' 'fresh-baked'
       'pie.\n' %s","react_quest4");
   trig_new("%w 'gives' 'you' 'a' 'blood-red'
       'piece' 'of' 'parchment.\n' %s","react_quest5");
   */
}

int
reward1(string who)
{
    object obj;
    int ran;
    if(obj = present(who, environment()))
    {
        if(obj->test_bit("Kalad",1,2))
            {
            command("say You've done this already!");
            this_player()->catch_msg("You get no experience since you have " +
                "already done this quest before.\n");
            return 1;
            }
        command("say Congrats!");
        this_player()->catch_msg("You completed the task!\n");
        this_player()->catch_msg("You feel a little more experienced!\n");
        obj -> add_exp(100);
        obj -> set_bit(1,2);
    }
}

void
reward2(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj->test_bit("Kalad",1,3))
         {
         command("say Hey, you already brought me a pair before!");
         this_player()->catch_msg("You got no experience at all!\n");
      }
      else
         {
         command("say Thanks for getting me some pants, " +
             "its been feeling kinda drafty around here lately.");
         this_player()->catch_msg("You feel a little more experienced!\n");
         obj -> add_exp(200);
         obj -> set_bit(1,3);
      }
   }
}

void
reward3(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj->test_bit("Kalad",1,4))
         {
         command("grin");
         command("say You didn't really expect to get " +
             "rewarded again for this task, now did you?");
         this_player()->catch_msg("You received no experience.\n");
      }
      else
         {
         command("say Ahh, you have done a great service for the High Lord.");
         command("smile");
         this_player()->catch_msg("You feel more experienced!\n");
         obj -> add_exp(500);
         obj -> set_bit(1,4);
      }
   }
}

void
reward4(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj->test_bit("Kalad",1,5))
         {
         command("smirk");
         command("say I won't reward you more than once for this task!");
         this_player()->catch_msg("You received no experience at all.\n");
         command("say Well, we can't very well let his pie go to waste...");
         command("smile");
      }
      else
         {
         command("say Well done!");
         this_player()->catch_msg("You feel more experienced!\n");
         obj -> add_exp(750);
         obj -> set_bit(1,5);
      }
   }
}

void
reward5(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj->test_bit("Kalad",1,6))
         {
         command("laugh " + (obj->query_real_name()));
         command("say I will not reward you again for this task!");
         this_player()->catch_msg("You received no experience.\n");
      }
      else
         {
         command("hmm");
         command("smile");
         command("thank " + (obj->query_real_name()));
         command("say The High Lord will be pleased with the information you "+
            "have gathered.");
         this_player()->catch_msg("You feel more experienced!!\n");
         obj -> add_exp(1000);
         obj -> set_bit(1,6);
      }
   }
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
        return;

    if(obj->id("smelly_quest_rag"))
    {
        set_alarm(1.0, 0.0, &reward1(from));
        obj->remove_object();
        return;
    }

    if(obj->id("tanned_leather_pants"))
    {
        set_alarm(1.0, 0.0, &reward2(from));
        obj->remove_object();
        return;
    }

    if(obj->id("bloody_quest_note"))
    {
        set_alarm(1.0, 0.0, &reward3(from));
        obj->remove_object();
        return;
    }

    if(obj->id("fresh-baked_pie"))
    {
        set_alarm(1.0, 0.0, &reward4(from));
        obj->remove_object();
        return;
    }

    if(obj->id("quest_parchment"))
    {
        set_alarm(1.0, 0.0, &reward5(from));
        obj->remove_object();
        return;
    }

    set_alarm(1.5, 0.0, &command("say I dont want this."));
    set_alarm(2.0, 0.0, &command("drop " +OB_NAME(obj)));
    return;
}