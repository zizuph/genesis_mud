/*
 * prisoner.c
 * FIXA
 * Used in nyreese/cas_dung1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <macros.h>

int started;

void treffa();
void gogge(object tp);
void gogge2(object tp);
void gogge3(object tp);
void gogge4(object tp);

int
query_knight_prestige()
{
    return -1;
}

void
create_monster()
{
    started = 0;

    set_alignment(199);

    set_name("prisoner");
    set_adj("old");
    add_adj("dying");

    set_long("This is an old dying prisoner. He has obviously been here " +
             "a very long time.\n");

    default_config_npc(13);

    set_hp(10000);

    set_race_name("hobbit");

    add_notify_meet_interactive("treffa");
}

void
init_living()
{
    // que? FIXA
    add_action("treffa", "", 1);
}

void
treffa()
{
    if (!started && E(TO)->query_prop(OBJ_I_LIGHT) > 0)
    {
        started = 1;
        set_alarm(2.0, 0.0, &gogge(TP));
    }
}

void
gogge(object tp)
{
    command("smile");

    set_alarm(1.0, 0.0, &gogge2(tp));
}

void
gogge2(object tp)
{
    command("say Finally someone that can release me from my captivity.");
    command("whisper " + tp->query_real_name() +
            " I will tell you something...");

    set_alarm(2.0, 0.0, &gogge3(tp));
}

void
gogge3(object tp)
{
    command("whisper " + tp->query_real_name() +
            " Many years ago, I worked for the good");
    command("whisper " + tp->query_real_name() +
            " wizard Kanthrun who ruled the castle.\n"); //FIXA wiznamn inkonsekvent
    command("whisper " + tp->query_real_name() +
            " But one day the evil Refnas turned him");
    command("whisper " + tp->query_real_name() + " into a dragon.");

    command("emote looks very weak.");

    set_alarm(3.0, 0.0, &gogge4(tp));
}

void
gogge4(object tp)
{
    command("whisper " + tp->query_real_name() +
            " Rumours says that Refnas' wand can turn him back...");

    set_hp(0);
    do_die(0);
}
