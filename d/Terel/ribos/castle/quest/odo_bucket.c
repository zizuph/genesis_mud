/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * norm_tab.c
 *
 * Vader
 * modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
inherit "/std/container";

public void
create_container()
{
    set_name("bucket");
    set_adj("Odo's");
    set_short("Odo's bucket");
    set_long("This is Odo's bucket.  Odo lived here, but it was swiped " +
	     "and somehow wound up here, where the King found it.\n");

    add_prop(CONT_I_WEIGHT,     250); 	
    add_prop(CONT_I_MAX_WEIGHT, 2250); 	
    add_prop(CONT_I_VOLUME,     30); 	
    add_prop(CONT_I_MAX_VOLUME, 2030); 	
    add_prop(OBJ_I_VALUE,       10);
}
