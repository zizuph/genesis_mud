#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

#define MAX_FIRE_DAMAGE 10
#define WASH_ASHORE "/d/Earthsea/gont/beach/karg_ship/rooms/wash_ashore"

int fire_damage = 0;
int destroyed = 0;

void create_karg_ship_room()
{
}

void reset_karg_ship_room()
{
}

void create_earthsea_room()
{
  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_LIGHT, 1);
  create_karg_ship_room();
}

void destroy_ship_room()
{
  object *livings;

  destroyed = 1;

  tell_room(this_object(), "The deck of the ship collapses under you " +
	    "and you are dumped into the sea water.\n");
  /* Move all livings to a temp room and wash them to shore */
  livings = FILTER_LIVE(all_inventory(this_object()));
  livings->move_object(WASH_ASHORE);
}

int query_ship_room_destroyed()
{
  return destroyed;
}

void enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!from->query_ship_room_destroyed())
    {
      if (destroyed)
	{
	  reset_room();
	}
      fire_damage = 0;
      destroyed = 0;
    }
}

void add_fire()
{
  fire_damage++;
  if (fire_damage > MAX_FIRE_DAMAGE)
    {
      destroy_ship_room();
    }
}

int query_fire()
{
  return fire_damage;
}

void reset_room()
{
  if (!destroyed)
    {
      ::reset_room();
      reset_karg_ship_room();
    }
}

public int is_karg_ship()
{
  return 1;
}
