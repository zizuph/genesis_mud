/*
 * Hebalist of Green Oaks
 * Based on the herbalist in Rivendell
 * By Finwe, December 2004
 */

inherit "/std/monster";

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>

void
create_monster()
{
    set_race_name("elf");

    set_name("aralea");
    set_adj("talkative");
    set_adj("busy");
    set_short("talkative busy elf");
    set_long("This golden-haired elf is the Pubmaster of Green Oaks. " +
        "She has blue eyes and is very talkative. She offers some of " +
        "the best food and drink that can be found anywhere and keeps " +
        "order in her pub. Everyone talks to her, so she knows everything " +
        "that goes on in the town.\n");
    set_title("Sul'avor, Pubmaster of Green Oaks");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);

    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable

    default_config_mobile(90+random(10));

    set_gender(G_FEMALE);
    set_chat_time(40+random(10));
    add_chat("I sell the best food anywhere.");
    add_chat("You would not believe the news I have been told.");
    add_chat("I just heard that orcs are moving south.");
    add_chat("Some traveller said that the graveyard has become haunted.");
    add_chat("No one knows more than I do about what happens around here.");
    add_chat("Those outsiders are such a bother. I don't know why I put up with them.");
    add_chat("Don't just stand there, order something!");
    add_chat("What can I get you?");
    
    set_act_time(60+random(60));
    add_act("emote polishes the counter.");
    add_act("emote sweeps the floor.");
    add_act("emote clears a table and wipes it down.");
    add_act("emote greets a visitor.");
    add_act("emote wipes down the counter.");
    add_act("emote straightens up some glasses behind the counter.");

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
react_intro(object tp)
{
    if (!present(tp, ENV(TO)))
    {
        command("shrug");
        return;
    }

    command("introduce me to "+tp->query_real_name());
    command("say Welcome to Faerie!");
    return;
}


void
tour_react(object tp, object nt)
{
    //if (note->query_player_name() != tp->query_real_name())
    //    return;

    if (!objectp(tp) || !present(tp, ENV(TO)))
        return;
        
    if (!TP->query_met(query_real_name()))
    {
        react_intro(tp);
    }

    command("greet " + tp->query_real_name());
    command("say You must be from Menerial? She's always after reports.");
    command("say Here, let me see the note she gave you and I'll fill it " +
        "out and I'll sign it saying you were here.");
    command("emote takes the tour note.");
    command("emote writes a short report on the tour note.");
    command("emote gives the tour note back.");
    command("say There you go. Take it back to her for me please. Thank you.");
    nt->set_tour_done();
}


void
init_living()
{
    object  note;

    ::init_living();

    if (!(living(TP) && interactive(TP) && CAN_SEE(TO, TP)))
        return;

    if (objectp(note = present("faerie_tour_note", TP)))
    {
        if ((note->query_tour_no() == PUB_TOUR_NUM) && 
            (!note->query_tour_done()) &&
            (note->query_player_name() == TP->query_real_name()))
        {
            set_alarm(2.0, 0.0, &tour_react(TP, note));
            return;
        }
    }
    
    if (!TP->query_met(query_real_name()))
    {
        set_alarm(2.0 + 5.0 * rnd(), 0.0, &react_intro(TP));
        return;
    }
}

