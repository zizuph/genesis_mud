/*
 * Fred the NPC
 * Sample NPC for bit_quests
 * By Finwe, June 2017
 */

inherit "/std/monster";

#include "../defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>

void
create_monster()
{
    set_race_name("elf");

    set_name("fred");
    set_adj("noble");
    set_adj("somber");
    set_short("noble somber elf");
    set_long("This is Fred. Be nice to Fred\n");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);
    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable

    set_chat_time(40+random(10));

    set_gender(G_MALE);
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
    command("say to " + TP->query_real_name() + " Nice to meet ya!");
    command("shake " + TP->query_real_name() );
}


void
quest_react(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
        return;

    command("greet " + tp->query_real_name());
    command("say You must be here for a signature.");
    command("say Please let me see it and I'll sign it for you");
    command("emote takes the quest note.");
    command("emote writes a short report on the quest note.");
    command("emote gives the quest note back.");
    command("say There you go. Return and report..");
}

void
react_intro(object tp)
{
    if (!present(tp, ENV(TO)))
    {
        command("shrug");
        return;
    }

    command("introduce me to " + tp->query_real_name());
    command("say It's nice to meet you!");
    return;
}

void
init_living()
{
    object  note;

    ::init_living();

    if (living(TP) && interactive(TP) && CAN_SEE(TO, TP) &&
        !(TP->query_met(query_real_name())))
    {
        set_alarm(2.0 + 5.0 * rnd(), 0.0, &react_intro(TP));
        return;
    }

    if (!objectp(note = present(QUEST_NOTE_PROP, TP)))
        return;

    if ((note->query_quest_no() != FRED_QUEST_NUM) || (note->query_quest_done()))
        return;

    note->set_quest_done();

    set_alarm(2.0, 0.0, &quest_react(TP));

}
