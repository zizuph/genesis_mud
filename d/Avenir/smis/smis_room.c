// file name:        /d/Avenir/smis/lib/smis_room.c
// creator(s):       Denis, Jul'96
// revision history: 
// purpose:          This room code to be used with smis - compatible objects.
//                   For info on what the hell smis is,
//		     use <cmdsoul /d/Avenir/smis/smiscmd>, <newhooks>.
/*
 * Revisions:
 *     Lucius, Jul 2017: Miscellaneous cleanups.
 *
 */
#pragma strict_types

#include <macros.h>
#include <filter_funs.h>

#include "smis.h"

inherit "/std/room";

public static int gSend_reset;
public static string gArea = "",
                    *gRemote_cmds = ({}),
                    *gLocation_roles = ({});

/*
 * Function name: set_area
 * Description:   Sets the object area identifier, which is at the same time
 *		  reference to the area manager.
 *		  Area manager is not neccessarily to exist.
 * Arguments:     area - The area id.
 * Returns:       void
 */
public void
set_area(string area)		{ gArea = area; }

/*
 * Function name: query_area
 * Description:   Returns the identifier to an area (which at the same time
 *		  is/should be smis reference to area manager).
 * Returns:       The area id.
 */
public string
query_area(void)		{ return gArea; }

/*
 * Function name: set_location_roles
 * Description:   Sets the role(s) of location.
 *                These roles are used by the smis modules to determine
 *		  what do to with the location.
 * Arguments:     role - string or array of string - the roles of the location.
 */
public void
set_location_roles(mixed role)
{
    if (stringp(role))
	gLocation_roles = ({ role });
    else if (pointerp(role))
	gLocation_roles = role;
}

/*
 * Function name: query_location_roles
 * Description:   Returns the role(s) of the location.
 * Returns:       The role(s) of the location.
 */
public string *
query_location_roles(void)	{ return gLocation_roles; }

/*
 * Function name: create_smis_room
 * Description:   To be overloaded by rooms code.
 */
public void
create_smis_room(void)
{
}

/*
 * Function name: create_room
 * Description:   
 * Arguments:     
 * Returns:       
 */
public nomask void
create_room(void)
{
    create_smis_room();

    gSend_reset = SMIS_MANAGER->object_created(
	this_object(), MASTER, gArea, gLocation_roles);

    if (!gSend_reset && !this_object()->query_reset_needed())
	disable_reset();
}

/*
 * Function name: reset_smis_room
 * Description:   To be overloaded by rooms code.
 */
public void
reset_smis_room(void)
{
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
public nomask void
reset_room(void)
{
    if (gSend_reset) SMIS_MANAGER->object_reset(
	this_object(), MASTER, gArea, gLocation_roles);

    reset_smis_room();
}

/*
 * Function name: transport_command
 * Description:   Relays the remote command to originating object.
 *		  Note: Function datatype is intentionally not used!!!
 * Arguments:     cmdobj - In which object to call function;
 *		  cmdfun - Which function to call there.
 * Returns:       what the remote command has returned.
 */
public int
transport_command(string cmdobj, string cmdfun, string str = 0)
{
    return call_other(cmdobj, cmdfun, str);
}

/*
 * Function name: init
 * Description:   Adds remote commands to player.
 */
public void
init(void)
{
    int i = -3, num = sizeof(gRemote_cmds);

    ::init();

    while((i = i + 3) < num)
    {
	add_action(&transport_command(gRemote_cmds[i + 1],
		gRemote_cmds[i + 2]), gRemote_cmds[i]);
    }
}

/*
 * Function name: add_remote_cmds
 * Description:   Adds remote commands, which will be available in this room.
 * Arguments:     cmd - The command,
 *		  cmdobj - In which object call function when player enters
 *			   the command cmd;
 *		  cmdfun - which function to call, when player enters cmd;
 */
public void
add_remote_cmds(string *value)
{
    gRemote_cmds += value;
    FILTER_LIVE(all_inventory())->update_actions(this_object());
}

/*
 * Function name: remove_remote_cmds
 * Description:   Removes the commands, which are set up by cmdobj
 *		  from the list.
 * Arguments:     
 */
public void
remove_remote_cmds(string cmdobj)
{
    int i = -3, num = sizeof(gRemote_cmds);

    while((i = i + 3) < num)
    {
	if (gRemote_cmds[i + 1] == cmdobj || !gRemote_cmds[i + 1])
	{
	    gRemote_cmds[i] = "_smis_room_removeit";
	    gRemote_cmds[i + 1] = "_smis_room_removeit";
	    gRemote_cmds[i + 2] = "_smis_room_removeit";
	}
    }
    gRemote_cmds = filter(gRemote_cmds, &operator(!=) ("_smis_room_removeit"));
    FILTER_LIVE(all_inventory())->update_actions(this_object());
}

/*
 * Function name: stat_object
 * Description:   Interface to 'stat' command.
 * Returns:       The statistics of room.
 */
public string
stat_object(void)
{
    string str = ::stat_object() +
"------------------------------------------------------------------------------\n" +
	"The room is subject to smis modules operation.\n" +
	"Reset notifications:\t" +
	(gSend_reset ? "yes" : "no") + "\n" +
	"Area id:\t\t" + gArea + "\n" +
	"Location role(s):\t\t";

    foreach(string role: gLocation_roles)
	str += role + "\t";

    str += "Remote cmds:\t\t";

    int i = -3;
    while ((i = i + 3) < sizeof(gRemote_cmds))
	str += gRemote_cmds[i] + "\t";

    return str + "\n";
}
