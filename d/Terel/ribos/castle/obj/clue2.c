/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * clue2.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("scroll");
    set_adj("unfinished");
    set_long("This is a scroll.  It has the following written upon it.  " +
	     "Dear King Prockyer;  The mission is uncertain.  There are " +
	     "still a few obstacles I have to overcome here at King " +
	     "Bor-El's castle, but I should be able to remove them " +
	     "before my welcome is worn out.  I will then travel to .....\n" +
	     "The letter ends, unfinished.\n");
    
    add_prop(OBJ_I_VALUE,  1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}
