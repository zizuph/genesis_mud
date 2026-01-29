
/*
 *	Small quest giver.
 *
 *						Napture.
 */

inherit "/std/monster";

/*
 * The following include is needed to let say act like normal players.
 */
#include "/d/Genesis/login/login.h"
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>
#define PLAYER_O_GIVEN  "_flowers_given_to"

object asked;   /* Who we asked to take the flowers  */
object flowers; /* Flowers to be given               */
int given;	/* Given the flowers away all ready? */

/* Prototypes */
void arm_me();
void give_info(string *passed);
void return_nod(string *passed);

create_monster()
{
    if (!IS_CLONE) return;

    set_name("quarloss");
    set_adj("old");
    add_adj("crippled");
    set_long("This crippled old man is having troubles walking " +
             "along the old road here.  He looks slightly lost.\n");
    set_race_name("human");

    add_prop(CONT_I_WEIGHT, 54000);
    add_prop(CONT_I_HEIGHT, 152);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(NPC_I_NO_RUN_AWAY, 1);	    /* Too old and weak to panic! */

    default_config_npc(10);
    set_stats(({ 11, 14, 9, 55, 67, 1 }));
    set_hp(query_max_hp());
    set_alignment(800);

    set_aggressive(0);
    set_attack_chance(0);

    set_act_time(3);
    add_act("lean stick");
    add_act("sigh");
    add_act("@@flower_comment");
    add_act("@@flower_comment");

    set_chat_time(7);
    add_chat("Who blocked this pathway?");
    add_chat("How do I get to the graveyard now the road is blocked?");
 
    set_cchat_time(4);
    add_cchat("After all these years, I'll finally be able to join my wife.");

    set_cact_time(3);
    add_cact("@@combat_flower_comment");
    
    /*trig_new("%w 'nods' %s",  "trig_nod");   
     * trigging on emotes won't work anymore, use emote_hook instead
     * (see below)
     */

    set_default_answer(VBFC_ME("unknown_question"));
    add_ask(({"quest", "quests", "about quests", "for quests",
              "for quest"}), VBFC_ME("quest_question"));
    add_ask(({"sir", "sir quarloss", "sir Quarloss", "Sir Quarloss"}),
              VBFC_ME("sir_question"));
    add_ask(({"wife", "late wife", "dead wife"}), VBFC_ME("wife_question"));
    add_ask(({"name", "your name", "what is your name"}),
              VBFC_ME("name_question"));
    add_ask(({"allenia", "lady allenia", "lady Allenia", "Lady Allenia"}),
            VBFC_ME("real_name_q"));
    add_ask(({"help", "helping"}), VBFC_ME("help_question"));
    add_ask(({"lost"}), VBFC_ME("lost_question"));
    add_ask(({"directions"}), VBFC_ME("dir_question"));
    add_ask(({"flower", "flowers", "grave", "graveyard", "about flowers"}),
	      VBFC_ME("flower_info"));
    getuid();
    seteuid(getuid());
    enable_reset();
}

void
reset_monster()
{
    ::reset_monster();
    asked = TO;
    flowers = clone_object(WROAD_DIR + "obj/flowers");
    flowers->move(TO, 1);
    flowers->add_prop(PLAYER_O_GIVEN, TO);
    given = 0;
}

void
arm_me()
{
    object ob;
    
        ob = clone_object(WROAD_DIR + "arm/cloak");
    ob->move(TO, 1);
    ob = clone_object(WROAD_DIR + "obj/stick");
    ob->move(TO, 1);
    command("wear cloak");
    command("lean stick");
    reset_monster();
}

string
wizinfo()
{
    return "\nThis poor old guy is trying to take his flowers to an\n" +
           "old grave in the graveyard.  Shame the road is blocked...\n\n" +
           "To re-start the quest, do 'Call quarloss reset_monster'.\n" +
           "This shouldn't affect any quest in process!\n\n";
}

void
flower_comment()
{
  if (flowers)
    if (ENV(flowers) == TO)
        command("say I must take these flowers to the graveyard.");
    else  {
        command("say I must remember to thank that person.");
        command("say They took my flowers to the graveyard for me.");
        command("smile");
    }
}

