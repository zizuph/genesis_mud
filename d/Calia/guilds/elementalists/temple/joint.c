/*
 * Joint Council Room for the Elemental Guilds of Calia
 *
 * Jaacar, January 2018
 */

#pragma strict_types

#include <stdproperties.h>
#include <files.h>
#include "defs.h"

inherit TEMPLE_ROOM_BASE;

public void load_board();

public int
query_prevent_snoop()
{
    return 1;
}

public void
create_temple_room()
{
    set_short("Joint Council Room");
    set_long("You are standing in the joint council room for the Elemental "
             + "Guilds of Calia. Located in the center of the room "
             + "is the joint Elementalists Council board. There are "
             + "two exits from here - the Worshippers council room and "
             + "the Clerics councilroom. The walls here "
             + "are carved out of a beautiful slab of a white and "
             + "black swirled marble that you have only seen in the common "
             + "room in the Temple.\n\n");
    
    try_item( ({ "wall", "walls", "marble", "slab", "beautiful slab",
                    "swirled marble", "black marble", "white marble" }),
        "You do wonder where this very special marble comes from that "
        + "adorns the wall. Most likely, it must have been brought from "
        + "far away since it doesn't match much of the rest of the "
        + "crystalline Temple.\n");

//    add_exit(ELEMENTALIST_TEMPLE + "worshipper_councilroom", "worshipper", "@@cannot_enter_worshippers", 1, "@@cannot_see_worshippers");
    add_exit(ELEMENTALIST_TEMPLE + "cleric_councilroom", "cleric", "@@cannot_enter_clerics", 1, "@@cannot_see_clerics");

    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_INSIDE,1);

    load_board();
}

public int
cannot_see_clerics()
{	    
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    if (GUILD_MANAGER->query_is_ec_council(TP, 1))
    	return 0;
    else
      	return 1;
}

public int
cannot_enter_clerics()
{
	if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    if (GUILD_MANAGER->query_is_ec_council(TP, 1))
    	return 0;
    
    // Non-council members cannot use these exits.
    write("As you attempt to enter, you feel a calming restraining "
          + "force preventing your movement.\n");
    return 1;
}

public int
cannot_see_worshippers()
{	    
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    if (GUILD_MANAGER->query_is_ew_council(TP))
    	return 0;
    else
      	return 1;
}

public int
cannot_enter_worshippers()
{
	if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    if (GUILD_MANAGER->query_is_ew_council(TP))
    	return 0;
    
    // Non-council members cannot use these exits.
    write("As you attempt to enter, you feel a calming restraining "
          + "force preventing your movement.\n");
    return 1;
}

public void
load_board()
{
    setuid();
    seteuid(getuid());

    clone_object(ELEMENTALIST_OBJS + "joint_board")->move(this_object());
}

/*
 * Function: enter_inv
 * Description: block unwanted people from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from && !living(ob) && IS_PLAYER_OBJECT(from))
    {
        // Player is attempting to drop something. We prevent this
        from->catch_msg("Something is preventing you from dropping "
                        + "this item.\n");
        ob->move(from);
        return;
    }

    // Otherwise, allow non-living objects to enter this room
    if (!living(ob)) 
    {
        return;
    }    
}

/*
 * Function:    no_drop
 * Description: Prevent members from using the Council Chambers
 *              as their own personal storage room.
 */
public int
no_drop(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    write("You cannot drop things in this room.\n");
    return 1;
}

public void 
init()
{
    ::init();

    add_action(no_drop,"drop");
    add_action(no_drop,"put");
}
