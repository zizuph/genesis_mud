/*
* The shopkeeper of the Joke Shop (April Fool's Day) in Bree.
* Cloned by ~Shire/common/bree/rooms/town/hshop.c
*/
inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

//   Protoypes
int return_sigh(string who);
int return_smile(string who);
void return_introduce();
void greet(object ob);

void
create_monster() {
   if (!IS_CLONE) return;
   set_name("jaunty");
   add_name(({"keper","shopkeeper"}));
   set_living_name("jaunty");
   set_title("Jaunty, Shopkeeper of the Bree Joke Shop");
   set_race_name("hobbit"); 
   set_adj(({"comical","happy"}));
   set_long("@@my_long");
   default_config_npc(30);
   set_base_stat(SS_CON, 39);
   
   set_skill(SS_UNARM_COMBAT,20);
   set_skill(SS_DEFENCE,30);
   set_pick_up(75);
   
   set_aggressive(0);
   set_attack_chance(0);
   
   add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
   add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   add_prop(LIVE_I_ALWAYSKNOWN, 1);
   set_gender(G_MALE);
   
   /*
   set_act_time(3);
   add_act("emote cheerfully cleans the counter.");
   add_act("smile happ");
   add_act("emote sweeps the floor.");
   add_act("emote goes about her work dusting.");
   add_act("say Everybody loves my gifts.");
   add_act("say I sell some rather extraordinary things.");
   add_act("say I just love the holidays.");
   add_act("say You won't find anything else quite like what I sell.");
   add_act("say Do you want to by a special gift for someone?");
   add_act("say Be sure to visit my friend Fuschia in Frogmorton. " +
        "She wraps gifts for everyone!");
    */
}

init_living() {
   ::init_living();
   if (interactive(this_player()))
      {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}

void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say Hi there " + ob->query_nonmet_name() + ". What can I help " +
      "you with?");
}

my_long() {
   if (notmet_me(this_player())) this_player()->add_introduced("jaunty");
   return("This is Jaunty, owner of the Bree " +
        "Joke Shop. He's a sly joker who enjoys " +
        "helping others pick the perfect prank.\n");
}

int
return_smile(string who) {
   object ob;
   
   ob = present(who, environment());
   if (!ob) return 0;
   switch (random(4)) {
      case 0: command("smile"); return 1;
      case 1: command("smile " + who); return 1;
      case 2: if (notmet_me(ob)) {
         command("introduce myself to " + who);
         return 1; 
          }
      break;
   }
   return 0;
}

int
return_sigh(string who)
{
   if (!who) return 0;
   who = lower_case(who);
   if (random(3)) return 0;
   command("say Can I help you purchase a prank? A gag maybe?");
   return 1;
}

int
add_introduced(string who)
{
   object ob;
   
   if (!who) return 0;
   who = lower_case(who);
   ob = present(who, environment());
   if (!ob) return 0;
   if (!CAN_SEE(this_object(), ob)) return 0;
   if (!notmet_me(ob)) return 0;
   if (!random(20)) return 0;
   set_alarm(itof(random(9)),0.0,&return_introduce());
   return 1;
}

void
return_introduce()
{
   command("introduce myself");
}

void
emote_hook(string emote,object actor,string averb = 0)
{
   string name = actor->query_real_name();
   
   switch(emote)
   {
      case "sigh":
      set_alarm(3.0,0.0,&return_sigh(name));
      break;
      case "smile":
      set_alarm(3.0,0.0,&return_smile(name));
      break;
   }
}
