/*
 * fisherman.c
 *
 * Used in nyreese/cadu_s2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "std/monster";

#include "defs.h"
#include <macros.h>
#include <money.h>

void
create_monster()
{
    int i;

    set_name("fisherman");
    add_name("dirty");
    set_short("dirty fisherman");
    set_long("The fisherman is busy carrying fish from his boat " +
             "to a small shed to the north.\n");
  
    NEVERKNOWN;

    for (i = 0; i < 6; i++)
        set_base_stat(i, 15);

    set_all_attack_unarmed(10, 10); /* a good fighter */
    set_all_hitloc_unarmed(3);

    set_alignment(100);/* a good guy */

    MONEY_MAKE_CC(20)->move(TO);

    set_hp(250);

    set_act_time(1);
    add_act("whistle");
    add_act("say Have you seen the stairway to heaven? It's somewhere in the mountains.");
    add_act("stare");
}

int query_knight_prestige(){return -2;}
