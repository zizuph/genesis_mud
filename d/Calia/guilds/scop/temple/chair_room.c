/*
 * This code is inherited into the Spirit Circle's library.
 * It simulates the chair that is given in the room's description.
 *
 * Created by Quintas  06/16/03
 *
 * Thank you to Glykron.  This is adapted code 
 * from couches_room.c
 *
 */

#pragma save_binary

#include <macros.h>
#include <composite.h>
#include "defs.h"
inherit "/std/room";

private object *chair_contents;

status
is_standing(object ob)
{
    return member_array(ob, chair_contents) == -1;
}

status
is_sitting(object ob)
{
    return member_array(ob, chair_contents) != -1;
}

int
can_leave()
{
    if (is_standing(TP))
    {
        return 0;
    }

    if (this_player()->query_prop("_is_writing"))
    {
        write("You are still busy writing your book!\n");
        return 1;
    }
    write("You are still sitting!\n");
    return 1;
}

status
sit(string destination)
{
    if (sizeof(chair_contents) > 0)
    {
        write("There is already someone sitting in the only chair. " +
              "Please wait your turn.\n");
        return 1;
    }

    if(destination == 0 || destination == "in chair" ||
       destination == "in the chair" || destination == "at desk" ||
       destination == "at the desk" || destination == "on the chair" ||
       destination == "on chair" || destination == "down")
    {
        object tp;
	tp = TP;
	if (is_standing(tp))
	{
	    chair_contents = ({ tp });
            write("You sit down in the chair and prepare to write your book.\n");
            say(QCTNAME(tp) + " sits down in the chair and grabs a piece of " +
                "parchment and a quill.\n");
            tp->add_prop("_is_sitting", 1);
	}
	else
	{
            write("You are already sitting down.\n");
	}
	return 1;
    }
    return 0;
}

status
stand(string destination)
{
    if (this_player()->query_prop("_is_writing"))
    {
        write("You are too busy writing a book to stand up.\n");
        return 1;
    }

    if (destination == 0 || destination == "up")
    {
        object tp;
	tp = TP;
	if (is_sitting(tp))
	{
	    chair_contents -= ({ tp });
            write("You stand up.\n");
            say(QCTNAME(tp) + " stands up.\n");
            tp->remove_prop("_is_sitting");
	}
	else
	{
            write("You are already standing up.\n");
	}
	return 1;
    }
    return 0;
}

string
describe_chair()
{
    string description, tmp;
    object tp;
    status tp_is_sitting;
    description = "";
    tmp = "";
    tp = TP;
    tp_is_sitting = is_sitting(tp);
    if (tp_is_sitting)
	chair_contents -= ({ tp });
    if (sizeof(chair_contents) > 0)
    {
        description += "You see " + COMPOSITE_LIVE(chair_contents) +
	               " sitting in it.";
        set_long(long + "You see " + COMPOSITE_LIVE(chair_contents) +
	               " sitting in the only chair at the desk.");
    }    
    description += "\n";
    tmp += description;
    description = "A comfortable looking chair to sit in while writing " +
             "your book.";
    description += tmp;
    if (tp_is_sitting)
	chair_contents += ({ tp });
    return description;
}

void
init()
{
    ::init();
    add_action(sit, "sit");
    add_action(stand, "stand");
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (is_sitting(ob))
        chair_contents -= ({ ob });
}

void
create_room()
{
    add_item("chair", describe_chair);
    chair_contents = ({ });
}
