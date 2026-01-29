/* Vladimir 8-09-94 */

#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>

#include "local.h"

void
create_monster()
{
    set_race_name("orc");
    set_name("jazmine");
    set_title("the Smelly");
    set_adj("smelly");
    set_alignment(-100);
    default_config_npc(5);

    add_adj("wretched");
    set_long("You seem to have disturbed this orc as "+
             "he is about to fall asleep. He does not "+
             "look happy about it.\n");

    add_chat("I will sacrifice you to Kalach!");
    add_chat("Some say that ducks are what Kalach desires!");
    set_chat_time(2);
    set_skill(SS_DEFENCE, 4);
    set_skill(SS_WEP_KNIFE, 4);
}

void
arm_me()
{
    clone_object(ORC+"obj/tknife2")->move(TO);
    clone_object(ORC+"obj/sleepshirt")->move(TO);

    command("wear all");
    command("wield all");
}

void
do_introduce(object tp)
{
    if (!present(tp, ENV(TO)))
        return;

    command("introduce me to "+ tp->query_real_name());
}

void
add_introduced(string str)
{
    if (TP->query_npc() || TP->query_met(query_name()))
        return;

    set_alarm(2.0, 0.0, &do_introduce(TP));
}
