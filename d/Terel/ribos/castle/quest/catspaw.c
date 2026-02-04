/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Queen Alexia's cat's paw
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
    set_name("paw");
    set_short("Queen Alexia's cats' paw");
    set_adj("cats");
    set_long("This is the paw of Queen Alexia's prized cat, Bootsie.  " +
	     "It was given to the King for good luck after the cat died " +
	     "of old age.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 33);
}
