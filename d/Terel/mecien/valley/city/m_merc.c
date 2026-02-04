inherit "/std/monster";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>

#define TO this_object()
#define EN environment
#define PATH "/d/Terel/mecien/valley/city/"
#define OBJ "/d/Terel/mecien/valley/guild/obj/"

create_monster(){
   set_name("fuldermil");
   set_race_name("human");
   add_name("master_merchant");
   add_name("merchant");
   set_adj("shrewd");
   add_adj("merry");
   set_stats(({ 100, 99, 100, 87, 88, 90 }));
   set_skill(SS_TRADING, 100);
   set_skill(SS_DEFENCE, 60);
   set_skill(SS_AWARENESS, 80);
   set_all_attack_unarmed(40);
   set_all_hitloc_unarmed(40);
   
   set_alignment(120);
   set_chat_time(9);
   add_chat("Elnoven is full of joy");
   add_chat("I glad you have come here");
   add_chat("We are a town of ancient praise");
   add_chat("Money is glorious, but I often give to the wizards on the hill");
   add_chat("Merry are my days");
   add_chat("Believe me, you must be careful what you say and do in these parts");
   add_chat("I have seen the great masters");
   add_chat("Let the spirits of wood and stream be at peace with us...");
   add_chat("In the cold forest lie many treasures");
   set_act_time(3);
   add_act("emote cleans up the shop.");
   add_act("smile merr");
   add_act("emote dusts off the tapestries.");
   add_act("emote counts some money.");
   add_act("emote looks under the table.\n");
   add_act("emote stands up on a chair and takes something down.\n");
   
   MONEY_MOVE(random(200), "copper", 0, TO);
   MONEY_MOVE(random(20), "silver", 0, TO);
   MONEY_MOVE(random(5), "gold", 0, TO);
   
}

