/*
 * car_spirit.c
 * FIXA
 * Used in carisca/s2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* a mighty spirit */

/*  Changes made 2/4/98 Amelia:
 *  workaround made for this_player calls in 
 *  the set_alarms, since they did not function
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

void test_summoner();
void talaett();
void talatva();
void talatre();
void talafyra();
void talafem();
void talasex();
void talasju();
void talaatta();

object tp;

void
create_monster()
{
    default_config_npc(75);

    set_name("spirit");
    set_race_name("spirit");
    set_short("spirit of the pole");
    set_adj("pole");

    set_long("This is a spirit summoned by some magic force.\n");

    set_alignment(5000);

    seteuid(getuid());

    add_prop(OBJ_I_NO_MAGIC_ATTACK, 1);
    add_prop(OBJ_I_NO_ATTACK, 1);

    set_alarm(10.0, 0.0, test_summoner);
}

void
test_summoner()
{
    if (!objectp(tp))
    {
        say("The spirit dissolves.\n");
        remove_object();
    }
}

void
summoner(object o)
{
    tp = o;
    set_alarm(10.0, 0.0, talaett);
}

void
talaett()
{
    command("say I am the Spirit of The Volcano!");
    set_alarm(7.0, 0.0, talatva);
}

void
talatva()
{
    command("say I will grant you three wishes!");
    command("say First I suppose that you want to get away from here!");

    set_alarm(5.0, 0.0, talatre);
}

void
talatre()
{
    tp->catch_msg("The pole spirit waves with his hands.\n");
    tp->move_living("into a strange mist", CARISCADIR + "m", 1);
    TO->move_living("into a strange mist", CARISCADIR + "m");

    set_alarm(10.0, 0.0, talafyra);
}

void
talafyra()
{
    command("say oooopssss!!!");
    command("blush");

    set_alarm(10.0, 0.0, talafem);
}

void
talafem()
{
    command("say It seems like I have made a mistake...");
    command("say I will correct it, but it will take another wish...");

    set_alarm(5.0, 0.0, talasex);
}

void
talasex()
{
    tp->catch_msg("The pole spirit waves with his hands.\n");
    tp->move_living("into a strange mist", CARISCADIR + "t", 1);
    TO->move_living("into a strange mist", CARISCADIR + "t", 1);

    set_alarm(7.0, 0.0, talasju);
}

void
talasju()
{
    command("ponder");
    set_alarm(4.0, 0.0, talaatta);
}

void
talaatta()
{
    object s;

    command("say I presume that you are out solving a quest...");
    command("say Take this stick and return to the mayor, and you will be " +
            "rewarded for your efforts!");

    s = clone_object(ROKEDIR + "obj/strange");
    s->move(tp);
    s->add_prop("_roke_given_by_spirit", tp);

    tp->catch_msg("The pole spirit gives you a strange " +
                  "wooden stick, and then he dissolves himself.\n");
    say("The spirit dissolves.\n", ({tp}));
    remove_object();
}
