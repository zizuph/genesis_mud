/* By Korat
 * Nov. 1996
 * Fysix, Dec 1997, revised lift code
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"
#include "lift.h"

void
create_monster()
{
    ::create_monster();
    set_name("winchman");
    set_adj("broad-shouldered");
    set_race_name("human");
    set_long("A broad-shouldered man who has the job of "+
      "winching the basket up and down the cliffside.\n");
    set_stats(({130,50,50,40,40,50}));
    set_alignment(400);
    set_knight_prestige(-10);
    set_act_time(20);
    add_act("emote wipes the sweat off of his brow.");
    add_act("emote leans against the wheel of the winch.");
    add_act("say Hard work, this.");
    //add_prop(NPC_M_NO_ACCEPT_GIVE,1);
    add_prop(OBJ_M_NO_ATTACK,"Who would do the winching then?\n");

    add_ask(({"basket","lift","down","winch","lower","lower me down"}),
      VBFC_ME("winch"));
    add_speak("I can lower you down in the basket. Just ask me.\n");
}

string
winch()
{
    string str;

    switch (LIFT->query_lift_status())
    {
    case MOVING_DOWN:
	str = "say Hold on to yah hat man! I'm lowering "+
	"someone down right now.";
	break;
    case MOVING_UP:
	str = "say Relax stranger. It will soon be here.";
	break;
    case LIFT_RESTING:
	str = "say Gimme a chance to rest will ya!?  Jeez..";
	break;
    }

    if (str)
    {
	command(str);
	command("emote goes back to his work.");
	return "";
    }

    switch(LIFT->query_lift_location())
    {
    case AT_TOP:
	command("say Are yah blind? The basket is here and ready.");
	command("sigh");
	command("say Just climb into it, and pull the rope when "+
	  "you want me to lower you down.");
	break;
    case AT_BOTTOM:
	command("say Alright.. lemme get this sucker moving!");
	command("emote busies himself at the lift.");
	LIFT->move_lift();
	break;
    }

    return "";
}

