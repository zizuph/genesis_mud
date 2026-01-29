/*
 *  /d/Sparkle/area/orc_temple/obj/reagent.c
 *
 *  This is the reagent(s) that will fuel the enchanters forge in the
 *  quest of the Enchanter's Saga.
 *
 *  Created December 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>


/* prototypes */
public void        create_object();
public void        configure_reagent(string r_type);


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    add_prop(OBJ_M_NO_GIVE, "You'd better hang on to that.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to that.\n");

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        configure_reagent
 * Description  :        Set up the reagent - called upon cloning.
 * Arguments    :        string r_type - the reagent type
 */
public void
configure_reagent(string r_type)
{
    set_name(r_type);
    add_name( ({ "sample" }) );
    set_short("sample of " + r_type);

    set_long("You have collected this sample of " + r_type + " from the"
      + " stores of the High Priest. Perhaps you know what to do with"
      + " it?\n");
} /* configure_reagent */