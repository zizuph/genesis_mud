/*
 * dragon.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";

#include "../../defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

object ob;
string name;

void check_if_there();
void check_if_there2();
void fl_there();

void
default_config_npc(int i)
{
    int j;
    for (j = 0; j < 6; j++)
        set_base_stat(j, i);
}

void
create_creature()
{
    default_config_npc(400);

    set_name("dragon");
    add_name("eskil");
    set_race_name("dragon");
    set_living_name("eskil");

    set_short("green sea dragon");
    set_adj("green");
    add_adj("sea");

    set_long("This is the Dragon of Revenge, summoned by a mighty dragonmaster.\n");

    set_alignment(1500);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 100);

    add_act("emote breathes ice.\n");

    set_act_time(2);

    name = "";
    add_notify_meet_interactive("meet_interactive");

    set_attack_unarmed(0, 100, 100, W_IMPALE, 100, "jaws");
    set_attack_unarmed(1, 100, 100, W_BLUDGEON, 100, "heavy tail");
    set_hitloc_unarmed(0, ({100}), 10, "head");
    set_hitloc_unarmed(1, ({100}), 80, "body");
    set_hitloc_unarmed(2, ({100}), 10, "tail");

    refresh_living();
}

void
meet_interactive()
{
    if (TP->query_real_name() == name)
    {
        if (!ob)
            ob = TP;
        if (ob != TP)
            command("confused");
        command("kill " + name);
        set_follow(name);
    }
}

void
destroy(string player)
{
    set_follow(player);
    command("kill " + player);

    ob = find_player(player);
    name = player;

    set_alarm(30.0, 0.0, check_if_there);
}

void
check_if_there()
{
    heal_hp(30);
    if (!ob)
    {
        command("laugh");
        set_alarm(300.0, 0.0, check_if_there2);
        return;
    }
    if (!present(ob, ENV(TO)))
    {
        /* he has escaped */

        set_alarm(2.0, 0.0, fl_there);
    }

    set_alarm(30.0, 0.0, check_if_there);
}

void
check_if_there2()
{
    object pl;
    pl = find_player(name);
    heal_hp(300);
    if (pl)
    {
        if (ENV(TO) != ENV(pl))
        {
            tell_room(ENV(TO), "The dragon flies away.\n");
            tell_room(ENV(pl), "A huge green dragon arrives from the sky.\n");
            move_living("M", ENV(pl));
        }
        command("say Gotcha!");
        set_follow(name);
        command("kill " + name);
        ob = pl;
        set_alarm(30.0, 0.0, check_if_there);
    }
    else
    {
        set_alarm(300.0, 0.0, check_if_there2);
    }
}

void
fl_there()
{
    if (!ob)
    {
        command("shrug");
        return;
    }

    if (ENV(TO) != ENV(ob))
    {
        tell_room(ENV(TO), "The dragon flies away.\n");
        tell_room(ENV(ob), "A huge green dragon arrives from the sky.\n");
        move_living("M", ENV(ob));
    }
    command("kill " + name);
}

void
notify_you_killed_me(object obj)
{
    log_file("dragon", capitalize(obj->query_real_name()) +
             " was killed by the mighty dragon.\n");
    if (obj == ob)
    {
        tell_room(ENV(TO),
                  "The dragon feels satisfied, as he has gotten his revenge.\n" +
                  "He flies away, towards his home in the ocean.\n");
        remove_object();
    }
}
