/*
 *  /d/Sparkle/area/tutorial/lib/lib_sign.c
 * 
 *  This module adds functionality for placing an object into
 *  the room from which a chapter of the tutorial can be read.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

/* Prototypes */
public void        add_sign(int chapter, string name = "sign");


/*
 * Function name:        add_sign
 * Description  :        add and a configure a tutorial sign for the room
 * Arguments    :        int chapter - the chapter number for the sign
 *                       string name - the name of the object. Default
 *                                     is "sign".
 */
public void
add_sign(int chapter, string name = "sign")
{
    object   sign;

    if (!present("_tutorial_sign"))
    {
        sign = clone_object(OBJ_DIR + "sign");
        sign->config_sign(name);
        sign->set_chapter(chapter);
        sign->move(this_object());
    }

    return;
} /* add_sign */
