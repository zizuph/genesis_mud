inherit "/std/monster";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include <money.h>
#include <language.h>
static int counter=0;
void
create_monster() {
   set_name("dukroll");
   set_race_name("wyrmman");
   set_adj("well-built");
   set_adj("crafty");
   set_long("This muscular wyrmman appears quite frightening. " +
      "His eyes seem almost to glow with a green light and his skin is " +
      "much darker than the other of his kind you've seen.  It is nearly " +
      "black!\n");
   set_title("the Weapon Master of the Wyrm Lord");
   set_gender(0);
   set_alignment(-250);
   set_aggressive(0);
   set_stats(({ 75, 75, 75, 45, 60, 65 }));
   set_hp(550);
   set_skill(SS_2H_COMBAT, 50);
   set_skill(SS_DEFENCE, 60);
   set_skill(SS_PARRY, 50);
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_WEP_SWORD, 30);
   set_skill(SS_WEP_CLUB, 40);
   set_skill(SS_WEP_KNIFE, 40);
   set_skill(SS_WEP_AXE, 50);
   add_prop(CONT_I_WEIGHT, 101500);
   add_prop(CONT_I_HEIGHT, 2200);
   add_prop(CONT_I_VOLUME, 92000);
   set_act_time(5);
   add_act("say Yuin fool far arrivin!");
   add_act("emote pokes you in your gut with his warhammer.");
   add_act("emote throws his head back and laughs " +
      "uproariously at you!");
   add_act("emote slams his warhammer against the wall " +
      "with a thunderous Ka-PLOW and chips fly everywhere.");
   add_act("emote shows you his long, sharp teeth.");
   set_cchat_time(5);
   add_cchat("say I'n slay yunow.");
   add_cchat("emote screams:  Master!  Power to me!");
   add_cchat(({"emote grins deviously","emote rams his " +
            "knee into your gut!"}));
   add_cchat("emote swings his weapon around his head " +
      "bringing it down dangerously close to your own head!");
   add_cchat("emote massacres your body with his horned boots!");
   add_cchat("say You never dost defeat Dukroll!");
   trig_new("%s 'introduces' %s","intro_me");
   set_alarm(1.0,0.0,"get_stuff");
}
int
intro_me() {
   set_alarm(0.0,0.0,"intro_me2");
   return 1;
}
int
intro_me2() {
   command("introduce myself");
   return 1;
}
get_stuff() {
   int i;
   object ob1;
   object ob2;
   seteuid(getuid());
   ob1 = MONEY_MAKE(25, "silver")->move(TO);
   ob2 = MONEY_MAKE(3, "gold")->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wboots.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wwarhammer2.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wknife.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wknife.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wshield1.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wshield2.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wsword2.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/waxe.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/warmour1.c")
   ->move(TO);
   command("wield warhammer");
   command("wear second shield");
   command("wear all");
   return 1;
}
attacked_by()
{
   set_aggressive(1);
   command("grin");
   command("kill " + lower_case(TP->query_real_name()));
   counter++;
   set_alarm(0.0,0.0,"next_part");
}
int
next_part() {
   if (counter > 1)
      {
      return 1;
   }
   set_alarm(25.0,0.0,"change_weapons");
   return 1;
}
int
change_weapons() {
   command("unwield all");
   command("wield sword");
   command("remove shield");
   command("wear shield");
   set_alarm(20.0,0.0,"change_weapons2");
   return 1;
}
int
change_weapons2() {
   command("unwield all");
   command("wield knife");
   command("remove shields");
   command("wield second knife");
   set_alarm(15.0,0.0,"change_weapons3");
   return 1;
}
int
change_weapons3() {
   command("unwield all");
   command("wield axe");
   command("wear shield");
   if(TO->query_attack()) {
      set_alarm(20.0,0.0,"orig_weapons");
      return 1;
   }
   return 1;
}
int
orig_weapons() {
   command("unwield all");
   command("remove shields");
   command("wield warhammer");
   command("wear second shield");
   set_alarm(15.0,0.0,"change_weapons");
   return 1;
}
