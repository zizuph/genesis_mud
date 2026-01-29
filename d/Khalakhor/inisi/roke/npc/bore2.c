/*
 * bore2.c
 *
 * Used in carisca/f10.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

int pregn = 0;

void
default_config_npc(int i)
{
    int j;
    for (j = 0; j < 6; j++)
        set_base_stat(j, i);
}

int
pregnant()
{
    return pregn;
}

void
breed()
{
    int i;
    object ob;
    pregn = 0;
    i = random(2) + 1;

    ob->clone_object(ROKEDIR + "npc/bore" + i);
    ob->equip_me();
    ob->move(ENV(TO));

    tell_room(ENV(TO), "The wild boar gives birth to a new boar.\n");
    remove_prop(LIVE_S_SOULEXTRA);
}

void
mount()
{
    pregn = 1;
    set_alarm(45.0, 0.0, breed);
}

void
do_die(object k)
{
    (ROKEDIR + "npc/borehandler")->kill_bore();
    if (pregn)
        (ROKEDIR + "npc/borehandler")->kill_bore();

    ::do_die(k);
}

int
gogga()
{
    if (present("grugg", ENV(TO)))
        command("kill grugg");
    return 1;
}

void
add_spit()
{
    set_this_player(this_object());
    add_action(gogga, "gogga");
}

void
equip_me()
{
    clone_object(ROKEDIR + "wep/tooth2")->move(TO);
}

void
create_creature()
{
    default_config_npc(40);
    set_short("huge wild boar");
    set_name("boar");
    add_name("female_bore");
    set_gender(1);

    set_adj("wild");
    set_long("This is a huge wild boar with a mouth full of grim teeth.\n");
    set_race_name("boar");

    set_attack_unarmed(0, 25, 25, W_IMPALE, 90, "grim teeth");

    set_hitloc_unarmed(A_HEAD, 10, 10, "head");
    set_hitloc_unarmed(A_BODY, 25, 80, "body");

    add_act("emote stomps forcefully in the ground with its feet.");
    add_act("growl wild");
    add_act("gogga");
    add_act("spit on grugg");

    add_cact("spit on grugg");
    set_cact_time(15);

    set_act_time(7);

    seteuid(getuid());

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_UNARM_COMBAT, 40);

    NEVERKNOWN;
    set_random_move(2);

    add_leftover(ROKEDIR + "obj/skin", "fur", 1, "", 1, 1);
    set_alignment(150);
    add_spit();
}
