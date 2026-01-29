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
  add_adj(({"silver", "round"}));
  set_short("silver round token");
  set_long("This silvery token looks a bit like a coin, with a celtic cross "+
           "engraved on one side, and a swordsman figure on the other one.\n");
  add_prop(OBJ_I_WEIGHT, 25);
  add_prop(OBJ_I_VOLUME, 10);
  add_prop(OBJ_I_VALUE, 180); // silver
}

int
toss_coin (string str)
{
  if (!str || str != "coin" && str != "token")
    NF0("Toss what?\n");

  string result = random(2) ? "cross" : "swordsman";
  TP->catch_msg("You toss the token and catch it on the back of your palm. "+
                "It lands on the " + result + ".\n");
  tell_room(ENV(TP), QCTNAME(TP) + " tosses a strange grayish coin.\n", ({TP}));
  return 1;
}

void
init ()
{
  ::init();
  add_action(toss_coin, "toss");
}
