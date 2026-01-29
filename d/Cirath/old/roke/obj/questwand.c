/*
 * questwand.c
 *
 * Used in npc/transformer.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

string
query_recover()
{
  return MASTER;
}

void
create_object()
{
  set_name("wand");
  add_name("gemejminexpe");
  set_adj("magic");
  set_short("magic wand");
  set_long("This is a Wand of Destruction.\n");
  
  add_prop(OBJ_I_WEIGHT,100);
  add_prop(OBJ_I_VOLUME,100);
}
