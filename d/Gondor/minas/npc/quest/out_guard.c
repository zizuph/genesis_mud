/*
 *  /d/Gondor/minas/npc/quest/out_guard.c
 *
 *  A guard for the whodunnit quest
 *  This guard is guarding the door into the house of Gimilzor
 *
 *  28-may-1995, Olorin
 */
inherit "/d/Gondor/minas/npc/std_gondor_guard";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

#define INVESTIGATION_CHATS ({ \
    "I hope they'll finish soon with their investigation so I can go home again.",\
    "As if it weren't bad enough that war is drawing nigh, now we also have murder in the city!",\
    "The murderer must have been a servant of the Enemy, but why would he kill a man like Gimilzor?",\
    "That body didn't look nice, no sir, it didn't!",\
    "He cut him up really good indeed.",\
    })

static int     investigation_active = 0;	// the guard will leave if the investigation has ended

int
start_investigation() 
{
    if (investigation_active)
        return 0;
    investigation_active = 1;
    return 1;
}

void
create_monster()
{
    ::create_monster();

    set_name("soldier");
    set_long(BSN("This is a soldier of the city guard."));

    default_config_npc(75);

    set_skill(SS_WEP_SWORD,   80);
    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_2H_COMBAT,   75);
    set_skill(SS_PARRY,       85);
    set_skill(SS_DEFENCE,     85);

    set_alignment(250 + random(250));

    set_chat_time(20);
    add_chat(VBFC_ME("chat"));

    set_act_time(20);
    add_act("sigh");
    add_act("emote walks around impatiently.");
    add_act("twiddle");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"help"}), VBFC_ME("ask_help"));
    add_ask(({"gimilzor"}), VBFC_ME("ask_gimilzor"));
    add_ask(({"murder", "murderer", "investigation", }), VBFC_ME("ask_murder"));
    add_ask(({"door", "open door", "entry", }), VBFC_ME("ask_door"));
}

string
default_answer()
{
    command("peer "+TP->query_real_name());
    command("say I don't know what you are talking about.");
    return "";
}

int
prop_check(object tp)
{
    return (tp->query_prop(MT_PW5_I_HUNTHOR_SENT_ME));
}

string
ask_gimilzor()
{
    int     seed;

    command("say Aye, he was murdered!");

    sscanf(OB_NUM(TO), "%d", seed);
    switch(random(4, seed))
    {
        case 0:
            command("say Well, it had to happen some day, he was just too greedy.");
            break;
        case 1:
            command("say He was such a fine man, always so helpful.");
            break;
        case 2:
            command("say He was just too rich for his own good.");
            command("say Too much money just makes other people hate you.");
            break;
        case 3:
            command("say A noble man, from a noble family.");
            command("say But he should have been a little more selective when choosing his business partners.");
            break;
    }

    return "";
}

string
ask_door()
{
    if (!investigation_active)
        return default_answer();

    if (!prop_check(TP))
        return default_answer();

    command("say I'll open the door for you.");
    set_alarm(2.0, 0.0, "open_door");

    return "";
}

string
ask_murder()
{
    if (!investigation_active)
        return default_answer();

    if (!prop_check(TP))
    {
        command("peer "+TP->query_real_name());
        command("say I don't think that is any of your business.");
        command("say Hunthor is in charge of the investigations.");
        return "";
    }
    command("say Hmm, well, you're not the only one who wants to learn more about that murder.");
    command("say The captain's inside, I'll let you in.");
    command("say He can tell you what we have found out until now.");

    set_alarm(3.0, 0.0, "open_door");

    return "";
}

string
ask_help()
{
    command("peer "+TP->query_real_name());
    command("say Help? You want help? With what?");
    return "";
}

void
arm_me()
{
    object  key;

    ::arm_me();

    key = clone_object("/std/key");
    key->set_key("MT_h1_ncrc4");
    key->move(TO, 1);

}

int
open_door()
{
    command("unlock door with key");
    command("open door");

    set_alarm(20.0, 0.0, "command", "close door");

    return 1;
}

string
chat()
{
    if (!investigation_active)
    {
        if (!(find_object(MT_PW5_MASTER)->query_status()) && !objectp(query_attack()))
        {
            set_alarm(2.0, 0.0, "move_living", "south", "/d/Gondor/workroom");
            set_alarm(4.0, 0.0, "remove_object");
            return "I guess I can go home now.";
        }
        else
            start_investigation();
    }

    return ONE_OF_LIST(INVESTIGATION_CHATS);
}
