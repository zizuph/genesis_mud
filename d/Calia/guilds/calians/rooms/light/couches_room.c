/*
 * This room contains couches.
 *
 * Created by Glykron 05/27/00
 */

#pragma save_binary

#include <macros.h>
#include <composite.h>
#include "defs.h"
inherit "/std/room";

private object *couch_contents;

status
is_standing(object ob)
{
    return member_array(ob, couch_contents) == -1;
}

status
is_sitting(object ob)
{
    return member_array(ob, couch_contents) != -1;
}

int
can_leave()
{
    if (is_standing(TP))
	return 0;
    
    write
    (
        "You are still sitting!" +
        "\n"
    );
    return 1;
}

status
sit(string destination)
{
    if
    (
	destination == 0 ||
	destination == "on couch" ||
	destination == "on a couch"
    )
    {
        object tp;
	tp = TP;
	if (is_standing(tp))
	{
	    couch_contents += ({ tp });
            write
	    (
                "You sit down on a couch and relax." +
                "\n"
	    );
            say
	    (
                QCTNAME(tp) + " sits down on a couch and relaxes." +
                "\n"
	    );
	}
	else
	{
            write
	    (
                "You are already sitting down." +
                "\n"
	    );
	}
	return 1;
    }
    return 0;
}

status
stand(string destination)
{
    if
    (
	destination == 0 ||
	destination == "up"
    )
    {
        object tp;
	tp = TP;
	if (is_sitting(tp))
	{
	    couch_contents -= ({ tp });
            write
	    (
                "You stand up." +
                "\n"
	    );
            say
	    (
                QCTNAME(tp) + " stands up." +
                "\n"
	    );
	}
	else
	{
            write
	    (
                "You are already standing up." +
                "\n"
	    );
	}
	return 1;
    }
    return 0;
}

string
describe_couches()
{
    string description;
    object tp;
    status tp_is_sitting;
    description = "";
    tp = TP;
    tp_is_sitting = is_sitting(tp);
	
    description = "The couches here look very comfortable and "
        + "inviting.";
    if (tp_is_sitting)
    {        
        description += " You feel quite comfortable on the couches.";
        if (sizeof(couch_contents) == 1)
        {
            description +=  " You are the only one sitting on them "
                + "right now.";
        }
        else
        {
            description += " Besides yourself, you see "
                + COMPOSITE_LIVE(couch_contents - ({ tp }))
                + " sitting on them.";
        }
	}
	else
	{
        description += " You think that if you were to sit in the couches "
            + " you would feel very relaxed.";
        if (sizeof(couch_contents) > 0)
        {
            description += " You see " + COMPOSITE_LIVE(couch_contents) 
                + " sitting on them.";
    	}
    	else
    	{
    	    description += " No one is sitting on them.";
    	}
    }
    	
    description += "\n";
    	
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
        couch_contents -= ({ ob });
}

void
create_room()
{
    add_item("couch", "The couches can only be examined as a group.\n");
    add_item("couches", describe_couches);
    couch_contents = ({ });
}
