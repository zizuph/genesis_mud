/* Vision's Ghost, Sarr */
/* 2017-08-19 Malus: Moving defaults to base/std file */
#include "defs.h"
#define A_BITE 0
#define A_LPAW 1
#define A_RPAW 2
inherit STD_UNDEAD;

object weapon, armour;

void
create_monster()
{
    ::create_monster();
    string adj = one_of_list(({
      "horrible", "ghastly", "dire", "awful",
    }));
    set_name(({"_raumdor_vghost", "warrior"}));
    add_name("ghost");
    set_race_name("warrior");
    set_adj(adj);
    add_adj("ghost");
    set_short(adj + " ghost warrior");
    set_long(
      "This is one of the four awful ghosts of the feared vision. The poor " +
      "soul looks tortured and mutilated. It is certainly not a pretty sight " +
      "to look at.\n");
    set_gender(G_MALE);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_DEFENCE, 90);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 45);
    set_act_time(3);
    add_act("emote wails.");
    add_act("moan softly");
    add_act("emote radiates a coldness that sinks into your bones.");
    set_cact_time(3);
    add_cact("emote hisses.");
    add_cact("emote wails loudly.");
    add_cact("emote wails: Thou shalt... die!");

    weapon = clone_object(COMMON_WEP_DIR + "vghost_sword");
    armour = clone_object(COMMON_ARM_DIR + "vghost_plate");
    equip(({weapon, armour}));
}

void
notify_you_killed_me(object who)
{
    command(
      "emote hovers over the fresh corpse and its chest glows red for a " +
      "moment.");
    TO->heal_hp(2000);
    command("emote looks reinvigorated!");
}

void
do_die(object killer)
{
    command("emote crumbles to dust, then blows away in the wind.");
    weapon->do_destroy();
    armour->do_destroy();
    ::do_die(killer);
}