void
combat_flower_comment()
{
  if (flowers)
    if (ENV(flowers) == TO)
        command("say How will I get my flowers to my late wife if I'm dead?");
    else  {
        command("say I hope that person made it to the graveyard.");
    }
}

string
unknown_question()
{
  command("frown");
  command("say I'm an old man, with a weak heart!");
  command("lean stick");
  command("say My memory is failing me!");
  command("ask " + TP->query_real_name() +
          " How am I supposed to know about such things?");
  return "";
}

string
quest_question()
{
    tell_room(ENV(TO), "The old man's eyes widen at the prospect " +
        "of fun and adventure.\nBut then he sinks back down onto his " +
        "walking stick.\n");
    command("sigh");
    command("say I am too old for such things!");
    command("say All I desire now is to take these flowers " +
        "to my late wife's grave.");
    return "";
}

string
sir_question()
{
    command("peer " + TP->query_real_name());
    command("say That is my name, but how does that help " +
            "me get to the graveryard?");
    return "";
}

string
wife_question()
{
    command("sigh");
    command("say My poor wife died many years ago.");
    return "";
}

string
name_question()
{
    command("frown");
    command("say How will knowing my name help me get to the graveyard?");
    return "";
}

string
real_name_q()
{
    command("gasp");
    command("say How did you know my wife's name?");
    command("cry");
    command("say That name brings back happy memories.");
    return "";
}


string
help_question()
{
    command("say Do you want me to help you, or are you offering to help me?");
    command("confused");
    command("say I don't think that I would be much help to you.");
    return "";
}


string
lost_question()
{
    command("say Yes, I am lost!");
    command("sigh");
    command("say I don't know any other way to get to the graveyard " +
	    "from here.");
    return "";
}

string
dir_question()
{
    command("frown");
    command("say I'm the one that's lost, maybe you should be " +
            "giving me directions");
    return "";
}

string
flower_info()
{
    give_info(({ TP->query_real_name(), TP->query_pronoun() }));
    return "";
}

void
give_info(string *passed)
{
  object obj;
  
  if (obj = present(passed[0], environment()))
      if (!given)
      {
          command("ask " + obj->query_real_name() +
                  " Will you take these flowers to the graveyard for me?");
          command("whisper " + obj->query_real_name() +
                  " Just nod if you will do this for me.");
          asked = obj;
      }
      else
      {
          command("whisper " + obj->query_real_name() + " I'm sorry, but " +
                  "someone has already taken my flowers for me.");
      }
  else
  {
    command("say Where did " + passed[1] + " go??");
    command("sigh");
  }
}

/* replaced with emote_hook below
int
trig_nod(string who, string how)
{
    if (who) {
	who = lower_case(who);
	return_nod(({ who, how}));
        return 1;
    }
    return 0;
}*/
void
emote_hook(string emote, object actor, string adverb=0)
{
  if (emote != "nod")
    return;
  if (actor)
    return_nod( ({ actor->query_real_name(),adverb }) );
}

void
return_nod(string *passed)
{
    object obj;
          
    if (!(obj = present(passed[0], environment())))  { /* Still there ?? */
        command("say Why was that person nodding like that?");
	return;
    }
    
    if (asked == obj && !given)  {
	    command("whisper to " + obj->query_real_name() +
		    " Please plant these at my late wife's grave.");
	    given = 1;
	    flowers->add_prop(PLAYER_O_GIVEN, obj);
    	    command("give flowers to " + obj->query_real_name());
    	    command("thank " + obj->query_real_name());
	    command("smile happily");
    }
}


void
add_introduced(string who)
{
    
    switch (random(6))
    {
    case 0 : command("say Hello " + CAP(who) + ".");
        break;
    case 1 : command("say Hello " + CAP(who) + ".");
        command("say My name is Quarloss.");
        break;
    case 2 : command("say So many people that come and go.");
        command("lean stick");
        break;
    case 3:
        command("introduce myself to " + who);
        break;
    case 4 : command("say Your name doesn't help me get " +
                     "to the graveyard.");
                     command("sigh");
                     break;
    case 5 : command("say So, " + CAP(who) + " is your name.");
        command("say Well, my name is Quarloss.");
        break;
    }
}
