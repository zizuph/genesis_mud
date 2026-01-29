/* cloak_ob.c created by Shiva@Genesis
 * This is the "guild object" for the vampire guild
 */

#pragma save_binary

inherit "/std/armour";

#include "../guild.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

static int cloaked;

void create_armour()
{
  set_name( ({ "cloak", GUILD_EMBLEM_ID }) );
  set_long("A finely made, heavy, woolen cloak.  The hood is " +
      "exceedingly large, easily draping over your face to " +
      "conceal your identity.\n");

  set_default_armour(3, A_ROBE, ({ -2, -1, 3 }), TO);

  add_prop(OBJ_I_NO_DROP, 1);

  setuid();
  seteuid(getuid());
}

string query_recover() { return 0; }

#ifndef NO_CLOAK
int cloak(string str)
{
  NF("Cloak whom?\n");
  if (strlen(str) && str != "me" && str != "myself" &&
      str != TP->query_real_name())
  {
    return 0;
  }

  NF("You are already well concealed.\n");
  if (cloaked)
  {
    return 0;
  }

  NF("You need to be able to wear your cloak for that.\n");
  if (!query_worn() && stringp(wear_me()))
  {
    return 0;
  }

  write("You wrap yourself tightly in your voluminous cloak, pulling " +
      "the hood up and over your face.\n");
  say(QCTNAME(TP) + " wraps " + OBJ(TP) + "self tightly in " +
      POS(TP) + " voluminous cloak, pulling the hood up and over " +
      POS(TP) + " face.\n");

  AP(TP, LIVE_I_NEVERKNOWN, VBFC_ME("check_neverknown"));

  if (TP->cloak(cloaked = 1))
  {
    TP->add_subloc(CLOAK_SUB, TO);
  }

  return 1;
}

void reveal_wearer()
{
  if (QP(TP, LIVE_I_NEVERKNOWN) == VBFC_ME("check_neverknown"))
  {
    RP(TP, LIVE_I_NEVERKNOWN);
  }

  TP->cloak(cloaked = 0);
  TP->remove_subloc(CLOAK_SUB);
}

int uncloak(string str)
{
  NF("Uncloak whom?\n");
  if (strlen(str) && str != "me" && str != "myself" &&
      str != TP->query_real_name())
  {
    return 0;
  }

  NF("You aren't cloaked, though.\n");
  if (!cloaked)
  {
    return 0;
  }

  write("You remove your hood and open the front of your " +
      "cloak.\n");

  reveal_wearer();
  return 1;
}

int check_neverknown()
{
  return !IS_WIZ(TP);
}

/* The cloak covers up other armours (see guild shadow),
 * but we should still see the cloak itself.
 */
string show_subloc(string subloc, object on, object for_obj)
{
  if (subloc == CLOAK_SUB)
  {
    return (on == for_obj ? "You are" : capitalize(PRO(on)) + " is") +
        " wearing a " + short() + ".\n";
  }

  return "";
}

int remove(object ob)
{
  reveal_wearer();
  return 0;
}

void remove_object()
{
  reveal_wearer();
  ::remove_object();
}
#endif

void remove_vamp_guild_cloak()
{
  remove_object();
}

void init()
{
  object *inv;

  if (!IS_MEMBER(TP))
  {
    remove_object();
    return;
  }

  if (sizeof(inv = all_inventory(TP) - ({ TO })))
  {
    inv->remove_vamp_guild_cloak();
  }

  ::init();

#ifndef NO_CLOAK
  add_action(cloak,   "cloak");
  add_action(cloak,   "conceal");
  add_action(uncloak, "uncloak");
  add_action(uncloak, "reveal");
#endif

  if (!sizeof(query_adjs()))
  {
    set_adj(TP->query_vamp_covenmaster() ? "blood-red" :
       "jet-black");
  }
}
