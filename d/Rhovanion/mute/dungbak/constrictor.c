inherit "/std/monster";
inherit "/std/combat/unarmed";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#define A_BITE  0
#define A_CONS  1
#define H_HEAD 0
#define H_BODY 1
#include <ss_types.h>
void
create_monster() {
   int i;
   object ob1;
   set_name("snake");
   set_living_name("_mute_constrictor");
   add_name("constrictor");
   set_adj("constrictor");
   set_adj("slimey-green");
   set_adj("giant");
   set_race_name("snake");
   set_long("This is a giant constrictor snake perhaps over " +
      "twenty feet long with a blackish green " +
      "back and lighter, slimey green belly.  The snake's eyes are solid " +
      "white and so are its fangs. These creatures have been " +
      "known to swallow all manner of beings and items storing " +
      "them in its gut for who knows how long.\n");
   set_gender(G_NEUTER);
   default_config_mobile(45);
   set_alignment(-50);
   set_aggressive(1);
   set_hp(450);
   set_skill(SS_HIDE, 50);
   add_prop(CONT_I_WEIGHT, 70000);
   add_prop(CONT_I_VOLUME, 60000);
   set_attack_unarmed(A_BITE, 50, 15, W_IMPALE, 33, "gripping bite");
   set_attack_unarmed(A_CONS, 40, 30, W_BLUDGEON, 67,
      "constricting grip");
   set_hitloc_unarmed(H_HEAD, (({ 20, 40, 45, 35 })), 20, "head");
   set_hitloc_unarmed(H_BODY, (({ 15, 35, 40, 30 })), 80, "body");
   set_act_time(10);
   add_act("emote hisses.");
   ob1 = clone_object("/d/Rhovanion/mute/dungeon1/chloramite1.c")
   ->move(this_object());
   command("hide");
   set_alarm(0.0,0.0,"snake_hide");
}
hide_part()
{
   command("hide");
}
snake_hide() {
   command("hide");
}
