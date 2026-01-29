/*
 *	/d/Gondor/common/ship/captain8.c
 *
 *	Coded by Finwe, September 2005
 *
 *	Modification log:
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/ship/captain.c";
inherit "/d/Gondor/common/ship/pel_tours.c";

#include "/d/Gondor/defs.h"

#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define TICKET  (SHIP_DIR + "ticket8")
#define PRICE   720

public void
create_gondor_captain()
{
    set_name("ilderril");
    add_name( ({ "man", }) );
    set_living_name("ilderril");
    set_race_name("human");
    set_adj(({"strong", "barrel-chested"}));
    set_title("the Sea Mariner");

    set_chat_time(12);
    add_chat("The Elves are leaving, never to return.");
    add_chat("Minas Tirith is still bustling with activity. Trade is good.");
    add_chat("Competition is not hard nowadays.");
    add_chat("I wonder how long before the war breaks out.");
    add_chat("You'll arrive safely when you travel with me.");
    add_chat("Those Corsairs are dangerous, but they've never caught me.");
    add_chat("My ship is one of the fastest on the open seas.");
    add_chat("Fair wind today. We should be able to stay on schedule.");
    add_chat("I think there will be a good wind to sail up coast.");
    add_chat("The open ocean is a dangerous place, but I've sailed it many times.");

    set_cchat_time(11);
    add_cchat("Hey! Are you one of the pirates of Umbar??!");
    add_cchat("Stop it, you pestering dog!");
    add_cchat("I fear noone but the Corsairs of Umbar!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    set_up_pelargir_tour();

    set_ticket(TICKET);
    set_price(PRICE);
}

public void
catch_question(string question)
{
    int     i,
            length;
    string  str;

    if (dont_answer_unseen && (!TP->check_seen(TO) ||
        !CAN_SEE_IN_ROOM(TO)))
    {
	set_alarm(rnd()*3.0 + 1.0, 0.0, unseen_hook);
	return;
    }

    i = strlen(question);
    if (question[i - 1] == "."[0] || question[i - 1] == "?"[0])
	question = extract(question, 0, i - 2);

    posed_question = lower_case(question);

    str = explode(posed_question," ")[0];
    if (str != "where" && str != "destination")
	::catch_question(question);
    else if (!objectp(Ship))
        set_alarm(rnd()*4.0, 0.0, &command("say I'm not going anywhere!"));
    else
    {
        switch(Ship->query_location())
        {
	case 0:
	    str = "We will sail out onto the open ocean, up the Anduin, " +
            "and dock at Harlond.";
	    break;
	case 1..6:
	    str = "We are on our way to Harlond, the harbour of Minas Tirith.";
	    break;
	case 7:
	    str = "We will sail down the Anduin, out onto the Great Sea, " +
            "and land at Mithond.";
	    break;
	case 8..13:
	    str = "We are on our way to Mithlond, also known as the Grey Havens.";
	    break;
        }
        command("say "+str);
    }
    return;
}
