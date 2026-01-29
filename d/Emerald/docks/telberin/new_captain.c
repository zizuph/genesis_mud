/*
 *  /d/Emerald/docks/telberin/captain.c
 *
 *  This elf operates the ship which travels between
 *  Telberin and Ceral Isle.
 *
 *  Copyright (c) August 2003, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Emerald/telberin/npc/telberin_elf";
inherit "/d/Genesis/ship/captain";

#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define PRICE   10

/* prototypes */
public void        arm_me();

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
    set_name("harfex");
    set_living_name("harfex");
    add_name( ({ "ferundi narm", "captain", "ship captain" }) );

    set_race_name("elf");
    add_adj("quiet");
    add_adj("silver-eyed");

    set_title("Narm, Captain of the Telberin Shipping Line");

    set_short("quiet, silver-eyed elf");
    set_long("This quiet elf has seen many years come and go."
      + " His silver eyes stare constantly to the water, where"
      + " he seems to find some solace against cares you cannot"
      + " guess at.\n");

    config_elf(200); /* you know ... boat captain and all */
    set_skill(SS_SWIM, 100);
    set_alignment(250);

    add_prop(OBJ_M_NO_ATTACK,
        "As you come at the captain, he makes a swift gesture, and"
      + " you stagger back, your muscles spasming out of control. You"
      + " lose your balance and sit down hard! As you get back to your"
      + " feet the captain smiles grimly at you and shakes his head"
      + " from side to side.\n");
    set_ticket(DOCK_DIR + "telberin/ticket");
    set_price(PRICE);

    add_telberin_asks();
    set_job_response("I am in charge of regular passage between"
      + " the City of Telberin and Ceral Isle.");

    arm_me();
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
                str = "Soon we will be on our way back to the"
                    + " fair city of Telberin and her docks.";
                break;
            case 1..3:
                str = "We are on our way to Telberin.";
                break;
            case 4:
                str = "Soon we will be on our way back to the"
                    + " many docks of Ceral Isle.";
                break;
            case 5..12:
                str = "We are on our way to Ceral Isle.";
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
