/*
 * skin.c
 *
 * Used in several monsters
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Fixed the object not being a leftover
 * Tapakah, 07/2021
 */

#pragma save_binary
#pragma strict_types

inherit "/std/leftover";

#include "defs.h"
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>

void
leftover_init (string organ, string race)
{
  set_name(organ);
  set_short(organ);
  set_adj(race);
  set_long("This is a " + organ + " from " + LANG_ADDART(race) + ".\n");
  
  add_prop(OBJ_I_WEIGHT, previous_object()->query_prop(OBJ_I_WEIGHT) / 50);
  add_prop(OBJ_I_VOLUME, previous_object()->query_prop(OBJ_I_VOLUME) / 1000);
  
}

/*void
decay_fun ()
{
  tell_room(ENV(TO), "The " + name() +
            " decays and leaves nothing behind.\n");
  remove_object();
  }*/

