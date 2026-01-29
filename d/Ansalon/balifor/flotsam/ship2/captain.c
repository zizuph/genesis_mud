inherit "/d/Genesis/ship/captain";
#include "/d/Ansalon/balifor/flotsam/ship2/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include "/d/Ansalon/common/defs.h"
#include <filter_funs.h>

#define ENV(xxx) environment(xxx)

int intro = 0;

/*
* Prototypes
*/
void grimoire_found(mixed ob);

void
create_monster()
{
   set_name("maquesta");
   add_name("captain");
   set_race_name("half-elf");
   add_adj("swarthy");
   set_adj("dark-skinned");
   set_gender(G_FEMALE);
   set_long("This female appears to be one of the dark-skinned " +
      "mariners from Northern Ergoth, but something about her makes you think she is " +
      "more than what she seems.\n");
   set_stats(({ 80, 80, 100, 60, 60, 90 }));
   set_skill(SS_SWIM, 100);
   set_skill(SS_LOC_SENSE,100);
   set_skill(SS_UNARM_COMBAT,80);
   set_skill(SS_DEFENCE,50);
   heal_hp(10000);
   
   set_chat_time(8);
   add_chat("Hmm... I wonder what happened to my " +
      "helmsman? He seems to have disappeared.");
   add_chat("If you ever travel down to Port Balifor, " +
      "send my regards to Pig-faced William.");
   add_chat("Rumour has it that the Blue Lady is having " +
      "peace talks with the lords of Palanthas. In my opinion " +
      "those fops would be fools to trust her.");
   
   set_cchat_time(11);
   add_cchat("Stop it, you pestering dog!");
   add_cchat("Right, you'll pay for that!");
   add_cchat("Come on! I'll beat the living daylights out of you!");
   add_cchat("Right! I'm really gonna stump you this time!");
   add_cchat("Give it to me, big-nose!");
   add_cchat("I'm gonna smack you so hard....");
   
   trig_new("%w 'introduces' %s", "react_introduce");
   
   add_prop(OBJ_M_NO_ATTACK,
      "You feel this woman is under strong protection.\n");
   add_prop(OBJ_M_NO_MAGIC_ATTACK, "Somehow no harm can be done to "+
      "the captain by means of magic. How strange.\n");
    add_prop(OBJ_I_RES_MAGIC, 200);
   
   set_ticket(TICKET);
   set_price(PRICE);
   
   add_notify_meet_interactive("no_grimoire");
}    

string
query_my_title()
{
   return "Pirate Lord of the Bloodsea";
}

int
buy(string str)
{
   if (this_player()->query_average_stat() < 20)
      {
      notify_fail("You don't need to buy any ticket. " +
            "Young travel for free.\n");
      return 0;
   }
   
   return ::buy(str);
}

void
react_introduce(string person,string who)
{
   if (!intro)
      intro = set_alarm(4.0,0.0,"introduce_me");
}

void
introduce_me()
{
   tell_room(E(TO),QCTNAME(TO) + " introduces herself as:\n" +
      "Captain Maquesta Kar-thon, female half-elf.\n");
   FILTER_LIVE(all_inventory(E(TO)))->add_introduced("maquesta");
   intro = 0;
}


void
no_grimoire()
{
   object *players;
   object *obs;
   int i;
   int j;
   int gAlarm_time;
   
   gAlarm_time = 4;
   players = FILTER_LIVE(all_inventory(ENV(TO)));
   
   for (i = 1; i < sizeof(players); i++)
   {
      obs = deep_inventory(players[i]);
      
      for (j = 1; j < sizeof(obs); j++)
      {
         if (obs[j]->id("refnasgrim"))
            {
            obs[j]->remove_object();
            set_alarm(gAlarm_time, 0.0, &grimoire_found(players[i]));
            gAlarm_time +=2;
           }
        }
   }
   
   return;
}


void
grimoire_found(mixed ob)
{
   command("shout I don't want such dangerous things on my ship!");
   command("shout Give me that.");
   ob->catch_msg(" takes your grimoire.\n");
   tell_room(ENV(TO), "The captain takes something from " + QTNAME(ob) +
      ".\n", ob);
   
   return;
}
