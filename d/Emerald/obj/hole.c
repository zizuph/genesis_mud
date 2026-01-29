/*
 *  /d/Emerald/obj/hole.c
 *
 *  This is the hole which can be creating using the object:
 *
 *      /d/Emerald/obj/shovel.c
 *
 *  It is based on Olorin's:
 *
 *      /d/Gondor/common/obj/hole.c
 *
 *  but has been upated to current coding standards, and given
 *  a bit more refinement.
 *
 *  Copyright (c) March 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <language.h>

/* global variables */
public int         Size;
public int         Maxsize;
public string     *Snames;

/* prototypes */
public void        create_object();
public int         increase_size();
public string      my_short();
public string      my_long();
public void        setup_names();

public int         query_size() { return Size; }


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
  set_name("_hole_");
  add_name( ({ "hole", "trench", "pit" }) );
    add_adj( ({ "small", "large" }) );
  set_short(my_short);
  set_long(my_long);

  add_prop(OBJ_M_NO_GET,1);

  Size = 0;
  setup_names();
} /* create_object */


/*
 * Function name:        increase_size
 * Description  :        increase the size of the existing
 *                       hole
 * Returns      :        int - the value of Size
 */
public int
increase_size()
{
    if(Size < sizeof(Snames) -1)
    {
        Size++;
    }

    return Size;
} /* increase_size */


/*
 * Function name:        my_short
 * Description  :        determines the current short description
 *                       for the hole
 * Returns      :        string - the short description
 */
public string
my_short()
{
    return Snames[Size] + " in the ground";
} /* my_short */


/*
 * Function name:        my_long
 * Description  :        determines teh current long description for
 *                       the hole
 * Returns      :        string - the long description
 */
public string
my_long()
{
    return capitalize(LANG_ADDART(Snames[Size])) + " has been dug into"
      + " the ground here.\n";
} /* my_long */



/*
 * Function name:        setup_names
 * Description  :        set the value of Snames
 */
public void
setup_names()
{
    Snames = ({
    "small hole",
    "hole",
    "big hole",
    "small trench",
    "trench",
    "deep trench",
    "small pit",
    "pit",
    "large pit",
    });
} /* setup_names */
