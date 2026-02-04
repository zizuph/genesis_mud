/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * pocket_protector.c
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
    set_name("pocket protector");
    set_short("Tricky's pocket protector");
    set_long("This is a small, leather pouch that fits in the " +
	     "shirt pockets of most newly made cloaks.  They are " +
	     "made to protect the clothing of the wearer from ink " +
	     "stains.  This particular one once belonged to " +
	     "Tricky, before he cast a spell on his cloak to " +
	     "make it stain-resistant.\n");

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE,  0);
}
