/*
 * Banker of Green Oaks
 * By Finwe, December 2004
 */

inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

#include "defs.h"

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>

//object note;

void
create_monster()
{
    set_name("vefrain");
    set_race_name("gnome");
    set_adj("greedy");
    set_adj("friendly");
    set_short("friendly greedy gnome");
    set_long("This gnome is the money-lender of the bank. He's short " +
        "and very preoccupied with his ledgers, and counting and re-"+
        "counting his money. He is greedy and hoards all the money he " +
        "gets behind the counter.\n");

    set_gender(G_MALE);
    set_stats(({ 40,40,40,40,40,40}));

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);
    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable

    default_config_mobile(90+random(10));

    set_chat_time(40+random(10));
    add_chat("I CaN kEEP yOUR mOnEy FOR yOu.");
    add_chat("wHAT cAn I hElP yOU WiTh?");
    add_chat("MoNeY iS THe BeSt ThInG iN THe WoRLD!");
    add_chat("I caN OPen An aCCouNT If yOu Do NoT HAve OnE YEt.");
    add_chat("We HAvE ThE BeST RaTEs aNYwHEre.");

    set_act_time(60+random(60));
    add_act("emote counts some money behind the counter.");
    add_act("emote stacks some money behind the counter.");
    add_act("emote writes something down in a ledger.");
    add_act("emote looks up from his ledgers and looks at you.");
    add_act("emote arranges his ledgers carefully.");
    add_act("emote scribbles something down hurriedly");
    add_act("emote polishes a coin.");

}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
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
    command("say WElCoME tO FaERIE!");
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
    command("say yOu MuST bE fROM MeNERiAL? dID SHe gIV yOu AnYthING?");
    command("say aHH, SHe dID. HeRE, lET Me sEE It AnD I WiLL NOte iT " +
        "saYING yOu WeRE HeRE.");
    command("emote takes the tour note.");
    command("emote writes a short report on the tour note.");
    command("emote gives the tour note back.");
    command("say THeRE yOu gO. TaKE It bACK tO HeR FOR Me PleASEE aND " +
        "yOu WiLL bE doNE.");
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
        if ((note->query_tour_no() == BANK_TOUR_NUM) && 
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
