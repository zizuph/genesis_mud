/*
 * Chipmunk tamer of Green Oaks
 * By Finwe, January 2006
 * Updated by Gronkas, August 3, 2016 - fixed a typo
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

    set_name("Que'sha");
    add_name("quesha");
    add_name("que'sha");
    set_adj("excitable");
    set_adj("somber");
    set_short("excitable somber elf");
    set_long("This is the messenger keeper of Green Oaks. He has a way " +
        "with the animals, and has trained chipmunks to be special messengers " +
        "for the elves. He tirelessly keeps the cages clean and the animals " +
        "in good health.\n");
    set_title("Tal'anen, Messenger Keeper of Green Oaks");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);
    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable

    set_chat_time(40+random(10));

    set_gender(G_MALE);

    set_chat_time(60+random(60));
    add_chat("I've trained every one of my chipmunks to be expert messengers");
    add_chat("These chipmunks can be very temperamental.");
    add_chat("Would you like to hire a chipmunk as a messenger?");
    add_chat("Green Oaks is a wonderful place.");
    add_chat("I'm sure you have many tales to tell.");
    
    set_act_time(60+random(60));
    add_act("emote glances your way.");
    add_act("emote sweeps the floor.");
    add_act("emote cleans a cage.");
    add_act("emote greets a visitor.");
    add_act("emote feeds some chipmunks.");
    add_act("emote whistles.");

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
    command("say Ahh, she did. Here, let me see it and I'll note it " +
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
        if ((note->query_tour_no() == PO_TOUR_NUM) && 
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
