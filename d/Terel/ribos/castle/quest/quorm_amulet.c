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
    set_name("amulet");
    set_short("amulet of Quorm Shelbey");
    set_adj("silver");
    set_long("An amulet of rare beauty and complexity, it is silver in " +
	     "color and covered with imprints of fine gothic designs.  " +
	     "Inscribed around the perimeter are words so old, you cannot " +
	     "possibly translate it.  You do, however, recognize the name..." +
	     ".....Quorm Shelbey.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 33);
}
