/*
* The shopkeeper of the Tack Shop in Bree.
* Cloned by ~Shire/bree/rooms/town/stable/tack_shop
* By Palmer, snarfed from merigrin.c from Finwe
* Date: December 2002
*/
inherit "/d/Shire/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <const.h>
#include "/d/Shire/sys/defs.h"

//   Protoypes
int return_sigh(string who);
int return_smile(string who);
void return_introduce();
// void greet(object ob);

void
create_shire_monster() {
   if (!IS_CLONE) return;
   set_name("kalrin");
   add_name(({"clerk","shopkeeper"}));
   set_living_name("kalrin");
   set_title("Kalrin, Shopkeeper of the Bree Tack Shop");
   set_race_name("human");
   set_adj(({"lithe","solemn"}));
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

   set_act_time(3);
   add_act("emote solemnly cleans the counter.");
   add_act("smile curtly");
   add_act("emote sweeps the floor.");
   add_act("say My gear is made from the finest leather.");
   add_act("say You won't find anything else quite like what I sell.");
}

/*
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
*/

my_long() {
   if (notmet_me(this_player())) this_player()->add_introduced("barliman");
   return("This is Kalrin of Rohan, shopkeeper for the Bree " +
        "Tack Shop. He's a skilled rider and can help you " +
        "choose the right equipment for your steed.\n");
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
   command("say Can I help you purchase some equipment?");
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

void
return_to_shop()
{
    set_m_in("arrives climbing over the corral fence");
    TO->command("west");
    set_m_in("arrives");
    TO->command("west");
    TO->command("south");
}

void
attacked_by(object attacker)
{
    TO->command("blink");


    TO->command("north");
    TO->command("east");
    set_m_out("leaves climbing over the corral fence");
    TO->command("east");
    set_m_out("leaves");
    attacker->stop_fight(TO);
    TO->stop_fight(attacker);
    set_alarm(60.0, 0.0, return_to_shop);
}