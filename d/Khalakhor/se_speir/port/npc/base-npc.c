/*
 * Base Port Macdunn NPC
 * Refactoring and normalizing things
 * Tapakah, 07/2021
 */

#pragma no_clone
#pragma strict_types

#include <filepath.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "npc.h"

inherit STDHUMAN;

inherit "/d/Khalakhor/lib/knowledge_base";
inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";

string *armours = ({ });
string *weapons = ({ });
string *misc    = ({ });

int    not_configured = 0;
string explicit_name  = 0;

object shop;
string store_room;

static mapping remembered = ([]);

void
arm_me ()
{
  object item;
  
  seteuid(getuid());
  foreach (string *a_w: ({ armours, weapons, misc })) {
    foreach (string armour_or_weapon: a_w) {
      item = clone_object(armour_or_weapon);
      if (!objectp(item)) {
        log_me("Item " + armour_or_weapon +
               " failed to clone", "error", "base-npc");
        continue;
      }
      item->move(TO);
    }
  }
           
  command("wear all");
  command("wield all");
}

void
create_khalakhor_human ()
{
  string guess_name = explicit_name ? explicit_name : FILE_NAME(MASTER);

  if (! configure_from_database(guess_name)) {
    not_configured = 1;
    set_name(guess_name);
  }

  remembered = ([]);
  set_alarm(0.5, 0.0, arm_me);
}

void
add_introduced (string who)
{
  kb_add_introduced(who);
}

void
init_living ()
{
  ::init_living();
  kb_init_living();
}

void
enter_env (object to, object from)
{
  ::enter_env(to, from);
  kb_enter_env(to, from);
}

void
hook_return_intro_new (string str)
{
}

void
hook_return_intro_bad (string str)
{
}

void
hook_return_intro_good (string str)
{
}

void
forget (string str)
{
  m_delkey(remembered, str);
}

/*
 * Function name: hook_return_intro
 * Description  : Called when someone introduces themselves
 *                to us.
 * Arguments    : str - Name of the player introducing.
 * Returns      : n/a
 */

int
hook_return_intro (string str)
{
  if (!remembered[str]) {
    hook_return_intro_new(str);
    remembered[str] = "nice";
    present(str, environment(TO))->add_introduced(query_real_name());
    set_alarm(7200.0, 0.0, &forget(str));
  }
  else if (remembered[str] == "bad")
    hook_return_intro_bad(str);
  else
    hook_return_intro_good(str);
  TP->add_introduced(query_name());
  return 1;
}

void
attacked_by (object who)
{
  ::attacked_by(who);
 
  respond_to_attack(who);
}

string
laddie (object tp)
{
  return tp->query_gender() ? "lassie" : "laddie";
}
 
