/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * deerskin.c
 *
 * Janus 920701
 * modified by Sorgum 941002
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
    set_name(({"pelt", "deer pelt"}));
    set_adj("deer");
    set_long("The pelt from the deer looks like it is of good quality, " +
	     "maybe a tanner could use it.\n");
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,2000);  
    add_prop(OBJ_I_VALUE, 500);
}

