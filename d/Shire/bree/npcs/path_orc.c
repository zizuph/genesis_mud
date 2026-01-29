/*
 * common orc in bree orc camp
 */

inherit "/d/Shire/orcmaker/team";

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/make_money.h"

// Prototypes
void arm();

create_monster()
{
   seteuid(getuid());
   if (!IS_CLONE)
      return;

   set_name("orc");
   set_adj(({"sneaking","angry"}));
    set_alignment(-200 + random(50));
   set_race_name("orc"); 
   set_long("This orc is out scouting for enemies of him and his kin.\n"
	    + "He doesn't seem to be good at what he's doing though.\n");

   add_prop(CONT_I_WEIGHT,87000);   /* 87  Kg */
   add_prop(CONT_I_HEIGHT,153);     /* 153 cm */

   set_stats(({ 34, 25, 32, 18, 12, 55}));
   set_skill(SS_UNARM_COMBAT,10);
   set_skill(SS_WEP_SWORD,60);
   set_skill(SS_WEP_AXE,30);
   set_skill(SS_WEP_KNIFE,30);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_PARRY,30);
   set_skill(SS_SNEAK,30);

   set_pick_up(75);

   set_aggressive(1);
   set_attack_chance(0);

   set_hp(500); /* Heal fully */
   MAKE_MONEY;

   /* Actions */
   set_act_time(5);
   add_act("burp");
   add_act("fart");
   add_act("sneak north");
   add_act("sneak south");

   /* Combat actions */
   set_cact_time(5);
   add_cact("shout Help! I'm under attack!");

   add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */

   set_alarm(0.1,0.0,&arm());

}

arm() {
   clone_object(WEP_DIR + "/orc_scimitar")->move(this_object());
  command("wield scimitar");
}


/* For the solamnic Knights */

query_knight_prestige() { return(25); }
