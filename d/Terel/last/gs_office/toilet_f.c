/*
 * The actual female lavatory on Last pier
 * Adapted from Gelan lavatory code
 * Tapakah, 04/2009
 */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <const.h>
#include "gs_office.h"

inherit "/d/Calia/std/lav";


void
create_room()
{
  make_the_room(ENTRANCE, DOOR_F_OUT, DATA_F, G_FEMALE);
} 

