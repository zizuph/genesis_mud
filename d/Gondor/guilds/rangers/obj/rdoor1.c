/*
 * /d/Gondor/common/guild/ithilien/rdoor1.c
 *
 * The outside door for the council room.
 *
 * Modifications:
 * 13 Oct 98, Gnadnar: conform to coding standards
 * 21 Jul 01, Alto: change inheritances to fit new rangers theme
 */
inherit "/std/door";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

/* prototypes */
public void create_door();
public int  open_door(string arg);
public int  close_door(string arg);


/*
 * Function name: create_door
 * Description  : set up the door
 */
public void
create_door()
{
    set_door_id("councildoor");
    set_pass_command( ({ "s", "south" }) );
    set_door_name( ({ "dark narrow door", "door" }) );
    set_other_room(RANGERS_ITH_DIR + "ithilien_council");
    set_door_desc("The door is made of solid oak, massive and " +
        "dark with age. 'The Council of Rangers' is carved " +
        "on its center panel in deeply incised letters.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_key("Council_Key");
    set_knock_command("knock");
    set_open(0);
    set_locked(1);
}

/*
 * Function name: open_door
 * Description  : mask parent so they unlock before opening
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 on success, 0 on failure
 */
public int
open_door(string arg)
{
    if (query_locked())
    {
        if (!(unlock_door(arg + " with gold key")))
            return 0;

        write("You decide to unlock the door before opening it.\n");
    }

    return ::open_door(arg);
}


/*
 * Function name: close_door
 * Description  : mask parent so they lock after closing
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 on success, 0 on failure
 */
public int
close_door(string arg)
{
    if (!::close_door(arg))
        return 0;

    write("After you close the door, you decide to lock it as well.\n");
    return lock_door(arg + " with gold key");
}
