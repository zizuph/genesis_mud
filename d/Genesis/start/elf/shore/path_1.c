
#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "../desc_include/fir_forest.h"

#pragma save_binary

inherit "/std/room";
inherit ELFAREA;
inherit STRINGLIB;
inherit MISCLIB;

#define NORTH  SHOREDIR + "beach_1"
#define EAST   ROOMDIR  + "cove_1"

#define SHORT  "A small winding path"


#define ENTER_LONG \
  "You are walking along a small, winding path. When you entered it, it " + \
  "seemed to go towards the west, but now it seems to run more northwards.\n" +\
  "At this point it crosses a strange environmental borderline: Instead of "+\
  "the soft limestone ground and dark firs in the east, the path is suddenly " +\
  "surrounded by a rich, tropically lush greenery and hard, black rocks " +\
  "of clearly volcanic origin. The air also feels much warmer and more humid.\n"

#define LEAVE_LONG \
  "You are walking along a small, winding path. When you entered it, it " + \
  "seemed to go towards the south, but now it seems to run more eastwards.\n" +\
  "At this point it crosses a strange environmental borderline: Instead of "+\
  "the rich, tropically lush greenery and black rocks of the northern cliffs, " +\
  "the path is suddenly surrounded by a dark fir forest, growing from a soft " +\
  "limestone ground. The air also feels much chillier.\n"

#define LONG \
  "You are standing an a small, winding path, disappearing to the " +\
  "north and east.\n" +\
  "At this point it crosses a strange environmental borderline: Instead of "+\
  "the soft limestone ground and dark firs in the east, the northern part of the "+\
  "path is surrounded by a rich, tropically lush greenery and hard, black " +\
  "rocks of clearly volcanic origin.\n"



#define ROCK_ITEM ({"rock", "black rocks", "rocks"})
#define ROCK_DESC \
  "The dark, sharp and hard brittleness of these rocks indicate that they " +\
  "probably are the results of recent volcanic activity. But don't worry, " +\
  "as overgrown with green plants as they are, that activity must have " +\
  "been recent only in the geological sense.\n"

create_room()
{
  set_short(SHORT);
  set_long(LONG);

  FIR_FOREST_STD_ITEMS;
  add_item(ROCK_ITEM, WRAP(ROCK_DESC));
/*
  add_dir_phrase("long",  EAST, WRAP(ENTER_LONG));
  add_dir_phrase("long", NORTH, WRAP(LEAVE_LONG));
  add_dir_phrase("long",     0, WRAP(      LONG));
*/
  add_exit(EAST, "east", 0);
  add_exit(NORTH, "north", 0);

  stock();
}

stock()
{
  restock_object(MONSTERDIR+"parrot", 1, "parrot");
}

reset_room()
{
  stock();
}

/*
enter_inv(object obj, object origin)
{
  if (obj && interactive(obj))
    if (origin && file_name(origin) == EAST)
      notify(MAINTAINER,
	     capitalize(obj->query_real_name()) + " enters the shore beach.");

    else if (!origin || file_name(origin) != EAST)
      notify(MAINTAINER,
	     capitalize(obj->query_real_name()) + " enters from " + 
	     (origin ? file_name(origin) : "nowhere") + 
	     ".");
  return ::enter_inv(obj, origin);
}


leave_inv(object obj, object destination)
{

    if (obj && interactive(obj))
    if (destination && file_name(destination) == EAST)
      notify(MAINTAINER,
	     capitalize(obj->query_real_name()) + " leaves the shore beach.");
  return ::leave_inv(obj, destination);
}
*/
