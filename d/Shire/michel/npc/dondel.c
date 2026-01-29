/* Patched by Tapakah for quest reset - June 2011 */
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit SHIRE_MONSTER;

#define QUEST_NAME "lunch"

void
create_shire_monster()
{
  if(!IS_CLONE) return;

    set_living_name("_dondel_");
    set_name("dondel");
    set_title("the Handyman of Michel Delving");
    set_race_name("hobbit");
   set_long("This "+short()+" looks much like most other hobbits do: "+
      "bare, furry feet; large, rounded belly; and wide, friendly face. "+
      "He is holding his big belly in his hands.\n");
    set_adj(({"tired","hungry"}));
    set_stats(({65,50,65,50,65,50}));
    MAKE_MONEY;
    set_alignment(350);
    
    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_DEFENCE,50);
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 200);
    set_gender(G_MALE);

   set_act_time(8);
   add_act("emote mumbles something about food.");
   add_act("say What are you doing in here?");
   add_act("emote stares around him hungrily.");
   add_act("introduce myself");
   set_introduce(1);
}

void
introduce_me(string who)
{
    if (!::introduce_me(who))
    {
       command("say Hey there " + CAP(who) + ".");
    }
}


void 
test_locket_quest(object player)
{
     if(!player->query_prop("_amanda_gave_me_lunch_"))
     {
      command("say I can't accept this strange lunch, I don't know where it's been.");
     command("say Leave me, now.");
       return;
    }
    if (!REWARD_QUEST(player, QUEST_NAME))
    {
      command("say I appreciate the thought, but you already brought me food.");
      return;
    }

     command("say Thanks for the grub, bub.");
     player->remove_prop("_amanda_gave_me_lunch_");
    command("emote opens the bag of food and devours it in one bite.");
    command("say That was excellent, but I must be off now, goodbye!");
    command("wave all");
    command("emote leaves in a hurry.");
    remove_object();
}

void locket_quest()
{
    if(TP->query_prop("_amanda_gave_me_lunch_"))
    {
      command("eyebrow " + TP->query_name());
     command("say Well, are you gonna give me that lunch from my wife or aren't ya?");
      return;
  }
     command("sniff");
}

void
react_enter(object obj, object from)
{
    if (!living(from))
        return;
    if (obj->id("_lunch_")) 
        test_locket_quest(from);
    else
    {
        command("say What am I supposed to do with this?");
        obj->remove_object();
        return;
    }
}

public void
enter_inv(object obj, object from)
{ 
    set_alarm(1.5,0.0, &react_enter(obj,from));
}
