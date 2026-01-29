/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * prison_room.c
 *
 * A generic prison room.  Handle common actions that prisoners may try.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_giveup", "giveup");
    add_action("do_commune", "commune");
}

public int
do_commune(string str)
{
    write("You can't do that while you're in jail!  You can try to solve " +
	  "quest and escape from jail, or you can 'giveup'.  If you give " +
	  "you will be released from jail, but you forfeit your chance to " +
	  "solve the quest.\n");
    
    return 1;
}

public int
do_giveup(string str)
{
    /*
     * Set quest bit, and release the player from jail.
     */
    
    write("Wussy.\n" +
	  "Ok, you give up.  You get no xp, but you do get out of " +
	  "jail now...\n");

    return 1;
	
}
