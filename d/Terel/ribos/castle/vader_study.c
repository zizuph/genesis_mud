/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * vader_study.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

public int do_read(string str);

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "obj/wand"});
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Study");
    set_long("A small room, with books scattered throughout.  " +
	     "A hand-woven rug sits upon the floor underneath " +
	     "a table.  Atop the table is a bottle of ink, " +
	     "and a few quills.  A book rests open atop the table.  " +
	     "In one corner is a small chest.  Light fills the room " +
	     "from some strange rock that hangs from the ceiling.\n");

    add_item(({"rock", "strange rock"}), 
	     "This rock gives off a glow.  Otherwise, it is featureless.\n");

    add_item(({"rug", "hand-woven rug"}), 
	     "This rug looks as if it came from a hobbit weaver.\n");

    add_item(({"table"}), "Just a simple table.\n");

    add_item(({"book"}),
	     "This book is open, and is hand-written in ink.  It is " +
	     "not complete yet.\n");

    add_item(({"ink", "quills"}), "You see nothing special about this.\n");

    INSIDE;

    add_exit(CASTLE_DIR + "vader_ent", "west", 0);

    reset_room();
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
   ::init();
   add_action(do_read,  "read");
}

/*
 * Function name: do_read
 * Description:   Handle the read action
 * Returns:       1/0
 */
public int
do_read(string str)
{
    if (!strlen(str) || (str != "book")) {
	NF("Read what?\n");
	return 0;
    }

    write("This particular wand has been quite troublesome to make work.  " +
	  "It demands *so* much power that I can only fit one charge in " +
	  "the wand.  This makes it very impractical, but I am working " +
	  "on that.  I have also had trouble with the spell it emits.  " +
	  "It has worked fine altering the hand, but it does not alter " +
	  "whatever the hand touches.  If you cannot get the object " +
	  "out of the box, then this wand is useless.  I *think* I have " +
	  "figured it out, though.  If this wand works, the King would " +
	  "be able to retrieve the scroll from the evil King Yelit.  I " +
	  "will test it tomorrow, as I have much to do today.\n");

    return 1;
}
 
