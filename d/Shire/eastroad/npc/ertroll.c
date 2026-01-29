inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Shire/common/make_money.h"

object club;

void arm_me();

create_monster() {
   set_name("grunge");
   add_name("troll");
   set_short("ugly troll");
   set_race_name("troll");
   set_long("This troll is really ugly. Standing almost "+
      "9 feet tall, he looks powerful and tough. He seems to have "+
      "come down from the mountains to search for the treasure, "+
      "long rumored to have been buried here.\n");
   add_prop(CONT_I_WEIGHT, 677*1000);
   add_prop(CONT_I_HEIGHT, 300);
   set_stats( ({ 110, 35, 85, 10, 10, 50 }) );
   set_hp(query_max_hp());
   
   set_skill(SS_UNARM_COMBAT, 35);
   set_skill(SS_WEP_SWORD,    60);
   set_skill(SS_WEP_AXE,      30);
   set_skill(SS_WEP_CLUB,     69);
   set_skill(SS_DEFENCE,      65);
   set_skill(SS_PARRY,        10);
   set_pick_up(20);
   set_attack_chance(30);
   set_title("the grim, first killer of the Trollshaws");
   set_alignment(-280-random(200));
   MAKE_MONEY;
   make_gold(10);
   
   set_act_time(2);
   add_act("Hides something behind his back when he sees you.");
   add_act("say Me found it. Mine all mine.");
   add_act("grin");
   add_act("fart");
   add_act("emote headbutts some big boulders, they crumble into dust!!");
   add_act(({"scream", "laugh"}));
   add_act("emote swings his club around your head.");
   
   set_cact_time(2);
   add_cact("say Is that the best you can do, then i'll leave!!");
   add_cact("shout HAHAHA! You loose PECK!");
   add_cact("say I am gonna rip your heart out and fart down your throat!!!");
   add_cact("shout Dinner coming in a FEW blows!!!");
   add_cact("shout I am so scared i might run soon, HAHAHAHAHA!");
   add_cact("laugh");
   add_cact("emote starts to smell the blood from you!!");
   set_alarm(1.0, 0.0, &arm_me());
}

arm_me()
{
   if(!club || !present(club, this_object()))
      {
      club = clone_object(STAND_WEAPON+"woodclub");
      club ->move(this_object());
      command("wield club");
   }
   command("shout Me found it. It's mine. ALL MINE!!!!");
   command("shout Me will kill you if you try to take it.");
   command("shout HAHAHAHA! I smash your brains out looser!!");
   command("duh");
   command("scream");
   
   /*reset_monster()*/
   
}
