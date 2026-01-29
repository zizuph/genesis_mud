/* -*- Mode: C -*-
 *
 * obj/leftover/g_claw.c
 *
 * By Skippern 20(c)04
 *
 * A claw leftover from the stone golem.
 */
inherit "/std/object";

#include "../../defs.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/* Global variables */

public void
create_object()
{
    set_name("claw");
    set_short("stone claw");
    set_long("This is a claw shaped stone. It seems to have been " +
	     "made with the aid of magic as its surface is completely "+
	     "smooth. A patterns looking like blood veins can be seen " +
	     "all over the surface.\n");
}

