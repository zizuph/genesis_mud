/* Basic NPC file
 * May be moved elsewhere to make more common
 * Tapakah, 04-05/2021
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include "../defs.h"

inherit KSTDELF;
inherit "/d/Khalakhor/lib/knowledge_base";
inherit "/d/Khalakhor/std/npc/help-me";

string *equipment = ({});


public void
notify_others_of_attack(object who)
{
  ::notify_others_of_attack(who, "_sa_morgan_guard");                            
}

public void
add_introduced(string who)
{
  kb_add_introduced(who);
}

public void
init_living()
{
  ::init_living();
  kb_init_living();
}

public void
enter_env(object to, object from)
{
  ::enter_env(to, from);
  kb_enter_env(to, from);
}

public void
equip_me ()
{
  object ob_item;
  foreach (string item: equipment) {
    ob_item = clone_object(item);
    ob_item->move(TO);
    ob_item->wear_me();
  }
}

varargs public void
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

public void
receive_item (object ob, object from, string ob_name)
{
  return_item(ob, from);
}

public void
enter_inv(object ob, object from)
{
  string ob_name = ob->query_name();
  ::enter_inv(ob, from);
	
  if (!objectp(ob) || !objectp(from))
    return;

  set_alarm(1.0, 0.0, &receive_item(ob, from, ob_name));
}
