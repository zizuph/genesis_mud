/*
 * sammy.c
 *
 * Used in nyreese/red_pub.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"
#include <ss_types.h>

inherit ROKEDIR + "lib/monster";

#include <money.h>

void
reset_me()
{
    set_alarm(1000.0, 0.0, reset_me);
    if (TOTAL_MONEY(this_object()) < 2*12*12) 
      MONEY_MAKE_GC(2)->move(this_object());
    set_intoxicated(0);
}

void
create_monster()
{
    int i;

    /*set_name("sammy");*/
    NEVERKNOWN;
    add_name("human");
    set_adj("red-nosed");

    set_long("This is a very poor excuse for a human being. He looks like " +
             "he spends most of his time here, drinking beer.\n");

    set_race_name("human");
    set_gender(0);

    for (i = 0; i < 6; i++)
      set_base_stat(i, 180*(6-i)/6);
    set_alignment(0);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_act_time(3);
    add_act("burp");
    add_act("buy beer");
    add_act("puke");
    add_act("drink all");
    add_act("giggle");

    ::create_monster();
    set_alarm(1.0, 0.0, reset_me);
}

void
do_die(object killer)
{
  write_file(ROKEDIR + "log/sammy", ctime(time()) + " " + killer->query_name() + "\n");
  ::do_die(killer);
}

int
query_knight_prestige()
{
    return 12;
}
