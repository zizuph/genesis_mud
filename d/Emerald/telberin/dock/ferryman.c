/*
 *  /d/Emerald/telberin/dock/ferryman.c
 *
 *  This elf operates the ferry which travels between
 *  Telberin and the North Shore.
 *
 *  Copyright (c) June 2003, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Emerald/telberin/npc/telberin_elf";
inherit "/d/Genesis/ship/captain";

#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define TICKET  "/d/Emerald/telberin/dock/ferry_ticket"
#define PRICE   10

/* prototypes */
public void        arm_me();
public string      rillian_answer();

/* global variables */
static object    Ship;

/*
 * Function name: set_ship
 * Description:   Set our ship.
 */
public void
set_ship(object s)
{
    Ship = s;
}

public void
create_captain()
{
    set_name("ferundi");
    set_living_name("ferundi");
    add_name( ({ "ferryman", "ferry man", "ferundi indell",
                 "captain", "ferry captain" }) );
    set_race_name("elf");
    add_adj("old");
    add_adj("silver-haired");
    set_title("Indell, Ferryman of the Telberin Docks");

    set_short("old silver-haired elf");
    set_long("This elf, though old and careworn, looks quite powerful."
      + " There is a potency in his eyes which betrays his elderly"
      + " gentle appearance.\n");

    config_elf(200); /* you know ... boat captain and all */
    set_skill(SS_SWIM, 100);
    set_alignment(250);

    add_prop(OBJ_M_NO_ATTACK,
        "As you come at the ferryman, he makes a swift gesture, and"
      + " you stagger back, your muscles spasming out of control. You"
      + " lose your balance and sit down hard! As you get back to your"
      + " feet the ferryman smiles grimly at you and shakes his head"
      + " from side to side.\n");
    set_ticket(TICKET);
    set_price(PRICE);

    add_telberin_asks();
    set_job_response("I am in charge of regular passage between"
      + " the City of Telberin and the north shore where our"
      + " troops have been garrisoned lately.");

    add_ask( ({ "rillian" }), VBFC_ME("rillian_answer"));
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
        command("say Who said that? I must be hearing voices.");
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
                str = "We are soon to be on our way to the north"
                    + " shore of Lake Telberin.";
                break;
            case 1..3:
                str = "We are on our way to the north shore of Lake"
                    + " Telberin.";
                break;
            case 4:
                str = "Soon we will be on our way back to the"
                    + " fair city of Telberin and her docks.";
                break;
            case 5..12:
                str = "We are on our way to Telberin.";
                break;
        }
        command("say "+str);
    }
    return;
}


/*
 * Function name:        arm_me
 * Description  :        give the npc a weapon
 */
public void
arm_me()
{
    object  sword;

    sword = clone_object("/d/Emerald/telberin/obj/wep/longsword");
    sword->move(this_object());

    command("wield all");
} /* arm_me */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Yes, what's that? Who's there?");
        return;
    }

    command("introduce me");
} /* react_intro */


/*
 * Function name:       rillian_answer
 * Description  :       response to an add_ask
 */
public string
rillian_answer()
{
    command("say Rillian ... Rillian ... yes, somehow"
      + " that name does ring a bell.");
    command("say I recall that I gave someone by that name"
      + " passage to the north shore quite a long time"
      + " ago.");
    command("say Let me think ... yes, he's the one who"
      + " kept insisting he was going to make his master"
      + " so proud. He never did return, did he ...");

    return "";
} /* rillian_answer */
