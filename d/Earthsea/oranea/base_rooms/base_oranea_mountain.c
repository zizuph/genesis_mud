/*
 * Base mountain path in Oranea
 *
 * To be inherited by mountain rooms
 *
 * Ckrik July 1998.
 * This file is called by the path rooms and contains 
 * terrain related information.
 * 
 */

inherit "/d/Earthsea/std/room.c";
inherit "/d/Earthsea/lib/room_tell.c";

#include "/d/Earthsea/herbs/specials/hs.c";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"

int flag = random(4);
static int leaves = 5;

static string extra = " ";

void
add_long(string add)
{
  extra = extra + add;
}

string
query_add_long()
{
  return extra;
}

void
create_oranea_path()
{}

void
create_earthsea_room()
{    
  set_short("A forested mountain path");
  set_long("You are on a mountain switchback in an ancient forest. " +
	   "Evergreen pines and red maple trees surround you. " +
	   "Occasionally, you see a little critter scuffling around " +
	   "for food. " +
	   "Looking down the mountain, you see a " +
	   "village near the coast and a small sheltered cove. " +
	   "Further up the mountain, on a plateau, " +
	   "you can see the faint outlines of buildings. " +
	   "@@query_add_long@@");
  
  add_item((({"forest", "forests"})),
	   "The forest surrounds you.\n");
  add_item((({"maple", "red maple", "red maple tree",
		"red maple trees"})),
	   "These trees are red all year long and shed their " +
	   "leaves in the fall. They are extremely beautiful " +
	   "and prized by gardners. People often collect " +
	   "their elegant leaves.\n");
  add_item((({"building", "buildings"})),
	   "From this vantage point you can't really make " +
	   "much out of what is under all that mist.\n");
  add_item((({"pine needles", "needles", "path", "rugged path",
		"tangled undergrowth", "undergrowth", "rocks"})),
	   "Dense forest undergrowth prevents your leaving the rugged "+
	   "path. Pine needles and dried red maple leaves " +
	   "crunch under your feet as you walk.\n");
  add_item((({"tree", "trees"})),
	   "You see many pine and red maple trees around here.\n");
  add_item((({"pine", "pines", "pine tree", "pine trees"})),
	   "This forest is full of sweet smelling pine.\n");

  create_oranea_path();

  add_prop(OBJ_S_SEARCH_FUN, "herb_search");
  add_prop(OBJ_I_SEARCH_TIME, 2);
  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_IS, 1);
  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);

  set_up_herbs(this_object()->select_herb_files(FOREST_HERBS), 
	       FOREST_LOCATIONS, 5);
}

void
init()
{
  ::init();
  add_action("maple_leaves", "pick");
  add_action("maple_leaves", "pluck");
}

int
maple_leaves(string str)
{
  object leaf;

  if (str == "leaf" ||
      str == "maple leaf" ||
      str == "red maple leaf")
    {
      tell_room(environment(this_player()), 
		QCTNAME(this_player()) +
		" gently plucks a red leaf from a red maple tree.\n",
		this_player());
      this_player()->catch_msg("You gently pluck a red leaf from a " +
			       "red maple tree.\n");
      leaf = clone_object("/d/Earthsea/herbs/herb_files/red_maple.c");
      leaf->move(this_player());
      leaves--;
      return 1;
    }
  return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
	start_room_tells();
}
