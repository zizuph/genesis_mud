inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

public int oiled = 0;

public string oil_dependent()
{
  if (oiled)
    {
      if (oiled < 6000)
	{
	  return "The hay is slightly soaked in oil.";
	}
      else
	{
	  return "The hay is drenched in oil and completely soaked through.";
	}
    }
  return "The hay seems dry.";
}

void create_object()
{
  set_name("bunch of hay");
  set_pname("bunches of hay");
  add_name("hay");
  add_pname("hays");
  set_long("A bunch of hay bound together by string at the center. " +
	   "@@oil_dependent@@\n");
  add_prop(OBJ_I_VALUE, 50);
  add_prop(OBJ_I_WEIGHT, 6000);
  add_prop(OBJ_I_VOLUME, 5000);
  add_prop(OBJ_M_NO_BUY, 1);
}

int light_on_fire(string str)
{
  object obj, env, fire;

  env = environment(this_object());
  if (parse_command(str, env,
		    "%o [on] [fire]", obj))
    {
      if (obj == this_object())
	{
	  setuid();
	  seteuid(getuid());
	  fire =
	    clone_object("/d/Earthsea/gont/beach/karg_ships/obj/fire_object");
	  if (oiled >= 6000)
	    {
	      fire->set_is_oil_fire(1);
	    }
	  fire->move(env);
	  remove_object();
	  return 1;
	}
    }
  notify_fail("Ignite what on fire?\n");
  return 0;
}

int filter_flask(object ob)
{
  if (stringp(function_exists("remove_oil", ob)) &&
      ob->query_amount() > 0)
    {
      return 1;
    }
  return 0;
}

int pour_oil(string str)
{
  object *flasks, hay;
  int amount;

  if (parse_command(str, environment(this_object()),
		    "'oil' [on] %o", hay))
    {
      flasks = filter(all_inventory(this_player()),
		      filter_flask);
      if (flasks != 0)
	{
	  write("You empty the " + flasks[0]->short() + " and " +
		"pour some oil onto a bunch of hay.\n");
	  tell_room(environment(this_player()),
		    QCTNAME(this_player()) + " pours some oil onto " +
		    "a bunch of hay.\n", this_player());
	  amount = flasks[0]->query_amount();
	  oiled += amount;
	  flasks[0]->remove_oil(amount);
	  return 1;
	}
      else
	{
	  write("You have no oil to pour on the hay.\n");
	  return 1;
	}
    }
  notify_fail("Pour what on what?");
  return 0;
}

void init()
{
  ::init();
  
  add_action(light_on_fire, "light");
  add_action(light_on_fire, "ignite");
  add_action(pour_oil, "pour");
}

