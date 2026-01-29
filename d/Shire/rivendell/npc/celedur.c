/*
 * The shopkeeper of Imladris
 * Modified by Finwe
 * February 1998
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
create_monster() 
{
   if (!IS_CLONE) return;
   set_name("celedur");
   add_name(({"celedur","shopkeeper"}));
   set_living_name("");
   set_title("celedur, shopkeeper of Imladris");
   set_race_name("elf"); 
   set_adj(({"tall","golden-haired"}));
   set_long("@@my_long");
   default_config_npc(50);
   set_base_stat(SS_CON, 59);
   
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_pick_up(75);
   
   set_aggressive(0);
   set_attack_chance(0);
   
   add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
   add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   add_prop(LIVE_I_ALWAYSKNOWN, 1);
   
   set_act_time(5);
   add_act("emote sweeps the floor.");
   add_act("say What would you like to buy?");
   add_act("emote peers at you.");
   add_act("smile happ");
   add_act("say Do you have anything good to sell?");
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
   if (!CAN_SEE(this_object(), ob)) return;
   command("say Hi there " + ob->query_nonmet_name() + ". How may " +
      "I help you?");
}
 
my_long() 
{
//    if (notmet_me(this_player())) this_player()->add_introduced("Celedur");
    return ("This is Celedur the shopkeeper. He manages the " +
        "shop and makes sure transactions are dealt in an " +
        "honorable manner. He has seen and heard many tales " +
        "from those who travel abroad.\n");
}
 
int
return_smile(string who) 
{
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
   command("say Are you going to buy or sell something?\n");
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
