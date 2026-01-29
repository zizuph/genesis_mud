/*
 * bore1.c
 *
 * Used in carisca/f8.c carisca/f10.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
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
#include <stdproperties.h>

void mate();

void
default_config_npc(int i)
{
    int j;
    for (j = 0; j < 6; j++)
        set_base_stat(j, i);
}

void
do_die(object k)
{
    (ROKEDIR + "npc/borehandler")->kill_bore();
    ::do_die(k);
}

void
create_creature()
{
    default_config_npc(30);
    set_short("young wild boar");
    set_name("boar");
    set_adj("wild");
    set_long("This is a young wild boar with a mouth full of grim teeth.\n");
    set_race_name("boar");
    set_gender(0);

    add_act("emote taps silently with its feet in the ground.");
    add_act("growl carefully");
    set_act_time(7);

    set_attack_unarmed(0, 20, 20, W_IMPALE, 80, "grim teeth");

    set_hitloc_unarmed(A_HEAD, ({10}), 10, "head");
    set_hitloc_unarmed(A_BODY, ({15}), 80, "body");

    set_skill(SS_DEFENCE, 20);
    set_skill(SS_UNARM_COMBAT, 25);

    set_random_move(2);
    NEVERKNOWN;

    add_leftover(ROKEDIR + "obj/skin", "fur", 1, "", 1, 1);
    seteuid(getuid());

    set_alignment(100);
    set_alarm(120.0, 0.0, mate);
}

void
equip_me()
{
    clone_object(ROKEDIR + "wep/tooth1")->move(TO);
}

void
mate()
{
    object ob;
    object to = this_object();

    ob = present("female_bore", E(to));
    if (!ob)
    {
        set_alarm(25.0, 0.0, mate);
        return;
    }

    if (!(ob->pregnant()) &&
        (ROKEDIR + "npc/borehandler")->new_bore())
    {
        tell_room(E(to), "The young boar mounts the huge wild boar.\n");
        ob->mount();

        ob->add_prop(LIVE_S_SOULEXTRA, "pregnant");
    }
    set_alarm(120.0, 0.0, mate);
}
