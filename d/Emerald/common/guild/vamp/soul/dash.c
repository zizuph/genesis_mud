
/* dash.c created by Shiva@Genesis
 * This file contains the code for the "dash" command
 * This file is a subpart of the vampire guild shadow
 */

/* Description
 * -----------
 * This command allows a vampire to leave a room with such
 * speed as to seem invisible.  This is achieved by giving
 * the player 99 levels of OBJ_I_INVIS for a moment while
 * he/she exits a room.  Note that this shouldn't be considered
 * true invisibility and should not be counteracted by
 * LIVE_I_SEE_INVIS.  This is why a very high level of 
 * OBJ_I_INVIS is used. When a vampire dashes, no tracks
 * are left behind (i.e. * he/she has the LIVE_I_NO_FOOTPRINTS
 *  prop).
 */

#include "../guild.h"
#include "abilities.h"
#include <stdproperties.h>
#include <std.h>

static int dash2(string str);

static mixed
dash(string arg)
{
    string tmp;
  
    if (!strlen(arg))
    {
        notify_fail("Dash where?\n");
        return CMD_SYNTAX_FAILURE;
    }
  
    if (!CAN_SEE_IN_ROOM(this_player()))
    {
    	notify_fail("Your path is too dark to see.\n");
    	return CMD_SYNTAX_FAILURE;
    }
  
    if (strlen(tmp = SECURITY->modify_command(arg, environment(this_player()))))
    {
        arg = tmp;
    }
  
    if (member_array(arg, environment(this_player())->query_exit_cmds()) < 0)
    {
        notify_fail("Dash where?\n");
        return CMD_SYNTAX_FAILURE;
    }
  
    if (!levels_test())
    {
        return CMD_FAIL_WITHOUT_COST;
    }
  
    if ((this_player()->query_encumberance_weight() > 75) ||
	(this_player()->query_encumberance_volume() > 75))
    {
    	write("You are too encumbered.\n");
    	return CMD_FAIL_WITHOUT_COST;
    }
  
    if (!success_test())
    {
        return CMD_FAIL_WITH_COST;
    }
  
    return &dash2(arg);
}

int f(object ob)
{
    return (!IS_WIZ(ob) && IS_MEMBER(ob) && CAN_SEE_IN_ROOM(ob) &&
        CAN_SEE(ob, this_player()));
}

static int
dash2(string str)
{
    int footprints;
    object *team_present;
    string msgin, msgout;
  
    if (!(footprints = QP(this_player(), LIVE_I_NO_FOOTPRINTS)))
    {
        AP(this_player(), LIVE_I_NO_FOOTPRINTS, 1);
    }
  
    msgout = " disappears in a flash.\n";
  
    if (this_player()->query_invis())
    {
	say(({ "(" + METNAME + ")" + msgout,
	     ART_NONMETNAME + msgout,
	     "" }));
    }
    else
    {
	say(({ METNAME + msgout,
	     ART_NONMETNAME  + msgout,
	     "" }));
    }
  
    filter(all_inventory(environment(this_player())) - ({ this_player() }),
        f)->catch_msg("With your keen perception, you " +
        "notice that " + QTNAME(this_player()) + " left " + str + ".\n");
  
    CP(this_player(), OBJ_I_INVIS, 99);
  
    team_present = this_player()->query_team() &
        all_inventory(environment(this_player()));
  
  // Temporarily remove anyone whom we are leading in a team
    map(team_present, &(this_player())->team_leave());
  
  // Execute the exit command
    this_player()->command(str);
  
    CP(this_player(), OBJ_I_INVIS, -99);
  
    msgin = " dashes in.\n";
  
    if (this_player()->query_invis())
    {
        say(({ "(" + METNAME + ")" + msgin, ART_NONMETNAME + msgin, "" }));
    }
    else
    {
        say(({ METNAME + msgin, ART_NONMETNAME + msgin, "" }));
    }
  
    if (!footprints)
    {
        RP(this_player(), LIVE_I_NO_FOOTPRINTS);
    }
  
  // Add team members again
    map(team_present, &(this_player())->team_join());
    return 1;
}

