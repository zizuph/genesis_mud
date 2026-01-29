/*
 * sammy.c
 *
 * Used in nyreese/red_pub.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <money.h>

void
reset_me()
{
    set_alarm(1000.0, 0.0, reset_me);
    MONEY_MAKE_GC(2)->move(this_object());
    set_intoxicated(0);
}

void
create_monster()
{
    int i;

    set_living_name("sammy");
    set_name("sammy");
    add_name("human");
    set_adj("red-nosed");

    set_long("This is a very poor excuse for a human being. He looks like " +
             "he spends most of his time here, drinking beer.\n");

    set_race_name("human");
    set_gender(0);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 60);
    set_alignment(0);

    set_act_time(3);
    add_act("burp");
    add_act("buy beer");
    add_act("puke");
    add_act("drink all");
    add_act("giggle");

    ::create_monster();
    set_alarm(1.0, 0.0, reset_me);
}

int
query_knight_prestige()
{
    return 12;
}
