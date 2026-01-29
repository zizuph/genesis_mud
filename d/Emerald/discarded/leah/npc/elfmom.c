inherit "/d/Emerald/std/emerald_monster";

#include "/d/Emerald/defs.h"

#define HELPING_CINDELLE "_emerald_quest_find_bracelet"

object asked; /* The person we have asked to help us. */
int given;
void give_info(string *passed);
void return_nod(string *passed);

void
create_emerald_monster()
{
    set_name("cindelle");
    set_living_name("cindelle");
    set_race_name("elf");
    set_gender(G_FEMALE);
    add_adj("crying");
    add_adj("distraught");
    set_long("This poor elf woman looks like she is distraught about "+
	"something. She seems to be looking around for someone to help "+
	"her.\n");

    set_stats( ({ 50, 60, 40, 10, 20, 40 }) );

    set_alignment(250);

    add_ask( ({ "help", "task", "for help", "for task", "child",
		  "about child", "distraught" }), VBFC_ME("quest_give"), 0);
    set_default_answer("The elf just continues sobbing about her child.\n");
}

void
give_info(string *passed)
{
  object obj;
  
  if (obj = present(passed[0], environment()))
      if (!asked)
      {
          command("ask " + obj->query_real_name() +
                  " My child has fallen sick. Will you help me?");
          command("whisper " + obj->query_real_name() +
                  " Just nod at me if you wish to help.");
          asked = obj;
      }
      else
      {
          command("whisper " + obj->query_real_name() + " I'm sorry, but " +
                "some "+ asked->query_race_name() +" has already agreed "+
		"to help me.");
      }
  else
  {
    command("say Where did " + passed[1] + " go??");
    command("sigh");
  }
}

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
		" Please look for my child's ward. It is a "+
		"bracelet that protects against sickness and "+
		"poisons.");
	command("whisper to " + obj->query_real_name() +
		" I left it sitting on a window ledge while I "+
		"bathed him. When I returned, It was gone!");
	command("thank " + obj->query_real_name());
	command("smile happily");
	given = 1;
	obj->add_prop(HELPING_CINDELLE, 1);    
	return;
    }
    if (asked == obj && given) {
	command("whisper to " + obj->query_real_name() +
		" But I already told you! Find my child's bracelet!\n");
	return;
    }
}

public void
add_introduced(string str)
{
    object betterNotBeNpc;
    if(betterNotBeNpc = present(str, environment(TO)))
        if(!betterNotBeNpc->query_npc())
           {
                set_alarm(1.0, 0.0, &command("introduce myself to "+str));
           }
}

string
quest_give()
{
    give_info(({ TP->query_real_name(), TP->query_pronoun() }));
    return "";
}
