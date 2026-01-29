/*  
 *  
 *  A leader in the Evendim orc camp
 *  Was cloned by ~Shire/common/hobbiton/tent many years ago
 *  Now cloned by !shire/evendim/orc_camp/tent20.c
 *  Updated by Finwe, May 2001 for new prisoner quest
 */

inherit "/std/monster";

#include "/d/Shire/sys/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_monster()
{
   seteuid(getuid());
   if (!IS_CLONE)
      return;

    set_alignment(-150 + random(50));
    set_name("leader");
    add_name("_leader_orc_");
    set_race_name("orc");
    set_adj("grim");
    set_short("orc leader");
    set_long("You are gazing at the leader of the orc patrol: " +
        "a White Hand orc, as can be seen from the emblems on " +
        "his gear. The orc is bigger than a usual orc, and he " +
        "looks a bit smarter as well. He looks like he has " +
        "seen much combat.\n");

    add_prop(CONT_I_WEIGHT,102000);  /* 102 Kg */
    add_prop(CONT_I_HEIGHT,183);     /* 183 cm */

            /* STR DEX CON INT WIS DIS */
    set_stats(({ 43, 21, 57, 21, 25, 99}));
    set_skill(SS_UNARM_COMBAT,74);
    set_skill(SS_WEP_SWORD,78);
    set_skill(SS_WEP_AXE,78);
    set_skill(SS_WEP_KNIFE,83);
    set_skill(SS_DEFENCE,68);
    set_skill(SS_PARRY,57);
    set_pick_up(75);

    set_aggressive(1);
    set_attack_chance(90);
    set_hp(10000); /* Heal fully */

   /* Actions */
    set_act_time(5);
    add_act("frown");
    add_act("snarl");
    add_act("say Prepare to become our prisoner, insolent one!");
    add_act("say Guards! Guards! Remove this filth from my sight at once!");
    add_act("say Who let you in here?");

   /* Combat chat-strings */
    set_cchat_time(5);
    add_cchat("I knew I was the only one with brains here!");
    add_cchat("Bloody guards!");
    add_cchat("I want the head of the guard on duty!");
    add_cchat("Die, intruder!");

   /* Combat actions */
    set_cact_time(5);
    add_cact("shout Help! Intruders!");

    add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */
    clone_object(EVENDIM_DIR + "wep/orc_scimitar")->move(this_object());
    command("wield scimitar");
}


//    call_out("arm",0);


/*
arm() {
  clone_object(STAND_PARENT + "weapon/orc_scimitar")->move(this_object());
  command("wield scimitar");
}


init_living() {
   if (this_player()->query_npc())
      return;

}
*/

/* For the solamnic Knights */

query_knight_prestige() { return(100); }

