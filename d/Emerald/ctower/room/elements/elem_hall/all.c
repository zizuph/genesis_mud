inherit "/d/Emerald/ctower/room/ctower_base";
 
#include <tasks.h>
#include "../../ctower.h"
 
#define AIR    1
#define EARTH  2
#define FIRE   4
#define WATER  8
#define ALL    15
#define GOTTEN 16

#define LIVE_I_FOUND_SAPPHIRE "_live_i_found_ctower_sapphire"
 
void
create_ctower_room()
{
  set_short("Room of Elemental Fury");
 
  set_long("This room is a clash between all of the "+
     "elements, producing a chaotic combination which makes this "+
     "room deadly but strangely majestic.\n");
 
  add_item( ({ "flames", "flame", "fire", "inferno" }),
	    "@@flame_desc");
 
  add_item( ({ "wind", "air", "winds" }),
	    "@@wind_desc");
 
  add_item(({"stalactite", "stalagmite"}), "The formations "+
     "are made of the same material as the walls and appear to be rather "+
     "sharp.\n");
 
  add_item("water", "@@water_desc");
 
  add_item(({"mist"}), "The mist is being churned "+
     "rapidly by a very strong wind and is wet and cold.\n");
 
  add_item(({"smoke"}), "The smoke is being churned "+
     "rapidly by a very strong wind and is quite warm.\n");
 
  add_item(({"mud"}), "The mud is churning "+
     "slowly and seems to change consistency constantly.\n");
 
  add_item(({"lava"}), "The lava is churning "+
     "slowly and you can see the waves of heat radiating from the "+
     "floor.\n");
 
  add_item(({"wall"}), "The walls are "+
     "made of a dark crystal that seems to absorb the light.\n");
 
  add_item( ({ "floor", "ground", "earth" }),
	    "@@ground_desc");
 
  add_item(({"ceiling", "roof"}), "The upper part of the room "+
     "seems to be a battle between mist, smoke, wind, flames and "+
     "stalactites.\n");
 
  add_exit(CTOWER_ROOM_ELEM + "smoke", "south");
  add_exit(CTOWER_ROOM_ELEM + "mud", "north");
  add_exit(CTOWER_ROOM_ELEM + "lava", "west");
  add_exit(CTOWER_ROOM_ELEM + "mist", "east");
 
  add_prop(OBJ_S_SEARCH_FUN, "search_it");
}
 
string
search_it(object player, string what)
{
  int success, found;
 
  found = this_player()->query_prop(LIVE_I_FOUND_SAPPHIRE);
  success = player->resolve_task(TASK_SIMPLE, ({ TS_INT, SS_AWARENESS }));
  
  if (success < 0 || found >= GOTTEN)
  {
    return 0;
  }

  if (what == "flames" || what == "flame" || 
      what == "fire" || what == "inferno") 
  {
    found |= FIRE;      
  }
  else if (what == "wind" || what == "air" || what == "winds") 
  {
    found |= AIR;
  }
  else if (what == "water") 
  {
    found |= WATER;
  }
  else if (what == "ground" || what == "earth" || what == "floor") 
  {
    found |= EARTH;
  }
  else
  {
    return 0;
  }

  this_player()->add_prop(LIVE_I_FOUND_SAPPHIRE, found);

  return (found == ALL ? "Your search reveals a sapphire!\n" :
          "You saw a gem but it quickly flits to another element.\n");
}
 
int
get_it(string str)
{
  object gem;
  int  success;
 
  notify_fail("Get what?\n");
  if (str!="sapphire" && str!="black sapphire")
  {
    return 0;
  }
 
  if (this_player()->query_prop(LIVE_I_FOUND_SAPPHIRE) < ALL)
  {
    return 0;
  }
 
  success = this_player()->resolve_task(TASK_ROUTINE, ({ TS_DEX, TS_DEX }));

  if (success > 0) 
  {
    gem = clone_object(CTOWER_OBJ + "bsaph");
    gem->move(this_player(), 1);
    
    this_player()->add_prop(LIVE_I_FOUND_SAPPHIRE, GOTTEN);

    write("You quickly grab the black sapphire.\n");
    return 1;
  }

  this_player()->reduce_hit_point(this_player()->query_max_hp() / 10);

  write("You try to get the black sapphire but just aren't quick enough.\n");
  write("You snatch back your hand but not before being hurt!\n");

  if (this_player()->query_hp() <= 0)
  {
    this_player()->do_die(this_object());
  }

  return 1;
}

void
init()
{
  ::init();
 
  add_action(get_it, "get");
  add_action(get_it, "take");
}
 
string
flame_desc()
{
  int found = this_player()->query_prop(LIVE_I_FOUND_SAPPHIRE);
  string str = "As you stare deeper into the flames, you think " +
               "you can detect a pattern to their dance. And " +
               "with the last vestiges of your will, you tear " +
               "your eyes away before it is too late. You are " +
               "covered in sweat, and not sure how much time " +
               "has passed";

  if (found < GOTTEN) 
  {
    if (found == ALL)
    {
      return str + ", but you do see a sapphire.\n";
    }

    return str + ", but you did see something.\n";
  }

  return str + ".\n";
}
 
string
wind_desc()
{
  int found = this_player()->query_prop(LIVE_I_FOUND_SAPPHIRE);
  string str = "The incredibly fierce winds howl thru the " +
               "room, buffeting you mercilessly";

  if (found < GOTTEN) 
  {
    if (found == ALL)
    {
      return str + ", but you do see a sapphire.\n";
    }

    return str + ", but you did see something.\n";
  }

  return str + ".\n";
}
 
string
ground_desc()
{
  int found = this_player()->query_prop(LIVE_I_FOUND_SAPPHIRE);
  string str = "The floor is a churning mass of lava, mud, water "+
	       "and stalagmites which all seem to be battling for floor "+
               "space";

  if (found < GOTTEN) 
  {
    if (found == ALL)
    {
      return str + ", but you do see a sapphire.\n";
    }

    return str + ", but you did see something.\n";
  }

  return str + ".\n";
}
 
string
water_desc()
{
  int found = this_player()->query_prop(LIVE_I_FOUND_SAPPHIRE);
  string str = "It is normal water although you are not sure " +
	   "how it stays in the room. It is cool, but not cold";

  if (found < GOTTEN) 
  {
    if (found == ALL)
    {
      return str + ", but you do see a sapphire.\n";
    }

    return str + ", but you did see something.\n";
  }

  return str + ".\n";
}
