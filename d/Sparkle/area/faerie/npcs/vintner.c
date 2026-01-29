/*
 * Vintner of Green Oaks
 * By Finwe, April 2005
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

    set_name("isenrain");
    set_adj("noble");
    set_adj("somber");
    set_short("noble somber elf");
    set_long("This is the vintner of Green Oaks. His skills include " +
        "distilling fruits and brewing the best wines for all occasions. " +
        "His somber demeanor hides a rather cheerful disposition, " +
        "especially after he's sampled too much of his own drinks. His " +
        "grey eyes twinkle and he's most happy to assist you.\n");
    set_title("Kit'leren, Vintner of Green Oaks");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);
    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable

    set_chat_time(40+random(10));

    set_gender(G_MALE);

    set_chat_time(60+random(60));
    add_chat("Check out my fine wines.");
    add_chat("The wine list shows all the wines for sale.");
    add_chat("Elderberry wine is my favorite drink.");
    add_chat("A good wine goes with every occasion.");
    add_chat("My wines may be expensive, but they are worth the price.");
    add_chat("Everyone knows elven wines are the best anywhere.");
    add_chat("What can I get you?");
    
    set_act_time(60+random(60));
    add_act("emote polishes the counter.");
    add_act("emote sweeps the floor.");
    add_act("emote arranges his wine methodically.");
    add_act("emote greets a visitor.");
    add_act("emote does some busy work behind the counter.");
    add_act("emote washes some glasses.");

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
    command("say You must be from Menerial? Did she give you anything?");
    command("say Ahh, she did. Here, let me see it and I'll sign it " +
        "saying you were here.");
    command("emote takes the tour note.");
    command("emote writes a short report on the tour note.");
    command("emote gives the tour note back.");
    command("say There you go. Take it back to her for me please and " +
        "you will be done.");
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
        if ((note->query_tour_no() == VINT_TOUR_NUM) && 
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
