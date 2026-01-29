/*
 * brew.c
 *
 * Used in nyreese/red_pub.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Made the description more flexible.
 * Tapakah, 07/2021
 */

/* gresolle 921113 */

#pragma strict_types

#include <stdproperties.h>

inherit "/std/drink";

object buyer = 0;

string
my_long ()
{
  if (environment() == buyer)
    return "As you look at the bottle, you really wonder " +
      "why you bought it.\n";
  else
    return "As you look at the bottle, you really wonder " +
      "why someone would buy it.\n";
}

void
create_drink ()
{
  set_soft_amount(540);       /* a pint */
  set_alco_amount(50);
  set_long(my_long);
  set_name("brew");
  set_adj("strange");
  add_name("bottle");
  add_adj("bottle");
  add_adj("brew");
  
  set_short("bottle of strange brew");
  set_pshort("bottles of strange brew");
  
  add_prop(OBJ_I_WEIGHT, 600);
  add_prop(OBJ_I_VOLUME, 600);
}

void
enter_env (object to, object from)
{
  ::enter_env(to, from);
  if (! buyer)
    buyer = to;
}
