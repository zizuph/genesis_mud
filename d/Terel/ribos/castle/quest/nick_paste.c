/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * nick_paste.c
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
    set_name("toothpaste");
    set_short("tube of toothpaste");
    set_long("This is a tube of toothpaste.  On the side, you " +
	     "see a familiar looking set of smiling teeth.  They " +
	     "can only be those of Nick, the ever-smiling wizard.  " +
	     "Now you know how he keeps those teeth so white.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 70);
}
