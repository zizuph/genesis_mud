/*
* The keeper of the Prancing Pony Inn in Bree.
* Cloned by ~Shire/common/bree/inn
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
   set_name("barliman");
   add_name(({"butterbur","innkeeper"}));
   set_living_name("butterbur");
   set_title("Butterbur the Innkeeper of the Prancing Pony");
   set_race_name("human"); 
   set_adj(({"short","fat"}));
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
   
   set_act_time(3);
   add_act("emote cleans the counter meticulously.");
   add_act("chuckle");
   add_act("emote bustles about the inn, a tray of mugs in hand.");
   add_act("emote smiles so broadly his nose turns red.");
   add_act("emote wonders aloud if he'll need four kegs or five for that dwarven party.");
   add_act("emote sighs wistfully, remembering when more hobbits came from the Shire.");
   add_act("smile slee");
   add_act("shout Pipe down in there, I'm working!");
   add_act("shout If you run out of beer, I have more.");
   add_act("shout Is there a Mister Baggins in there by any chance?");
   add_act("say Even though I may not look it, I'm busy, busy, busy.");
   add_act("say I have not seen Gandalf the Grey in a long time.");
   add_act("say I hear rumors of orcs very near Bree.");
   add_act("shout Nob! Where are you? Those hobbits need more beer. Nob!");
   add_act("shout Bob, how many times have I told you about to keep the ponies in the stables, not the inn yard?");
   add_act("say Must I do everything myself?");
   add_act("say What is it I am forgetting?");
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
   command("say Hi there " + ob->query_nonmet_name() + ". What can I serve " +
      "you?");
}

my_long() {
   if (notmet_me(this_player())) this_player()->add_introduced("barliman");
   return break_string("Meet Barliman Butterbur the innkeeper. Barliman "+
      "Butterbur will serve you anything on the "+
      "menu. Barliman Butterbur is human and you wonder "+
      "what he is doing here in the land of the Hobbits. "+
      "He is currently holding a tiny mirror in his right "+
      "hand.\n", 70);
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
   command("say Are you gonna order something or what?");
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
