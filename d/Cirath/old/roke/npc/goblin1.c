/*
 * goblin1.c
 *
 * Used in nyreese/red_h1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(ROKEDIR + "wep/club")->move(TO);
    command("wield all");
}

void
create_monster()
{
    int i;

    set_name("goblin");
    set_short("filthy goblin");
    set_race_name("goblin");
    set_adj("filthy");

    set_gender(1);

    set_skill(SS_WEP_CLUB, 30);
    set_skill(SS_PARRY, 15);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 60);
    set_alignment(-35);

    add_chat("Please kill that nasty monster for me!");
    add_chat("The Jabberwock has invaded our town!");
    add_chat("He is east and south of here!");

    add_ask(({"quest", "assignment", "help", "jabberwock"}),
            "The goblin says: Bring me the head of the Jabberwock, " +
            "and you will get your reward!\n");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

int
query_knight_prestige()
{
    return 50;
}

void
enter_inv(object a, object b)
{
    ::enter_inv(a, b);
    if (member_array("jab_head", a->query_names()) > -1)
    {
        if (!QDONE(ROKEGROUP, JABBERWOCK))
        {
            QSET(ROKEGROUP, JABBERWOCK);
            QLOG("killed jabberwock");
            TP->add_exp(10000);
            TP->catch_msg("You feel more experienced!\n");
        }
        set_alarm(1.0, 0.0, &a->remove_object());
    }
}
