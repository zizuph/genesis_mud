/*
 * He really does wander around
 * Can be cloned by ~Shire/common/evendim/ev8
 */
 inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/make_money.h"

void
create_monster()
{
    set_name("orc");
   set_adj(({"scouting","small"}));
    set_alignment(-150 - random(50));
   set_race_name("orc");
   set_long("This orc is out scouting for enemies of him and his kin.\n"
    + "He doesn't seem to be good at what he's doing though.\n");
    add_prop(CONT_I_WEIGHT,87000);   /* 87  Kg */
   add_prop(CONT_I_HEIGHT,153);     /* 153 cm */
    set_stats(({ 17, 25, 16, 18, 12, 20}));
   set_skill(SS_UNARM_COMBAT,25);
   set_skill(SS_WEP_SWORD,30);
   set_skill(SS_WEP_AXE,30);
   set_skill(SS_WEP_KNIFE,30);
   set_skill(SS_DEFENCE,40);
   set_skill(SS_PARRY,30);
   set_skill(SS_SNEAK,30);
    set_pick_up(75);
    set_aggressive(0);
   set_attack_chance(0);
   set_random_move(5);
    /* Actions */
   set_act_time(5);
   add_act("burp");
   add_act("fart");
    /* Combat actions */
   set_cact_time(5);
   add_cact("shout Help! I'm under attack!");
    add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */
    set_alarm(1.0,0.0,"arm");
   MAKE_MONEY;
}
 void
arm()
{
  clone_object(EVENDIM_DIR + "wep/orc_scimitar")->move(TO);
  command("wield scimitar");
}
  /* For the solamnic Knights */
 query_knight_prestige() { return(25); }

