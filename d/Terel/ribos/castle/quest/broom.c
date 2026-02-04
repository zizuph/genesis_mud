/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Hillary's broom
 *
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
    set_name("broom");
    set_short("Hillary's broom");
    set_long("This is the broom that the Calathin Mayors wife, " +
	     "Hillary Rodham Archibus, once used to fly around on.  " +
	     "She stopped using it when she was crushed by a house.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE,  10);
}
