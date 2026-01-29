/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
public void
create_object()
{
    set_name("ticket");
    add_name("the Terel-elven line");
    add_adj("torn");
    set_long("It looks like a ticket to some ship.\n");
    add_prop(OBJ_I_VALUE, 30);
}
