/*
 * Base SaMorgan villager
 * Tapakah, 05/2021
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit KSTDELF;

string *equipment = ({});

void
equip_me ()
{
  object ob_item;
  foreach (string item: equipment) {
    ob_item = clone_object(item);
    ob_item->move(TO);
  }
  command("wear all");
  add_prop(LIVE_M_NO_ACCEPT_GIVE, 0);
}

varargs void
return_item (object ob, object from, string message="I don't need this.")
{
  string whom = OB_NAME(from), what = OB_NAME(ob);
	
  if (present(from, environment()) && from->check_seen(this_object())) {
    command("say " + message);
    if (command("give " + what + " to "+ whom) == 0)
      command("drop " + what);
  }
  else {
    command("say What am I supposed to do with this?");
    command("drop "+ what);
  }
}

void
receive_item (object ob, object from)
{
  return_item(ob, from);
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!objectp(ob) || !objectp(from))
    return;
  set_alarm(1.0, 0.0, &receive_item(ob, from));
}
