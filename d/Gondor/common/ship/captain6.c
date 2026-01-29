#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/ship/captain.c";

#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define TICKET  (SHIP_DIR + "ticket6")
#define PRICE   30

public void
create_gondor_captain()
{
    set_name("falastaran");
    set_living_name("falastaran");
    set_race_name("human");
    add_adj("bald");
    add_adj("one-eyed");
    set_title("the Corsair");

    set_alignment(-250);

    set_chat_time(12);
    add_chat("Business is bad nowadays, there are not many merchantmen sailing anywhere.");
    add_chat("We have to chance upon not meeting the Gondorian navy today.");
    add_chat("The Haradrim give no quarter, but luckily, they don't have many ships.");
    add_chat("There's hardly any ship sailing up the Gwathlo these days.");
    add_chat("Sometimes, I think there are more corsairs on the seas than merchantmen.");
    add_chat("I wonder how long before the war breaks out.");
    add_chat("I've heard talk that the Dark Lord is capturing ships to increase His navy.");
    add_chat("Umbar is a beautiful place, very peaceful, comfortable to live in.");
    add_chat("Without any traders to capture, we have to take on paying passengers. "+
        "It's a mean world for a hard working corsair!");
    set_cchat_time(11);
    add_cchat("Hey! Are you one of the cursed rangers??!");
    add_cchat("Stop it, you pestering dog!");
    add_cchat("I fear noone but the Dark Lord!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    set_default_answer(VBFC_ME("default_answer"));

    set_ticket(TICKET);
    set_price(PRICE);
}

/* Solamnian knights prestige */
public int query_knight_prestige() {return 100;}

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
    if(str != "where" && str != "destination")
        ::catch_question(question);
    else if(!objectp(Ship))
        set_alarm(rnd()*4.0, 0.0, &command("say I'm not going anywhere!"));
    else
    {
        switch(Ship->query_location())
        {
            case 0:
                str = "We will sail to Lebennin shortly, and from there to Tharbad.";
                break;
            case 1..3:
                str = "We are on our way to Lebennin. From there we will sail to Tharbad.";
                break;
            case 4:
                str = "We will sail to Tharbad shortly.";
                break;
            case 5..12:
                str = "We are on our way to Tharbad.";
                break;
            case 13:
                str = "We will sail to Lebennin shortly, and from there upriver on the Poros.";
                break;
            case 14..21:
                str = "We are on our way to Lebennin, and from there upriver on the Poros.";
                break;
            case 22..23:
                str = "We will sail across the Anduin and from there upriver on the Poros.";
                break;
            case 24..25:
                str = "We are sailing upriver on the Poros to the Fords of Poros.";
                break;
        }
        command("say "+str);
    }
    return;
}

void
tour_react(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
        return;

    command("greet " + tp->query_real_name());
    command("say Are you coming from the Carastur?");
    command("emote takes the tour note.");
    command("emote writes a short report on the tour note.");
    command("emote gives the tour note back.");
    command("say Bring the tour note back to him and your task will be completed.");
}

void
init_living()
{
    object  note;

    ::init_living();

    if (!objectp(note = present("Pelargir_Tour_Note", TP)))
        return;

    if ((note->query_tour_no() != 0) || (note->query_tour_done()))
        return;

    note->set_tour_done();

    set_alarm(2.0, 0.0, &tour_react(TP));
}
