/*
 * dragonmaster.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "../../defs.h"
#include <macros.h>

void dragon(string s);
void dragon2(string s);
void remove_kroll();

void
create_monster()
{
    set_name("kroll");
    set_long("He is a powerful Dragonmaster.\n");
    set_adj("massive");

    default_config_npc(100);
}

void
not(string s)
{
    set_follow(s);

    command("introduce me");
    command("shout I am Kroll, the brother of Krell and Krull, male dragonmaster!!!");
    command("shout You killed my brother!!!");

    set_alarm(10.0, 0.0, &dragon(s));
}

void
dragon(string s)
{
    command("emote waves with his hands and chants a few words in the true language.");

    set_alarm(5.0, 0.0, &dragon2(s));
}

void
dragon2(string s)
{
    object ob;

    ob = clone_object(SHIPDIR + "monster/dragon");
    ob->move_living("X", environment(find_player(s)));
    ob->destroy(s);

    command("laugh");

    set_alarm(5.0, 0.0, remove_kroll);
}

void
remove_kroll()
{
    tell_room(ENV(TO), "Kroll disappears in a puff of smoke.\n");
    remove_object();
}
