/* trainer.c: Gladiator trainer: Shiva, ?.
 *    Training function moved to room: Serpine, 3/28/96.
 */

inherit "/d/Cirath/std/monster";
#include "defs.h"

void 
create_monster()
{
    set_name(({ "barkara", "trainer"}));
    set_title("the Trainer of the Gladiators");
    set_race_name("human");
    set_adj("tall");
    add_adj("lean");
    set_long("Once a famous Gladiator of Athas, this human was the first "+
      "to earn the powers of an Overseer, but chose instead to "+
      "become a free man. Unfortunately his skills and attitudes "+
      "were of little use in the outside world, so he returned "+
      "to earn a living teaching the combat arts to the next "+
      "generation of warriors.\nHe has a scar across his face.\n"+
      "Both his ears are pierced.\n"+
      "He has the brutal look of a gladiator.\n");
    set_stats(({ 200, 150, 200, 100, 100, 120 }));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_2H_COMBAT, 100);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_act("' You have much to learn.");
    add_act("' Never underestimate an opponent.");
    add_act("' There is always someone better.");
    add_act("' Each victory only delays the inevitable.");
    add_act("emote teaches some young gladiators to fight.");
}

void
arm_me()
{
    clone_object(TYR+"wep/implr_st.c")->move(TO);
    clone_object(TYR+"wep/implr_st.c")->move(TO);
    clone_object(TYR+"arm/body_scl.c")->move(TO);
    clone_object(TYR+"arm/rarm_chn.c")->move(TO);
    clone_object(TYR+"arm/robe_sim.c")->move(TO);
    command("wield all");
    command("wear all");
}

void
do_die(object killer)
{
   WRITE_LOG(LOG_BARKARA, killer, "just killed Barkara!");
   ::do_die(killer);
}
