inherit "/std/object";
#include <stdproperties.h>
/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * book.c
 *
 * Vader
 * modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
#include <cmdparse.h>

inherit STDOBJECT;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("letter");
    add_name("ribos_letter");
    set_adj("unmailed");
    set_long("Dear Mystics:\n" +
	     "In regards to the ancient evil I informed you " +
	     "of earlier, we have come into a bit of luck.  Although it " +
	     "did manage to destroy a few houses, some of my bravest " +
	     "metalworkers followed it as it returned to its nest for a " +
	     "nap.  As it slumbered rather heavily, they constructed " +
	     "a large wall of iron.  Although it will hold him, " +
	     "it will not hold him forever.  I'm afraid we may still " +
	     "need any magicians you can spare.  Of course, anyone " +
	     "coming to the aid of the Kingdom will be well " +
	     "rewarded......if we survive.\n\nKing Bor-El\n");
    
   add_prop(OBJ_I_VALUE,  1);
   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VOLUME, 1);
}

