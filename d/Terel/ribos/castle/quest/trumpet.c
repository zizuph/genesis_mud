/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * trumpet.c
 *
 * Vader
 * modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
#include <cmdparse.h>

inherit STDOBJECT;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("trumpet");
    set_short("golden trumpet");
    set_adj("golden");
    set_long("A beautiful golden trumpet.  The King wanted to learn how " +
	     "to play, but gave it up after a number of years.  Maybe you " +
	     "could play it.\n");

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE,  500);
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("play", "play");
}

/*
 * Function name: do_play
 * Description:   Handle the play action
 * Returns:       1/0
 */
public int
play(string str)
{
    object *ob;

    NF("play what?\n");
    if (!sizeof(ob = FIND_STR_IN_OBJECT(str, TP)) || (ob[0] != TO))
	return 0;

    write("You play a beautiful melody, and suddenly the world seems to " +
	  "fall\ninto place.\n");

    say(QCTNAME(TP) + " plays a beautiful melody.  All the " +
	"worlds problems seem gone now.\n");

    return 1;
}


