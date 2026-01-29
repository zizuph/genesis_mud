/*
 *  A sleeping orc guard
 *  Cloned by ~Shire/common/hobbiton/camp1
 */

inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"


//   Prototypes
void arm();


void
create_monster()
{
   seteuid(getuid());
   if (!IS_CLONE)
      return;

   set_name("orc");
   set_adj(({"sleeping","small"}));
    set_alignment(-150 + random(50));
   set_race_name("orc"); 
   set_long("This orc is supposed to be guarding the camp. At the moment\n"
          + "he is not paying attention.\n");

   add_prop(CONT_I_WEIGHT,87000);   /* 87  Kg */
   add_prop(CONT_I_HEIGHT,153);     /* 153 cm */

   set_stats(({ 30, 20, 20, 23, 25, 27}));
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_WEP_SWORD,30);
   set_skill(SS_WEP_AXE,30);
   set_skill(SS_WEP_KNIFE,30);
   set_skill(SS_DEFENCE,40);
   set_skill(SS_PARRY,30);
   set_pick_up(75);

   set_aggressive(0);
   set_attack_chance(0);
   set_hp(query_max_hp()); /* Heal fully */

   /* Actions */
   set_act_time(5);
   add_act("snore");

   /* Combat chat-strings */
   set_cchat_time(5);
   add_cchat("You filthy swine!");
   add_cchat("I hope your hair will fall out!");
   add_cchat("Die, attacker!");

   /* Combat actions */
   set_cact_time(5);
   add_cact("shout Help! Intruders!");

   add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */

   set_alarm(0.1,0.0,&arm());

}

arm() {
  clone_object(HOBBIT_DIR + "wep/orc_scimitar")->move(TO);
  command("wield scimitar");
}


/* For the solamnic Knights */

query_knight_prestige() { return(25); }

attacked_by(object ob)
{
    ::attacked_by(ob);
    remove_adj("sleeping");
    remove_adj("sleepy");
    add_adj("sleepy");
    set_long(break_string("This orc looks extremely tired, and startled" +
    " at seeing you here.  He's supposed to be looking out for intruders;" +
    " seems he wasn't doing his job.\n", 70));
    set_aggressive(1);
    set_attack_chance(90);
}
