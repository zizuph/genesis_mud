/*
 * /d/Gondor/clubs/storytellers/obj/foyer_door_out.c
 */
inherit "/std/door";
#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <macros.h>

void
create_door()
{
    set_door_id("foyer_door");
    set_pass_command(({"n","north"}));
    set_door_name(({"green door","wooden door","door"}));
    set_other_room(STORYT_DIR + "rooms/foyer");
    set_door_desc("The green door is made of solid, polished wood.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_key(KEY_ID);
}

/*
 * Function name:       knock_door
 * Description  :       knock on the door
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 if we understand the arg, 0 if not
 */
int
knock_door(string arg)
{
    string      tmpstr;

    if ( !strlen(arg) )
    {
        notify_fail(capitalize(query_verb())+" on what?\n");
        return 0;
    }

    if ( sscanf(arg, "on %s", tmpstr) )
    {
        arg = tmpstr;
    }

    if (member_array(arg, door_name) < 0)
    {
        return 0;
    }

    if (!other_door)
    {
        load_other_door();
    }

    if (!open_status)
    {
        TP->catch_msg(knock_resp[0]);
        say(QCTNAME(this_player()) + " " + check_call(knock_resp[1]),
            this_player());
        if ( objectp(other_door) )
        {
             tell_room(environment(other_door), knock_resp[2]);
        }

        if (IS_STORYTELLER(this_player()) && lock_status)
        {
            tell_room(environment(this_object()), "You hear a faint 'click' "+
		"from the other side of the door.\n");
	    tell_room(other_room, "A storyteller walks up and peeks through "+
		"the peep hole. "+ (random(2) ? "He" : "She") + " unlocks the "+
		"door and moves along.\n");
	    do_unlock_door("");
	    other_door->do_unlock_door("");
        }
    }
    else
    {
        this_player()->catch_msg(knock_fail[0]);
        say(QCTNAME(this_player()) + " " + check_call(knock_fail[1]),
            this_player());
        if ( objectp(other_door) )
        {
             tell_room(environment(other_door), knock_fail[2]);
        }
    }
    return 1;
}

/*
int
pass_door(string arg)
{
    object	other;
    if (!TP->query_wiz_level() &&
	!sizeof(filter(all_inventory(TP),
		       &operator(==)("key_that_don't_exist") @ &->query_key())))
    {
	write("The door closes in your face!\n");
	say("The door closes.\n");
	do_close_door("");
	(other = query_other_door())->do_close_door("The door closes.\n");
	do_lock_door("");
	other->do_lock_door("");
	return 1;
    }
    return ::pass_door(arg);
}
*/
