/*
 *  The leader of the invading orcs
 *  Cloned by ~Shire/common/evendim/hut
 *
 *  Added a prop to show that the player who killed the orc
 *  is the one with the letter.  This is checked in
 *  /d/Shire/common/hobbiton/quest_hobbit.c
 *  Duragus, Sept 22, 1998
 */
 inherit "/std/monster";
#include "/d/Shire/sys/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/make_money.h"
 void
create_monster()
{
     set_name("leader");
    add_name("_letter_orc_");
   set_race_name("uruk-hai");
   set_adj("large");
    set_alignment(-150 - random(50));
   set_long("This is probably the leader of the orcs "+
   "in this camp. He looks like a rather competent uruk-hai.\n");
    add_prop(CONT_I_WEIGHT,102000);  /* 102 Kg */
   add_prop(CONT_I_HEIGHT,183);     /* 183 cm */
             /* STR DEX CON INT WIS DIS */
   set_stats(({ 25, 22, 37, 21, 25, 70}));
   set_skill(SS_UNARM_COMBAT,34);
   set_skill(SS_WEP_SWORD,48);
   set_skill(SS_WEP_AXE,78);
   set_skill(SS_WEP_KNIFE,43);
   set_skill(SS_DEFENCE,38);
   set_skill(SS_PARRY,47);
   set_pick_up(75);
    set_aggressive(1);
   set_attack_chance(90);
    /* Actions */
   set_act_time(5);
   add_act("frown");
   add_act("growl");
    /* Combat chat-strings */
   set_cchat_time(5);
   add_cchat("I knew I was the only one with brains here!");
   add_cchat("Bloody guards!");
   add_cchat("Die, intruder!");
    add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */
    set_alarm(1.0,0.0,"arm");
   MAKE_MONEY;
}
 void
arm()
{
  FIXEUID;
  clone_object(EVENDIM_DIR + "wep/orc_sword")->move(this_object());
  command("wield sword");
  clone_object(EVENDIM_DIR + "obj/orc_letter")->move(this_object()); /* quest */
}
  /* For the solamnic Knights */
 query_knight_prestige() { return(100); }

public void
do_die( object killer )
{
   killer->add_prop(KILLED_LETTER_ORC,1);
   ::do_die(killer);
}
