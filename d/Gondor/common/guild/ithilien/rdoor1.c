/*
 * /d/Gondor/common/guild/ithilien/rdoor1.c
 *
 * The outside door for the council room.
 *
 * Modifications:
 * 13 Oct 98, Gnadnar:	conform to coding standards
 */

#pragma save_binary

inherit "/std/door";
#include "/d/Gondor/defs.h"

/* prototypes */
public void	create_door();
public int	open_door(string arg);
public int	close_door(string arg);


/*
 * Function name:	create_door
 * Description	:	set up the door
 */
public void
create_door()
{
    ::create_door();
    set_door_id("councildoor");
    set_pass_command( ({ "s", "south" }) );
    set_door_name( ({ "dark narrow door", "door" }) );
    set_other_room(RANGER_ITH_DIR + "ithilien_council");
    set_door_desc(BSN("The door is made of solid oak, massive and "+
	"dark with age. 'The Council of Rangers' is carved "+
	"on its center panel in deeply incised letters."));
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_key("council_key");
    set_knock_command("knock");
    set_open(0);
    set_locked(1);
} /* create_door */


/*
 * Function name:	open_door
 * Description	:	mask parent so they unlock before opening
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
open_door(string arg)
{
    if (query_locked())
    {
	if (!(unlock_door(arg + " with _council_key")))
	{
	    return 0;
	}
	write("You decide to unlock the door before opening it.\n");
    }
    return ::open_door(arg);
} /* open_door */


/*
 * Function name:	close_door
 * Description	:	mask parent so they lock after closing
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
close_door(string arg)
{
    if (!::close_door(arg))
    {
	return 0;
    }
    write("After you close the door, you decide to lock it as well.\n");
    return lock_door(arg + " with _council_key");
} /* close_door */
