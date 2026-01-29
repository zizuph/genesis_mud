/*
 * Shopkeeper of Green Oaks
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

    set_name("falawas");
    set_adj("chatty");
    set_adj("nimble");
    set_short("chatty nimble elf");
    set_long("This golden-haired elf is the Shopkeeper of Green Oaks. " +
        "Her blue eyes are piercing and she oversees sales of the Shop. " +
        "Travellers from all over come here to trade with her, and the " +
        "items she sells are often the best found anywhere.\n");
    set_title("Ael'asian, Shopkeeper of Green Oaks");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);

    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable

    default_config_mobile(90+random(10));

    set_gender(G_FEMALE);
    set_chat_time(40+random(10));
    add_chat("You won't find any finer things for sale than here.");
    add_chat("Travellers come here from all over to buy my wares.");
    add_chat("Strange things are afoot, I've been told.");
    add_chat("Have you got anything good for sale?");
    add_chat("I will buy almost anything you have for sale.");
    add_chat("What can I get you?");
    
    set_act_time(60+random(60));
    add_act("emote polishes the counter.");
    add_act("emote sweeps the floor.");
    add_act("emote straightens some things up.");
    add_act("emote greets a visitor.");
    add_act("emote looks around.");
    add_act("emote smiles at you.");

}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
    command("say to " + TP->query_real_name() + " Nice to meet you! " +
        "What can I get for you?");
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
        if ((note->query_tour_no() == SHOP_TOUR_NUM) && 
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
