/*
 *  /d/Emerald/telberin/dock/sparkle/captain.c
 *
 *  This elf operates the ship which travels between
 *  Telberin and Sparkle.
 *
 *  Created August 2007, by Cooper Sherry (Gorboth)
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

#define TICKET  "/d/Emerald/telberin/dock/sparkle/ticket"
#define PRICE   30

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
    set_name("Fennan");
    set_living_name("fennan");
    add_name( ({ "fennan lil", "captain", "ship captain" }) );
    set_race_name("elf");
    add_adj("graceful");
    add_adj("silver-haired");
    set_title("Lil, Sea Master of the Telberin Ship Lines");

    set_short("graceful silver-haired elf");
    set_long("The eyes of this elf tell tales that the grace and"
      + " demeanor of his body do not. Clearly, he has seen the wonders"
      + " and horrors of the open sea for many a year.\n");

    config_elf(200); /* you know ... boat captain and all */
    set_skill(SS_SWIM, 100);
    set_alignment(250);

    add_prop(OBJ_M_NO_ATTACK,
        "As you come at the captain, he makes a swift gesture, and"
      + " you stagger back, your muscles spasming out of control. You"
      + " lose your balance and sit down hard! As you get back to your"
      + " feet the ferryman smiles grimly at you and shakes his head"
      + " from side to side.\n");
    set_ticket(TICKET);
    set_price(PRICE);

    add_telberin_asks();
    set_job_response("I am in charge of regular passage between"
      + " the City of Telberin and the port of Sparkle, Hub of Genesis.");

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
                str = "We are soon to be on our way to the far port"
                    + " of Sparkle, Hub of Genesis!";
                break;
            case 1..9:
                str = "We are on our way to Sparkle, traveller.";
                break;
            case 10:
                str = "Soon we will be on our way back to Emerald at the"
                    + " fair city of Telberin and her docks.";
                break;
            case 11..19:
                str = "We are on our way back to the fair city of"
                    + " Telberin in Emerald.";
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
    command("say Rillian? I'm afraid I've heard nothing about him,"
      + " but you might try with the other captains along these docks.");

    return "";
} /* rillian_answer */
