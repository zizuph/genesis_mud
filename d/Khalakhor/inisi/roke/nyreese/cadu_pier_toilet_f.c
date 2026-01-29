/*
 * The actual female lavatory on Cadu pier
 * Adapted from Gelan lavatory code
 * Tapakah, 04/2009
 */

#pragma save_binary

inherit "/d/Calia/std/lav";
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <const.h>

void
create_room()
{
    make_the_room(NYREESEDIR + "cadu_pier_toilet", 
                  CADU_DOORS + "lavatory_female",
                  CADU_DATA  + "lf", G_FEMALE);
} 
