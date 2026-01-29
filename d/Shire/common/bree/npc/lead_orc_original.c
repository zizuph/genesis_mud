inherit "/d/Shire/orcmaker/team";

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/make_money.h"

//   Prototypes
void arm();

create_monster()
{
   seteuid(getuid());
   if (!IS_CLONE)
      return;

   set_name("orc");
   add_name("leader");
   set_adj(({"tall","calculating"}));
    set_alignment(-200 - random(50));
   set_race_name("orc"); 
   set_long("This orc is taller than most and seems to know what he is "+
   "doing. Strangely, enough you notice some kind of noble quality "+
   "about him. Clearly he cannot be purely orcish!\n");

   add_prop(CONT_I_WEIGHT,87000);   /* 87  Kg */
   add_prop(CONT_I_HEIGHT,153);     /* 153 cm */

   set_stats(({ 78, 60, 70, 30, 30, 80}));
   set_skill(SS_UNARM_COMBAT,10);
   set_skill(SS_WEP_SWORD,60);
   set_skill(SS_WEP_AXE,70);
   set_skill(SS_WEP_KNIFE,30);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_PARRY,60);

   set_pick_up(75);

   set_aggressive(1);
   set_attack_chance(1);

   MAKE_MONEY;

   /* Actions */
   set_act_time(3);
   add_act("burp");
   add_act("fart");
   add_act("snicker");
   add_act("emote sneers confidently.");

   /* Combat actions */
   set_cact_time(3);
   add_cact("shout Help! I'm under attack!");
   add_cact("knee all");
   add_cact("shout You will pay for this with your life!");
   add_cact("say I'm going to enjoy watching you suffer.");
   add_cact("panic");

   add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */

   set_alarm(0.1,0.0,&arm());

}

arm() {
   clone_object(WEP_DIR + "borc_axe")->move(this_object());
   clone_object(BREE_DIR + "obj/bree_locket.c")->move(this_object());
  command("wield all");
}


/* For the solamnic Knights */

query_knight_prestige() { return(25); }
