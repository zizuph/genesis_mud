/* Basic NPC file
 * May be moved elsewhere to make more common
 * Tapakah, 04/2021
 */

inherit "/d/Khalakhor/lib/knowledge_base";
inherit "/d/Khalakhor/std/npc/help-me";

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
