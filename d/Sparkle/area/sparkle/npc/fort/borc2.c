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
    set_name("tander");
    set_title("the Bouncer");
    set_adj("well-built");
    set_alignment(-100);
    default_config_npc(17);

    add_adj("broad-shouldered");
    set_long("This is one of the two bouncers that work at the bar. "+
             "You feel as though messing with him would be a bad idea.\n");

    set_skill(SS_DEFENCE, 10);
    set_skill(SS_WEP_KNIFE, 15);
}

void
arm_me()
{
   setuid (); seteuid (getuid ());
   clone_object(S_LOCAL_WEP_DIR + "tknife")->move(TO);
   clone_object(S_LOCAL_ARM_DIR + "bshirt")->move(TO);

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

