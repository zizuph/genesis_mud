/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Bog's drum
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
    set_name("drum");
    set_adj("bog's");
    set_short("Bog's drum");
    set_long("This drum is Bogs.  You should return it to him.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 300);
}
