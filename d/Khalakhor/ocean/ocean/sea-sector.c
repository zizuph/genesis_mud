/*
 * Base sector file
 * Tapakah, 10/2021
 */

#pragma no_clone
#pragma strict_types

#include <stdproperties.h>

#include "defs.h"

inherit ROOM_BASE;

string
long_descr ()
{
  return "Somewhere in the waters of Khalakhor...\n";
}

string
get_continents ()
{
  return "You see absolutely nothing.\n";
}

int
get_difficulty ()
{
  return 101;
}

mixed *
detect_edge (int primary, int secondary, int max_size, string *alts)
{
  if (primary == 0 || primary == max_size)
    return ({
      (secondary == 0 || secondary == max_size) ? 0 : 1,
      alts[primary ? 0 : 1],
    });
  return 0;
}
  
mixed *
detect_edges (int x, int y)
{
  return
    detect_edge(x, y, MAP_SIZE_X-1, ({"east",  "west"})) ||
    detect_edge(y, x, MAP_SIZE_Y-1, ({"south", "north"}));
}

string
edge_descr ()
{
  mixed edge_data = detect_edges(Xx, Yy);
  if (! edge_data)
    return "";

  string descr = sprintf(" The waters to the %s seem to be swirling wildly, "+
                         "as if encountering something completely foreign.",
                         edge_data[1]);
  if (edge_data[0])
    descr += sprintf(" Your eyes seem to perceive some vague contours to the "+
                     "%s, which remind you of %s.",
                     edge_data[1], NEIGHBOURS[edge_data[1]]);
  return descr + "\n";
}

string
long_descr_with_difficulty ()
{
  return long_descr() + edge_descr() + " " + query_sailing_difficulty_desc() + "\n";
}

void
configure_difficulty (string sea, int difficulty=-1) {

  if (difficulty == -1)
    difficulty = get_difficulty();
  string waters, danger, sailor;

  set_sailing_difficulty(difficulty);
  set_sailing_difficulty_message(sprintf("You navigate skillfully into %s!\n",
                                         sea));
  switch (difficulty) {
  case NORMAL_DIFFICULTY:
    waters = "calm";
    sailor = "a feeble";
    danger = "comfortable";
    break;
  case TRICKY_DIFFICULTY:
    waters = "tricky";
    sailor = "a layman";
    danger = "tricky";
    break;
  case ROUGH_SEAS_DIFFICULTY:
    waters = "rough";
    sailor = "a journeyman";
    danger = "challenging";
    break;
  case HIGH_SEAS_DIFFICULTY:
    waters = "high";
    sailor = "even a veteran";
    danger = "dangerous";
    break;
  case IMPOSSIBLE_SEAS_DIFFICULTY:
    waters = "extreme";
    sailor = "even a master";
    danger = "extremely dangerous";
  }
  set_sailing_fail_message(sprintf("The %s waters of %s are too dangerous " +
                                   "for %s navigator!\n",
                                   waters, sea, sailor));
}

varargs void
create_sea_sector (string sea, int difficulty = 0)
{
  ::create_sea_room();
  add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_LIGHT, 1);

  set_sink_path(SINK_ROOM);
  add_std_exits();
  set_short("Sailing the " + sea);
  set_long(long_descr_with_difficulty);
  configure_difficulty(sea, difficulty);
  add_item(({"continents","landmasses","islands"}),
           get_continents);
}

