/*
 * Base path in Oranea
 *
 * To be inherited by path rooms
 *
 * Ckrik June 1998.
 * This file is called by the path rooms and contains 
 * terrain related information.
 * 
 */

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"

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
{ }

void
create_earthsea_room()
{    
    ::create_herb_room();
    set_short("A path");
    set_long("You are in an ancient forest. Evergreen pines and red " +
      "maple trees surround you. Dense bushes prevent " +
      "you from going off the path. A refreshing mist " +
      "blankets the entire area. In the distance you see " +
      "a majestic forested peak rising out of the mist " +
      "that seems to stretch as far as you can see. " +
      "On a plateau, near the top of the mountain, " +
      "just under the curtain of the mist. " +
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

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_IS, 1);
    change_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs((this_object()->select_herb_files(FOREST_HERBS)),
      FOREST_LOCATIONS, 3);
    create_oranea_path();

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
	tell_room(environment(this_player()), QCTNAME(this_player()) +
	  " gently plucks a red leaf from the red maple tree.",
	  this_player());
	this_player()->catch_msg("You gently pluck a red leaf from the " +
	  "red maple tree.\n");
	leaf = clone_object("/d/Earthsea/herbs/herb_files/red_maple.c");
	leaf->move(this_player());
	leaves--;
	return 1;
    }
    return 0;
}


