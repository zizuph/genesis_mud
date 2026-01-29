/*
* Theadric Tallborrow, Traveling Tinkerer by Twire June, 2016
*/
inherit "std/monster";
inherit "/d/Faerun/thornhold/std/shop";

#include <const.h>   // for G_MALE
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "../defs.h"

#define  STORE_ROOM          ROOM_DIR + "tink_stock"

//   Protoypes
int return_smile(string who);
void return_introduce();
void greet(object ob);

void
create_monster() {
   if (!IS_CLONE) return;
   set_name("theadric");
   add_name(({"tallburrow", "tinker", "tinkerer", "Theadric", "merchant"}));
   set_living_name("theadric");
   set_title("Tallburrow the Traveling Tinkerer");
   set_race_name("halfling"); 
   set_gender(G_MALE);
   set_adj(({"unkempt","nimble-fingered"}));
   set_long("@@my_long");
   default_config_npc(30);
   set_base_stat(SS_CON, 80);
   set_base_stat(SS_STR, 80);
   set_base_stat(SS_DEX, 120);
   set_base_stat(SS_INT, 80);
   set_base_stat(SS_WIS, 90);
   
   set_skill(SS_UNARM_COMBAT,20);
   set_skill(SS_DEFENCE,80);
   set_pick_up(75);
   
   set_aggressive(0);
   set_attack_chance(0);
   
   add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
   add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */

   remove_prop(LIVE_M_NO_ACCEPT_GIVE);
   
   set_act_time(20);
   set_chat_time(25);
   add_act("peer");
   add_act("emote rummages around in his pockets.");
   add_act("emote starts searching through a bundle of junk.");
   add_act("emote pulls out a trinket from his wares and examines " +
           "it carefully.");
   add_act("emote drinks from a bottle of dandelion wine.");
   add_chat("If you travel to Waterdeep, don't waste your money in the " +
            "Trades Ward. The best deals are found in the Warrens.");
   add_chat("Odds and ends! Ends and odds! All for sale!");
   add_chat("Your trash is my treasure! Let me make you an offer!");
   add_chat("I love searching for baubles from all over Faerun!");
   add_chat("Stoneshaft ale is a bit too bitter for my taste.");
   
   add_ask( ({ "problem", "quest", "job", "task", "item", "missing" }),
   VBFC_ME("explain_problem"));
 
    add_ask( ({ "watch", "pocketwatch", "timepiece"}), 
                VBFC_ME("explain_watch"));
   
    add_ask( ({ "repair", "road", "ambush" }),
                VBFC_ME("explain_road"));

    setup_shop();
    set_store_room(STORE_ROOM);
    set_shop_name("the travelling tinkerer");
    set_money_greed_sell(90);
    set_money_greed_buy(90);
    set_keeper(this_object());
}

init_living() {
   ::init_living();
   ::init_shop();

   if (interactive(this_player()))
   {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}

public void
print_message(string str)
{
    keeper->command("say " + str);
}
int
do_buy(string args)
{
  if (check_keeper()) return ::do_buy(args);
  return 0;
}
int
do_value(string args)
{
  if (check_keeper()) return ::do_value(args);
  return 0;
}
int
do_sell(string args)
{
  if (check_keeper()) return ::do_sell(args);
  return 0;
}
mixed
shop_hook_filter_sell(object x)
{
    if (weapon_filter(x))
    {
        return "The shopkeeper says: You'll have to take that " 
          + x->short() + " to an arms dealer. I only trade in"
          + " general supplies.\n";
    }
    if (armour_filter(x))
    {
        return "The shopkeeper says: You'll have to take that "
          + x->short() + " to an armourer. I only trade in"
          + " general supplies.\n";
    }
    return 0;
}

void
explain_problem()
{
   if (interactive(this_player()))
   {
       if (QUEST_MASTER->check_gear(this_player()))
       {
            command("say Thanks for helping me repair my pocketwatch! I really " +
                    "appreciate it!");
       }
       else
       {
            command("say Oh, I'm not sure you can help me. My pocketwatch is " +
                    "broken!");
       }
   }
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;

    if (obj->id("gear"))
    {
        if(!QUEST_MASTER->check_gear(from))
        {
            command("say What's this? A gear?");
            command("emote flips down a magnifying lens over his eyes, and begins " + 
                    "tinkering with his pocketwatch. He inserts the gear carefully " +
                    "into the clockwork.");
            command("emote winds up the pocketwatch, and then lifts it to his ear."); 
            command("say Eureka! It works! Thank you friend!");
            QUEST_MASTER->award_gear(from);
        }
        else
        {
            command("say Another gear! Thanks!");
        }
        obj->remove_object();
    }
    else
    {
        command("say Hmm Not sure what I'd do with that.");
        obj->move(from);
    }
}

explain_watch()
{
    command("say I was ambushed on the road Thornhold!");
    command("say A highwayman tried to wrestle my pocketwatch away from me!");
    command("say Fortunately I was able to scare him off, but in the " +
            "scuffle I dropped my watch and it flew into pieces!");
    command("emote sighs in exasperation.");
    command("say I attempted to repair it, but I can't seem to figure out " +
            "how to get it working again!");
        
}
explain_road()
{
    command("say I wonder if a piece of my pocketwatch was lost on " +
            "on the road after the ambush. I tried to collect all the " +
            "scattered pieces, but I can't seem to reassemble it.");
    command("emote holds his pocketwatch up to his ear and frowns.");
}

void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say Nice to meet you " + ob->query_nonmet_name() + "!");
}

my_long() {
   if (notmet_me(this_player())) this_player()->add_introduced("theadric");
   return "This is an unkempt, nimble-fingered male halfling. \n" +
          "He is tall and lean for a halfling. \n";
          "He is a tinkerer. \n";
          "He is wearing trousers with many pockets. \n";
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
      case "smile":
      set_alarm(3.0,0.0,&return_smile(name));
      break;
   }
}
