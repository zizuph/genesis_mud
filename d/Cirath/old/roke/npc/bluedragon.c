/*
 * bluedragon.c
 *
 * Used in wild/dc2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

void trme(object tp);
void snok(object tp);

void
default_config_npc(int i)
{
    int j;
    for (j = 0; j < 6; j++)
        set_base_stat(j, i);
}

void
notify_been_zapped(object ob)
{
    if (!ob->query_prop("refnas_e_en_riktig_man_banka_gurka_det_kan_han"))
        return;

    set_alarm(3.0, 0.0, &trme(this_player()));
}

void
trme(object tp)
{
    tell_room(E(TO),
              "The dragon looks like hot jelly. It obviously has great " +
              "problems keeping it's shape.\n");
    set_alarm(3.0, 0.0, &snok(tp));
}

void
snok(object tp)
{
    object wiz;

    tell_room(E(TO),
              "Suddenly the dragon collapses, and transforms into a human.\n");
    seteuid(getuid(this_object()));
    wiz = clone_object(ROKEDIR + "npc/wizard");
    wiz->move(E(TO));
    wiz->reward(tp);

    remove_object();
}

void
create_creature()
{
    default_config_npc(150);

    set_name("dragon");
    set_race_name("dragon");
    set_living_name("bobban");

    set_short("blue dragon");
    set_adj("blue");

    set_long("This is the Blue Dragon of Nyreese. Rumors say that it is " +
             "an evil wizard that has been cursed by one of his enemies.\n");

    set_alignment(-1000);

    set_skill(SS_DEFENCE, 75);
    set_skill(SS_UNARM_COMBAT, 75);

    set_attack_unarmed(0, 50, 50, W_IMPALE, 50, "jaws");
    set_attack_unarmed(1, 50, 50, W_BLUDGEON, 50, "heavy tail");
    set_hitloc_unarmed(0, ({50}), 10, "head");
    set_hitloc_unarmed(1, ({50}), 80, "body");
    set_hitloc_unarmed(2, ({50}), 10, "tail");
}

int
query_knight_prestige()
{
    return 750;
}
