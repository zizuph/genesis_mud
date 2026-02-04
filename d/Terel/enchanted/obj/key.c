/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * key.c
 *
 * A coffin key
 */

#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;

#include "/d/Terel/include/recover.h"

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("key");
    set_short("large iron key");
    set_long("It's a large iron key.\n");
    set_adj(({"large", "iron"}));
    add_prop(OBJ_I_VALUE,  20);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 100);
}
