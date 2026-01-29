/* File         : /d/Khalakhor/std/room.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 1st 1999
 * Purpose      : Khalakhor standard room, to be inherited by all domain rooms
 * Related Files: /std/room.c
 * Comments     :
 * Modifications:
 *   Added Wizard Tourist Logging code. - Tomas  June 2000
 *   Added room_tell (thanks Lucius!)  - Tomas  July 2000
 *   Stripped weather code - Teth December 2001
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Khalakhor/sys/properties.h"
#include <files.h>
#include <std.h>


inherit "/std/room";
inherit "/d/Khalakhor/std/room_tell";


#define W_LOG "/d/Khalakhor/log/wlog"
#define ENV(arg)   environment(arg)

// Global Vars
static mapping gNo_exit_msg = ([]);

/* Function name: create_khalakhor_room
 * Description  : The actual room constructor function
 */
void create_khalakhor_room() {}

/* Function name: create_room
 * Description  : The standard room constructor... we add our domain
 *                wide code in here and mask it so you can't overide
 *                anything placed in here.
 */
nomask void
create_room()
{
    set_terrain(TERRAIN_OUTSIDE | TERRAIN_NATURAL);
    remove_prop(ROOM_I_INSIDE);          /* Default room has heaven above */
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);  /* Default is a room */
    create_khalakhor_room();
}

/* Function name:  set_no_exit_msg
 * Description:    This function is used in your create_* function for
 *                 your room to set up alternate messages for when a
 *                 player attempts to go in a non-existant direction.
 * Arguments:      mixed dirs:  The directions we want to set the
 *                              non-standard message for.
 *                 string msg:  The message we want to print when a player
 *                              goes in one fo the dirs have it set for.
 */
public void
set_no_exit_msg(mixed dirs, string msg)
{
    int i;

    if (!pointerp(dirs))
    {
        if (dirs == "all")
        {
            dirs = ({"north", "northeast", "east", "southeast", "south",
              "southwest", "west", "northwest", "up", "down"});
        }
        else
            dirs = ({dirs});
    }
    i = -1;
    while (++i < sizeof(dirs))
        gNo_exit_msg[dirs[i]] = msg;

}

/* Function name:  unq_no_move (MASKED)
 * Description:    This function prints out the message when a player
 *                 attempts to use a non-existant exit.
 * Arguments:      string str:  The direction the player tried to go.
 * Returns:        A failure message and 0
 */
public int
unq_no_move(string str)
{
    string vb = query_verb();

    if (gNo_exit_msg[vb])
        notify_fail(gNo_exit_msg[vb] + "\n");
    else
        notify_fail("There is no obvious exit "+ vb +".\n");

    return 0;
}

public void
enter_inv(object ob, object from)
{
   string str,domain,where;
   mixed rank;

    ::enter_inv(ob,from);

    if (interactive(ob))
    {
       start_room_tells();
    }

    if (ob->query_wiz_level())
    {
      where = file_name(ENV(ob));
      rank = WIZ_N[SECURITY->query_wiz_rank(ob->query_real_name())];
      domain = SECURITY->query_wiz_dom(ob->query_real_name());
      str = ob->query_real_name();
      str = str + ", " + rank + ", " + domain + ", " + where;
if (domain != "Khalakhor")
        write_file(W_LOG, str + " (" + ctime(time()) + ")\n");
    }

}
