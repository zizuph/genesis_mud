/* Vision's Ghost, Sarr */
/* 2017-08-19 Malus: in, moving defaults to base/std file */
#include "defs.h"
#define A_BITE 0
#define A_LPAW 1
#define A_RPAW 2
inherit STD_UNDEAD;
inherit "/d/Raumdor/common/lib/paralyze.c";

object weapon, armour;

create_monster()
{
    ::create_monster();
    string adj = one_of_list(({
      "horrible", "ghastly", "dire", "awful",
    }));
    set_name("warrior");
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
      "emote hovers over the fresh corpse and its chest glows red for " +
      "amoment.");
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

int
special_attack(object enemy)
{
    int     i;
    object *players;
    object  paralyze_obj;
    string  message1;
    string  message2;

    if (random(15))
        return 0;

    // We want at least two ghosts in the room or this doesn't make sense
    if (sizeof(filter(all_inventory(E(TO)),
          &operator(==)(1) @ &->id("_raumdor_vghost"))) < 2)
        return 0;

    message1 = " abruptly lets out a sorrowful wail, and soon";
    message2 =
      " others join in, creating a ghastly disharmony that leaves you " +
      "trembling.\n",
    tell_room(E(TO), ({"One of the ghosts" + message1 + " the" + message2,
                       "One of the ghosts" + message1 + " the" + message2,
                       "Someone nearby" + message1 + message2}),
      0, TO);

    players = FILTER_PLAYERS(all_inventory(E(TO)));

    for (i = 0; i < sizeof(players); i++)
    {
        if (is_paralyzed(players[i]) || random(4))
            continue;

        players[i]->command("$scream");
        players[i]->catch_msg(
          "You fall to the ground and begin to sob, overcome with sorrow.\n");
        tell_room(E(players[i]),
          QCTNAME(players[i]) + " falls to the ground sobbing.\n", players[i],
          players[i]);
        paralyze_obj = paralyze(players[i]);
        paralyze_obj->set_fail_message("You are too overcome with sorrow!\n");
    }
    return 1;
}
