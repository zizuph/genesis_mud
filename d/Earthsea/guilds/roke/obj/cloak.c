/*
 * Standard cloaks for Wizards of Roke
 *
 */
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

inherit "/std/armour";
inherit "/std/shadow";

#define ARMOUR_CLASS 17

#define CLOAK_SHADOW "/d/Earthsea/guilds/roke/obj/cloak_shadow"

static int hooded = 0;
static object cloak_shadow;

void create_armour()
{
  set_name("cloak");
  set_pname("cloaks");
  add_adj("dark-blue");
  add_adj("hooded");
  
  set_short("dark-blue hooded cloak");
  set_pshort("dark-blue hooded cloaks");
  
  set_long("A hooded dark-blue cloak. The cloak of wizards " +
	   "that have earn their staff from the School of Wizards " +
	   "on Roke.\n");
  set_ac(ARMOUR_CLASS);
  set_at(A_ROBE);
  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
  
  set_wf(this_object());
}

public int wear_hood(string str)
{
  /* Sanity check */
  if (query_worn() != this_player())
    {
      return notify_fail("You're not wearing the hooded dark-blue cloak.\n");
    }
  if((str != "hood" && str != "hood from head") || hooded)
    {
      return notify_fail("Wear what?");
    }
  tell_room(environment(query_worn()),
	    QCTNAME(query_worn()) + " puts the hood on " +
	    query_worn()->query_possessive() + 
	    " hooded dark-blue cloak over " +
	    query_worn()->query_possessive() + " head.\n", 
	    query_worn());
  query_worn()->catch_msg("You wear the hood on your hooded " +
			   "dark-blue cloak over your head.\n");
  setuid();
  seteuid(getuid());
  cloak_shadow = clone_object(CLOAK_SHADOW);
  cloak_shadow->shadow_me(query_worn());
  cloak_shadow->move(query_worn());
  query_worn()->add_prop(LIVE_I_NEVERKNOWN, 
			 query_worn()->query_prop(LIVE_I_NEVERKNOWN) + 1);
  hooded = 1;
  return 1;
}

public int remove_hood(string str)
{
  /* Sanity check */
  if (query_worn() != this_player())
    {
      return notify_fail("You're not wearing the hooded dark-blue cloak.\n");
    }
  if((str != "hood" && str != "hood from head") || !hooded)
    {
      return notify_fail("Remove what?");
    }
  tell_room(environment(query_worn()),
	    QCTNAME(query_worn()) + " removes the hood on " +
	    query_worn()->query_possessive() + 
	    " hooded dark-blue cloak over " +
	    query_worn()->query_possessive() + " head.\n", 
	    query_worn());
  query_worn()->catch_msg("You remove the hood on your hooded " +
			   "dark-blue cloak over your head.\n");
  cloak_shadow->remove_shadow();
  if (query_worn()->query_prop(LIVE_I_NEVERKNOWN) > 1)
    {
      query_worn()->add_prop(LIVE_I_NEVERKNOWN, 
			     query_worn()->query_prop(LIVE_I_NEVERKNOWN) - 1);
    }
  else
    {
      query_worn()->remove_prop(LIVE_I_NEVERKNOWN);
    }
  hooded = 0;
  return 1;
}

int remove(object obj)
{
  if (query_worn()->query_prop(LIVE_I_NEVERKNOWN) > 1)
    {
      query_worn()->add_prop(LIVE_I_NEVERKNOWN, 
			     query_worn()->query_prop(LIVE_I_NEVERKNOWN) - 1);
    }
  else
    {
      query_worn()->remove_prop(LIVE_I_NEVERKNOWN);
    }
  hooded = 0;
  return 0;
}

void init()
{
  ::init();
  add_action(wear_hood, "wear");
  add_action(remove_hood, "remove");
}

