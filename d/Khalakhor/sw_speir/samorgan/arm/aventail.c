/**********************************************************************
 * - aventail.c                                                         - *
 * - worn by the lieutenant                                         - *
 * - created by Tapakah, 5/2021                                     - *
 **********************************************************************/

#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

inherit SM_ARMOUR;

public nomask mixed
wear (object ob)
{
  object helmet = TP->query_armour(TS_HEAD);
  if (! helmet)
    return "You need to wear a helmet or something to attach " +
      "this aventail to.\n";
	TP->catch_msg("You attach the aventail to your " +
                helmet->query_name() + ".\n");
  return 1;
}

void
create_armour()
{
  set_name("aventail");
  add_name("helm");
  add_name("helmet");
  set_adj(({"steel","chain"}));
  set_short("steel chain aventail");
  set_long("This aventail is a piece of armour that is attached to a " +
           "helmet covers your chin, your neck and most of your chest. "+
           "It's made from a fine metal mesh, but still is a bit heavy.\n");
  set_ac(15);
  set_looseness(3);
  set_at(A_NECK|A_CHEST);
  set_am(({1, -2, 1}));
  set_af(TO);
  add_prop(OBJ_I_WEIGHT, 4500);
}
