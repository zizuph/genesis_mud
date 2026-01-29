/*
 * Captain's token
 * Tapakah, 09/2021
 */

#pragma strict_types;

#include "macros.h"
#include "stdproperties.h"

#include "../defs.h"

inherit "/std/object";

void
create_object ()
{
  set_name("token");
  add_adj(({"golden", "round"}));
  set_short("golden round token");
  set_long("This golden token looks a bit like a large coin, with a celtic "+
           "cross engraved on one side, and a commanding figure on the "+
           "other one.\n");
  add_prop(OBJ_I_WEIGHT, 25);
  add_prop(OBJ_I_VOLUME, 10);
  add_prop(OBJ_I_VALUE, 1000); // gold
}

int
toss_coin (string str)
{
  if (!str || str != "coin" && str != "token")
    NF0("Toss what?\n");

  string result = random(2) ? "cross" : "figure";
  TP->catch_msg("You toss the token and catch it on the back of your palm. "+
                "It lands on the " + result + ".\n");
  tell_room(ENV(TP), QCTNAME(TP) + " tosses a strange yellowish coin.\n", ({TP}));
  return 1;
}

void
init ()
{
  ::init();
  add_action(toss_coin, "toss");
}
