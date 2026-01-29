/*******************************************************************\
| KING.C                                                            |
\*******************************************************************/

/*
 * 06/02/01 Arandir     Added quest bit porting
 *
 */

#pragma save_binary

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

#include S_DOMAIN_SYS_QUESTS


void
create_monster()
{
    set_name("king");
    add_name("dwarf");
    set_adj("dwarf");
    set_short("dwarf king");
    set_race_name("dwarf");

    set_long("The dwarf king looks very strong.\n");

    set_default_answer(VBFC_ME("otherrespons"));
    add_ask(({"coffee","about coffee","give me the cup","cup",
                  "the cup","give me coffee"}),VBFC("askfurther"),1);
    trig_new("%w 'says:' 'coffee' %s","givecup");
    trig_new("%w 'says:' 'coffee\n' %s","givecup");

    set_act_time(8);
    add_act("emote tries to climb the throne but fails.");
    add_act("emote walks around drinking his coffee. He seems to enjoy it a lot.\n");
    add_act("emote looks like he's got problems with his stomach.\n");

    default_config_npc(75);

    set_skill(SS_WEP_AXE,75);
    set_skill(SS_PARRY,30);
    set_skill(SS_DEFENCE,20);
}

void
arm_me()
{
    clone_object(S_LOCAL_WEP_DIR+"axe_mighty")->move(TO);
    clone_object(S_LOCAL_ARM_DIR+"mail")->move(TO);
    clone_object(S_LOCAL_ARM_DIR+"crown")->move(TO);
    clone_object(S_LOCAL_OBJ_DIR+"cup")->move(TO);
    command("wield all");
    command("wear all");
}

int
lift(string s)
{
    NF("Lift whom?\n");

    if(s != "king" && s!= "the king")
        return 0;

    seteuid(getuid(TO));

    TP->catch_msg("You help the king climbing his throne.\n");

    QUEST_PORT_TP (Q_OLD_DWARFHEIM_KING, Q_DWARFHEIM_KING, "ported bits for dwarfheim king.");

    if (!QUEST_TEST_TP (Q_DWARFHEIM_KING))
    {
        TP->add_exp(100,0);
        QUEST_SET_TP(Q_DWARFHEIM_KING);
        QUEST_LOG_TP("helped the dwarfheim king.");
        TP->catch_msg("You feel more experienced!\n");
    }

    say(QCTNAME(TP)+" helps the king up on the throne.\n");

    set_alarm(10.0, 0.0,
              &tell_room(E(TO),"The king jumps down from the throne to get something he dropped.\n"));

    return 1;
}

string
otherrespons(string s)
{
    command("emote just complains about his throne and his stomach.");
    return "";
}

string
askfurther(string s)
{
    QUEST_PORT_TP (Q_OLD_DWARFHEIM_KING, Q_DWARFHEIM_KING, "ported bits for dwarfheim king.");

    if (!QUEST_TEST_TP (Q_DWARFHEIM_KING))
    {
        command("say Why should We, the King, give our coffee to you?");
        command("say What have you done for us lately?");
        return "";
    }
    command("say We want Our coffee to help Our stomach.");
    return "";
}

string
givecup(string s)
{
    object ob;

    QUEST_PORT_TP (Q_OLD_DWARFHEIM_KING, Q_DWARFHEIM_KING, "ported bits for dwarfheim king.");

    if (!QUEST_TEST_TP (Q_DWARFHEIM_KING))
    {
        command("say Why should We, the King, give our coffee to you?");
        command("say Help Us to the throne, and We'll think about it.");
        return "";
    }
    command("emote laughs loudly. 'We will always help people that helps Us!");
    ob=present("cup",TO);
    ob->move(TP);
    tell_room(E(TO),"The King hands you his cup of coffee.\n");
}

void
init_living()
{
    ::init_living();

    add_action(lift, "lift");
}

