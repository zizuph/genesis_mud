#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

private int alarm_id;
#define FIRE_DAMAGE 300
int oil_fire = 0;

string *search_paths = ({
  "/d/Earthsea/gont/beach/karg_ships/rooms/fore",
  "/d/Earthsea/gont/beach/karg_ships/rooms/midfore",
  "/d/Earthsea/gont/beach/karg_ships/rooms/midship",
  "/d/Earthsea/gont/beach/karg_ships/rooms/midaft",
  "/d/Earthsea/gont/beach/karg_ships/rooms/cabin"
});

void set_is_oil_fire(int i)
{
  oil_fire = i;
}

string fire_type()
{
  if (oil_fire)
    {
      if (environment(this_object())->is_karg_ship())
	{
	  return 
	    "The fire is burning white hot and it looks like it will " +
	    "be able to ignite the ship. It will not be long before the " +
	    "fire consumes the entire ship.";
	}
      else
	{
	  return
	    "The fire is burning white hot and it looks like it will " +
	    "be able to burn for quite a while.";
	}
    }
  else
    {
      return "However, the fire seems to be burning under control.";
    }
}

int is_fire()
{
  return 1;
}

void create_object()
{
  set_name("fire");
  set_pname("fires");
  set_adj("raging");
  add_prop(OBJ_M_NO_GET, "Ouch HOT!!!\n");
  add_prop(OBJ_I_LIGHT, 2);
  set_short("raging fire");
  set_long("A furious raging fire fueled by flammables. " +
	   "@@fire_type@@\n");
}

int filter_karg(object ob)
{
  if (ob->id("__es_basic_karg__") ||
      ob->id("eunuch") ||
      ob->id("_ara_"))
    {
      return 1;
    }
  return 0;
}

int kargs_put_out_fire()
{
  object *kargs;
  object env, ship_room;
  int i, fire = 1;

  /* Bring the kargs in the other room into this room to put
   * out fires
   */
  env = environment(this_object());
  kargs = filter(env->all_inventory(),
		 filter_karg);
  if (sizeof(kargs))
    {
      COMPOSITE_LIVE(kargs);
      tell_room(env, "Rapidly responding, " +
		QCOMPLIVE + " quickly put out the fire.\n");
      fire = 0;
    }

  for (i = 0; i < sizeof(search_paths); i++)
    {
      ship_room = find_object(search_paths[i]);
      if (ship_room == env)
	{
	  continue;
	}
      if (sizeof(kargs))
	{	
	  kargs = filter(ship_room->all_inventory(),
			 filter_karg);
	  kargs->move(env);
	  kargs->emote("$emote rushes in.");
	  if (fire)
	    {
	      COMPOSITE_LIVE(kargs);
	      tell_room(env, "Rapidly responding, " +
			QCOMPLIVE + " quickly put out the fire.\n");
	      fire = 0;
	    }
	}
    }
  if (fire)
    {
      return 0;
    }
  return 1;
}

void burn_env()
{
  object *victims;
  object *inv;
  string *adjacent_rooms;
  object env, fire;
  int i, j, damage;
  mixed result;
  string damage_desc;

  if (kargs_put_out_fire())
    {
      remove_object();
      return;
    }
  env = environment(this_object());
  tell_room(env, "You are engulfed in flames.\n");
  victims = FILTER_LIVE(all_inventory(env));
  for (i = 0; i < sizeof(victims); i++)
    {
      damage = FIRE_DAMAGE / 4;
      damage += random(damage) + random(damage) + random(damage);
      damage -= damage * victims[i]->query_prop(MAGIC_I_RES_FIRE) / 100;
      switch(damage)
	{
	case 0..50:
	  damage_desc = "slightly burned";
	  break;
	case 51..100:
	  damage_desc = "rather burned";
	  break;
	case 101..200:
	  damage_desc = "very charred";
	  break;
	default:
	  damage_desc = "severely charred";
	  break;
	}
      victims[i]->catch_msg("You are " + damage_desc + 
			    " by the raging fire.\n");
      victims[i]->heal_hp(-damage);
      if (victims[i]->query_hp() <= 0)
	{
	  victims[i]->do_die();
	}
    }
  env->add_fire();

  setuid();
  seteuid(getuid());

  adjacent_rooms = env->query_exit_rooms();
  for (i = 0; i < sizeof(adjacent_rooms); i++)
    {
      if (find_object(adjacent_rooms[i])->is_karg_ship())
	{
	  inv = all_inventory(find_object(adjacent_rooms[i]));
	  for (j = 0; j < sizeof(inv); j++)
	    {
	      if (inv[j]->is_fire())
		{
		  return;
		}
	    }
	  if (random(4))
	    {
	      fire = 
		clone_object(
		  "/d/Earthsea/gont/beach/karg_ships/obj/fire_object"
		);
	      fire->set_is_oil_fire(1);
	      fire->move(adjacent_rooms[i]);
	    }
	}
    }
}

public void enter_env(object ob, object from)
{
  ::enter_env(ob, from);
  if (oil_fire && ob->is_karg_ship())
    {
      tell_room(ob, "Your surroundings envelope in flames.\n");
      alarm_id = set_alarm(15.0, 11.0, &burn_env());
      ob->add_fire_damage();
      return;
    }
  tell_room(ob, "A fire ignites near you.\n");
  alarm_id = set_alarm(15.0, 0.0, &remove_object());
}

public void remove_object()
{
  remove_alarm(alarm_id);
  tell_room(environment(this_object()), "The fire dies out.\n");
  ::remove_object();
}
