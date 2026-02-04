/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * foxskin.c
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
    set_name(({"pelt", "fox pelt"}));
    set_adj(({"red", "gray"}));
    set_long("The pelt from the fox looks like it is of good quality,\n"+
             "maybe a tanner could use it.\n");
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
}

