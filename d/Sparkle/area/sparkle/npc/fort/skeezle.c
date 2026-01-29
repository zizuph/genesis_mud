/*******************************************************************\
| SKEEZLE.C                                                         |
\*******************************************************************/

/*
 * 06/02/01 Arandir     Added quest bit porting
 *
 */

#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"
// The following inherits give s_log and s_get_Name which are used in
// the QUEST_LOG define
inherit S_DOMAIN_LIB_DIR + "libs_logging";
inherit S_DOMAIN_LIB_DIR + "libs_player";

#include S_DOMAIN_SYS_QUESTS

int has_introduced=0;
int figure;

void
create_monster()
{
    set_name("skeezle");
    set_title("the Hopeless");
    set_race_name("orc");
    set_long("She looks very upset about something.\n");

    set_adj("upset");
    set_gender(1);
    add_name("genorc");

    add_prop(OBJ_M_NO_ATTACK, "After careful consideration, you decide not" +
      " to attack this poor creature.\n");

    default_config_npc(15);

    refresh_mobile();

    set_skill(SS_DEFENCE, 40);

    add_act("emote sobs.");
    add_act("sigh");
    add_act("emote smiles grimly.");
    add_act("sniff");

    add_chat("Find me my figurine!");
    add_chat("Have you seen it?!");

    add_cchat("My son will eat you!");

    set_act_time(20);
    set_chat_time(50);

    set_default_answer("She cries: Give me my figurine back!!!!\n");
}

void
arm_me()
{
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    setuid (); seteuid (geteuid ());

    clone_object(S_LOCAL_ARM_DIR + "shirt")->move(TO);
    command("wear all");
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

void
figure_return()
{
    figure = 1;
}

public void
enter_inv(object ob, object from)
{
    if(ob->id("genfigure"))
    {
        if(interactive(from))
        {
            QUEST_PORT (from, Q_OLD_ORC_FIGURINE, Q_ORC_FIGURINE, "ported bits for orc figurine.");

            if(QUEST_TEST (from, Q_ORC_FIGURINE))
            {
                command("puke " + TP->query_name());
                TP->catch_msg("You don't feel more experienced.\n");
            }
            else
            {
                command("thank " + TP->query_name());
                TP->catch_msg("You feel more experienced.\n");
                TP->add_exp(1000, 0);
                QUEST_SET (from, Q_ORC_FIGURINE);
                QUEST_LOG (from, "returned the orc figurine.");
            }

            ::enter_inv(ob,from);
            set_alarm(1.0,0.0,"remove_the_object",ob);

        }
    }

    ::enter_inv(ob,from);
    set_alarm(2.0,0.0,"drop_the_object",ob);
}

void
remove_the_object(object ob)
{
    ob->remove_object();
}

void
drop_the_object(object ob)
{
    command("drop " + ob->query_short());
}

