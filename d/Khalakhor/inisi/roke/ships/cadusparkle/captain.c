/*
 * captain.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Ported to the new ship system by Tapakah, 10/2008
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "../../defs.h"
#include <filter_funs.h>
#include "/d/Genesis/ship_new/ships.h"

inherit STDCAPTAIN;

object ship;
int has_introduced = 0;

void grimoire_found(object ob);

void
do_die(object killer)
{
    object dm;

    if ((query_hp() > 0))
        return;

    tell_room(ENV(TO), "Just before Krell dies, he chants a few words.\n");

    seteuid(getuid(TO));
    dm = clone_object(SHIPDIR + "monster/dragonmaster");
    dm->move_living("X", ENV(killer));
    dm->not(killer->query_real_name());

    ::do_die(killer);
}

void
set_ship(object s)
{
    ship = s;
}

void
create_captain()
{
 	::create_captain();
    set_name("krell");
    add_name("admiral");
    set_living_name("krell");
    set_race_name("human");
    add_adj("friendly");

    add_subloc("snok", this_object());

    default_config_npc(60);
    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 45);
    set_skill(SS_DEFENCE, 34);

    set_alignment(200);

    seteuid(getuid(TO));

    set_mm_in("falls out of the sky.");
    set_mm_out("dissolves in a thin cloud of smoke.");
    set_m_in("staggers in, singing an old song of war");
    set_title("the famous admiral");
    add_notify_meet_interactive("no_grimoire");
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc == "snok")
        return "He is wearing a huge ring with a picture of a dragon.\n";
    return ::show_subloc(subloc, on, for_obj);
}

void
introduce_me()
{
    command("introduce myself");
}

void
remove_int()
{
    has_introduced = 0;
}


void
add_introduced(string person)
{
    if (!has_introduced)
    {
        set_alarm(4.0, 0.0, introduce_me);
        has_introduced = 1;
        set_alarm(15.0, 0.0, remove_int);
    }
}

/*  This routine steals the grimoire from the castle so that it cant
    get out of the domain...
    Some code changed by Ged (Orig code by Mercade) to
    check for grimoires in sacks and chests and so on...
 */


void
no_grimoire()
{
    object *players;
    object *obs;
    int i;
    int j;
    float set_alarm_time;

    set_alarm_time = 4.0;
    players = FILTER_LIVE(all_inventory(ENV(TO)));

    for (i = 1; i < sizeof(players); i++)
    {
        obs = deep_inventory(players[i]);

        for (j = 1; j < sizeof(obs); j++)
        {
            if (obs[j]->id("refnasgrim"))
            {
                obs[j]->remove_object();
                set_alarm(set_alarm_time, 0.0, &grimoire_found(players[i]));
                set_alarm_time += 2.0;
            }
        }
    }

    return;
}

void
grimoire_found(object ob)
{
    command("shout I don't want such dangerous things on my ship!");
    command("shout Give me that.");
    ob->catch_msg(QCTNAME(TO) + " takes your grimoire.\n");
    tell_room(ENV(TO), "The captain takes something from " + QTNAME(ob) +
              ".\n", ob);
    
    return;
}
