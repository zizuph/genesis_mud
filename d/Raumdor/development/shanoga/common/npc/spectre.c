/* Spectre, Sarr.
 *
 * Updated by Nerull, to drop spectre medallions.
 * Removed extra hp buffer, and special functions, making the
 * npc alot easier to kill. 1/7-10
 */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file,
 * removed LIVE_I_NO_RUN_AWAY prop so it can flee from the path during day
 */
#include "defs.h"
//inherit STD_UNDEAD;
inherit "/d/Raumdor/development/shanoga/common/std/undead.c";
inherit "/std/combat/unarmed";

public void
create_monster(void)
{
    string adj = one_of_list(({
      "dark", "deadly", "terrifying", "black",
    }));
    ::create_monster();
    set_name("spectre");
    set_race_name("spectre");
    set_adj(adj);
    set_short(adj + " spectre");
    set_long(
      "This foul creature looks much like a wraith, only much bigger, and it " +
      "radiates an aura of greater fear and evil. Two blazing red eyes shine " +
      "from within the translucent black figure. Savage looking black claws " +
      "extend out of its hands. Even the brave would feel the urge to run " +
      "far away from this creature.\n");
    set_stats(STAT_ARRAY(200));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    set_random_move(5);
    set_act_time(3);
    add_act("emote radiates a coldness that sinks into your bones.");
    set_cact_time(3);
    add_cact("emote flashes its burning red eyes in fury.");
    add_cact("emote hisses: I shall take you to hell!");
    add_cact("emote hisses: Feel the power of the grave, mortal!");
    set_attack_unarmed(0, 60, 60, W_SLASH, 50, "left ethereal claw");
    set_attack_unarmed(1, 60, 60, W_SLASH, 50, "right ethereal claw");
    set_hitloc_unarmed(0, 75, 15, "head");
    set_hitloc_unarmed(1, 75, 10, "left arm");
    set_hitloc_unarmed(2, 75, 10, "right arm");
    set_hitloc_unarmed(3, 75, 45, "body");
    set_hitloc_unarmed(4, 75, 20, "legs");
    set_mm_in("flies in from somewhere above!");
}

public string
query_combat_file(void)
{
    return "/d/Raumdor/common/std/chumanoid.c";
}

public void
notify_you_killed_me(object who)
{
    command("emote hisses: I hope you like thy grave, mortal!");
}

public void
do_die(object killer)
{
    command("emote hisses: You will visit Death sooner or later, mortal!");

    log_file("spectre_killed",
      capitalize(killer->query_real_name()) + " (" +
        killer->query_average_stat() + "), killed a spectre at " +
        extract(ctime(time())) + ".\n");

    // Spectre medallion dropchance. Currently closed for review - Nerull
    /* if (random(SP_DROPCHANCE) == 1)
     {
           seteuid(getuid(TO));
         clone_object("/d/Raumdor/common/obj/spectre_med.c")->move(TO, 1);

         command("emote drops a small ghostly medallion!");

         log_file("spectre_med","A spectre dropped a medallion at " +
         extract(ctime(time())) + ".\n");
     }*/

    command("emote fades away into oblivion!");

    ::do_die(killer);
}

public int
special_attack(object enemy)
{
    if (random(7))
        return 0;

    object drain = present("spector_drain", enemy);

    if (objectp(drain))
        return 0;

    tell_watcher(QCTNAME(TO) + " reaches out and strikes " + QTNAME(enemy) +
                   " with a draining touch!\n", enemy);
    enemy->catch_tell(
      TO->query_The_name(enemy) +
      " reaches out and strikes you with a draining touch!\n");

    seteuid(getuid(TO));
    drain = clone_object("/d/Raumdor/development/shanoga/common/obj/sdrain");
    drain->move(enemy, 1);
    set_alarm(0.1, 0.0, &drain->drain(enemy));

    return 1;
}
