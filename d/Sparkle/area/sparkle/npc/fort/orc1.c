/* Vladimir 8-09-94 */

#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>

#include "defs.h"

void
create_monster()
{
    set_race_name("orc");
    set_name("gurplez");
    set_title("the Worthless");
    set_adj("fat");
    set_alignment(-100);
    default_config_npc(10);

    add_adj("reeking");
    set_long("This total waste of flesh guards this part of the fortress.\n");

    set_skill(SS_DEFENCE, 10);
    set_skill(SS_WEP_KNIFE, 15);
    add_act("snarl");
    add_act("fart");
    add_act("burp");
    add_act("emote looks you up and down.");
    add_act("emote picks his nose.");
    add_chat("Kalach will eat you!!!");
    add_chat("I worship Kalach, he will come.");
    add_cchat("Now suffer the wrath of Kalack!");

    set_act_time(15);
    set_chat_time(40);
}

void
arm_me()
{
   setuid (); seteuid (getuid ());
   clone_object(S_LOCAL_WEP_DIR + "tknife")->move(TO);
   clone_object(S_LOCAL_ARM_DIR + "shirt")->move(TO);

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

