/*
 * The Baker of Imladris
 * Based on Barliman of Bree
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
   set_name("iorius");
   add_name(({"iorius","baker"}));
   set_living_name("");
   set_title("Iorius, Master baker of Imladris");
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
   
   set_act_time(2);
   add_act("emote wipes the sweat from his brow.");
   add_act("say What can I get for you today?");
   add_act("emote opens the oven and pulls out some tasty bread.");
   add_act("emote opens the oven and pulls out some sweet cakes.");
   add_act("emote kneads a batch of bread.");
   add_act("smile happ");
   add_act("emote punches the bread dough.");
   add_act("say Feel free to order anything on the menu.");
   add_act("emote shapes a loaf of bread from the bread dough.");
   add_act("emote opens the oven and puts some loaves in to bake.");
   add_act("say Elves love to eat and drink, so I'm very busy.");
   add_act("say Have you decided what you want to order?");
   add_act("emote sighs happily.");
   add_act("emote looks up from his work.");
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
   command("say Hi there " + ob->query_nonmet_name() + ". What can I serve " +
      "you?");
}
 
my_long() 
{
    if (notmet_me(this_player())) this_player()->add_introduced("barliman");
    return ("This is Iorius the baker.  He works hard to feed " +
        "the many elves and peredhil in Imladris. He is " +
        "respected for his ability to turn anything into a " +
        "culinary masterpiece. It has been said that no elf can " +
        "rival the talent of Iorius.\n"); 
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
    command("emote smiles.");
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
