/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * goblin_brain.c
 *
 * modified by Sorgum 950707
 *
 *  Modified: 13 May 2003, by Bleys
 *      - Added a much needed long desc
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <stdproperties.h>
#include <macros.h>

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("brain");
    set_short("brain from a smart goblin");
    set_long("This rarity seems never to grow cold, but rather " +
        "emits a constant warmth in addition to an infrequent " +
        "pulse. It continuously drips with what seems to be a " +
        "never-ending supply of encephalic fluid.\n");

    add_prop(OBJ_I_VALUE,  0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}
