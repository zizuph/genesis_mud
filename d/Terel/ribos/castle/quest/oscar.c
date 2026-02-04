/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * oscar
 *
 * Vader
 * modified by Sorgum 950707
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
    set_name("statuette");
    set_short("statuette of Oscar");
    set_long("This is a small statuette of Oscar.  Oscar is quite famous " +
	     "around here.  Everyone seems to like to announce to their " +
	     "friends the exact time that he showed up.  Oscar is quite a " +
	     "guy.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE,  10);
}
