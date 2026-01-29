/* 
 * TESTFILE ONLY



 * Xak Tsaroth - Temple of Mishakal
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>

inherit INROOM;

object gDoor;

public void
create_xak_room()
{    
    set_short("In the entrance hall");
    set_long("@@my_long@@");
    
    gDoor = clone_object(OBJ + "d_courtyard");
    gDoor->move(TO);
    gDoor->set_key(K_TEMPLE);
}

public string
my_long()
{
    return "You are standing in an arching entrance hall of the temple of " +
           "Mishakal. It is a place of peace and it gives you a good " +
	   "feeling all over. You remember all the good times in your " +
	   "life and somehow you know that no matter what happens in " +
	   "your life things will always work out for the best in the " +
	   "end. On the west wall is a set of " + DOOR(gDoor) + " golden " +
	   "double doors, leading outside to the couryard. The hall " +
	   "leads to the east.\n";
}
 
public int
do_pick(string str)
{
    NF("Pick what?\n");
    if ((str == "lock") || (str == "the lock") || (str == "door lock"))
    {
        write("You try to pick the lock, but it is too complex for you.\n");
	SAY(" is messing with the door lock.");
	return 1;
    }
    return 0;
}

public int
do_knock(string str)
{
    NF("Knock where?\n");
    if ((str == "on the door") || (str == "on the doors")
	|| (str == " on the double doors") || (str == "door"))
    {
        write("You knock on the doors, the sound of your knocking " +
              "is swallowed up by the deathly silence of the city.....\n");
	SAY(" knocks on the door very loudly.");
	return 1;
    }
    return 0;
}

public void
init()
{
    ::init();
    add_action(do_pick, "pick");
    add_action(do_knock, "knock");
}









