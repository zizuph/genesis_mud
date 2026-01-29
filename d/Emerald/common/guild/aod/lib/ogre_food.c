/*
 *  /d/Emerald/common/guild/aod/lib/ogre_food.c
 *
 *  This module sets up some common aspects for the items sold in the
 *  Army of Darkness mess hall.
 *
 *  Copyright (c) October 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        add_ogre_food_props();
public string      not_ogre_food_hook();
public mixed       check_ogre();

/*
 * Function name:        add_ogre_food_props
 * Description  :        set up some of the aspects of Ogre food that
 *                       we want to be common to all items
 */
public void
add_ogre_food_props()
{
    this_object()->add_prop(OBJ_I_NO_GET, "@@check_ogre@@");
} /* add_ogre_food_props */


/*
 * Function name:        not_ogre_food_hook
 * Description  :        the fail message when the character is not an
 *                       Ogre and tries to consume this food/drink
 * Returns      :        string - the fail message
 */
public string
not_ogre_food_hook()
{
    return "The " + this_object()->short() + " is too big for you to"
      + " lift, let alone put in your mouth! Clearly, this is meant to be"
      + " consumed by some sort of giant.\n";
} /* not_ogre_food_hook */


/*
 * Function name:        check_ogre
 * Description  :        Check to see if this is an ogre or not.
 *                       If it isn't an ogre, they can't lift it.
 * Returns      :        mixed: 0 - let them get it
 *                            : string - fail message
 */
public mixed
check_ogre()
{
    if (IS_OGRE(this_player()))
    {
        return 0;
    }

    return "It is too big for you to lift! This is clearly meant for"
      + " some kind of giant.\n";
} /* check_ogre */
