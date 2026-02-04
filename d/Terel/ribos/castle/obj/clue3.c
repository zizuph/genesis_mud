/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * clue3.c
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
    set_name("map");
    set_adj("raggedy");
    set_long("This appears to be a map of the Northern parts of Calathin.\n" +
	     "You are uncertain what the treasure is, though.\n  " +
	     "Unfortunatly, it is written in ancient runes and symbols, " +
	     "and you cannot read its details.  You can only tell that " +
	     "X marks the spot somewhere in Calathin's forest.\n");

    add_prop(OBJ_I_VALUE,  1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}
