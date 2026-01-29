
/*
    Signor Patati Tomati, owner of the Gelan grocery store.

    Coded by Maniac

    History:  
            31/5/96     triggers removed                   Maniac
            24.2.96     Garden quest intro comments added  Maniac 
            12.1.95            Created                     Maniac
*/



#pragma save_binary

inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include "monster.h"
inherit STD_AIDED;
#include HAUNT_CODE

#define ENV environment

#define FRUITS ({ "broccoli", "celery", "oranges", "apples",\
                  "bananas", "beetroot", "melons" })

#define NUM_FRUITS 7

create_monster() 
{
  if (!IS_CLONE)
    return;
  set_name("patati");
  add_name("owner");
  add_name("shopkeeper");
  set_race_name("human");
  set_adj(({"happy","tired-looking"}));
  set_title("Tomati the Grocer");
  set_long("Signor Patati Tomati is the owner and shopkeeper of the " +
           "Tomati Empire grocery shop. This man is a very accomplished " +
           "gardener indeed, he quite literally has green fingers. " +
           "He looks pretty tired - this could be something to do with " +
           "his working very hard in the running of this shop, " +
           "to make a living for his huge " +
           "family of twelve children and two wives.\n"); 
  default_config_npc(55);
  set_base_stat(SS_CON,75);
  set_hp(5000);
  set_skill(SS_UNARM_COMBAT, random(20) + 55);
  set_skill(SS_DEFENCE, random(10) + 60);
  set_skill(SS_AWARENESS, random(10) + 50);
  set_alignment(50 + random(100));
  set_gender(0);

  set_cchat_time(12); 
  add_cchat("Hey! What's the problem, you don't like my broccoli?");
  add_cchat("Guards help me get rid of this pig-dog!");
  add_cchat("They're gonna put you in the pillory!");
  add_cchat("Go away or I'll smash this melon over your big ugly head!");

  set_act_time(6);
  add_act("emote juggles with some apples.");
  add_act("say Like to buy something healthy to eat?");
  add_act("@@puts");
  add_act("@@puts");
  add_act("@@eats");
  add_act("say We've had a pretty good crop this year."); 
  add_act("emote spots a solitary blackfly on the floor and stamps on " +
          "it savagely."); 

  add_ask(({ "task", "quest", "garden", "gardens", "garden task" }), 
          ("say The crystalline palace gardens get a lot of visitors and " +
           "we usually encourage them to do a little care-taking. " +
           "Usually the fish need feeding " +
           "and there might be another little chore to do."), 1);  

  add_ask(({"palace", "crystalline palace"}), 
           ("say It's the big sparkly thing on the top of Mount Kyrus."), 1);

  add_ask(({"mount kyrus", "Mount Kyrus"}), 
           ("say Mama mia, do you want me to hold your hand and walk you to " +
            "the gardens or what? It's the biggest mountain in Calia!"), 1); 

  add_ask(({"care-taking", "little care-taking", "care taking"}), 
           ("say Usually the fish need feeding " +
            "and there might be another little chore to do."), 1);  

  add_ask(({"fish", "feeding", "feeding fish", "feed fish"}), 
            "say They like bread I hear.", 1);
}


string
puts()
{
  return "emote puts some " + FRUITS[random(NUM_FRUITS)] +
         " into a basket for display.";
}


string
eats()
{  
   return "emote munches some " + FRUITS[random(NUM_FRUITS)] + 
          ".";
}


void
emote_hook(string emote, object actor, string adverb)
{
    if ((emote == "bow") || (emote == "curtsey"))
        set_alarm(1.0, 0.0, &command("bow " + actor->query_real_name()));
}

