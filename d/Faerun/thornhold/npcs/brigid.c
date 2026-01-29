/*
* Brigid Stoneshaft of Thornhold, by Twire June, 2016
*/
inherit "std/monster";

#include <const.h>   // for G_MALE
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

//   Protoypes
int return_smile(string who);
void return_introduce();

void
create_monster() {
   if (!IS_CLONE) return;
   set_name("brigid");
   add_name(({"stoneshaft", "girl", "brigid", "daughter", "child"}));
   set_living_name("brigid");
   set_title("Stoneshaft");
   set_race_name("dwarf"); 
   set_size_descs("short", "plump");
   set_gender(G_FEMALE);
   set_adj(({"young","freckle-faced"}));
   set_long("@@my_long");
   default_config_npc(30);
   set_base_stat(SS_CON, 80);
   set_base_stat(SS_STR, 80);
   set_base_stat(SS_DEX, 80);
   set_base_stat(SS_INT, 80);
   set_base_stat(SS_WIS, 80);
   
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_pick_up(75);
   
   set_aggressive(0);
   set_attack_chance(0);
   
   add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
   add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   
   set_act_time(25);
   set_chat_time(75);
   add_act("smile shyly");
   add_act("emote peers down at her game board seriously.");
   add_act("emote fidgets with a game piece.");
   add_act("emote tugs thoughtfully on one of her braids.");
   add_chat("Betcha I can beat ya at a game of noughts and crosses!");
   add_chat("Mam never plays with me.");
   add_chat("I won a fancy lens once playin' noughts and crosses!");

   add_ask( ({ "test", "t"}), "say " + "@@ask_gamer|hey@@", 1);

   add_ask( ({ "lens", "loupe", "won" }), VBFC_ME("explain_lens"));
   add_ask( ({ "noughts", "crosses", "game" }), VBFC_ME("explain_game"));
   add_ask( ({ "stop"}), VBFC_ME("stop_playing"));
}

void
stop_playing()
{
    command("stand");
}


public string
ask_gamer(string question)
{
    return "Hey";
}

void
explain_lens()
{
    command("say It's a special lens used to look at things up close!");
    command("say I won it from the deep-gnome that visits Thornhold sometimes.");
}

void
explain_game()
{
    object qp = this_player();
    
    command("say Noughts and crosses is a simple game, but I'm " +
            "really good at it!");
               
    if( command("sit at table") )
    {
        command("say Lets play. Betcha can't win!");
    }
    else
    {
        command("say Ask me again when the table is free and we'll play.");
    }

    /*
    seq_new("do_explain");
    seq_addfirst("do_explain",({
      "say First you play.", 
      "grin",
      1,
      "say Then you lose."
      }));
 */
}


my_long() {
   if (notmet_me(this_player())) this_player()->add_introduced("brigid");
   return "Brigid Stoneshaft is the daughter of Kala, proprietress " +
      "of the Thonrhold Alehouse. She is a young she-dwarf with plump " +
      "freckled cheeks and flame-red hair styled into two braided loops, " +
      "one on each side of her head. She is staring seriously at a game " +
      "board, contemplating her next move.\n";
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

