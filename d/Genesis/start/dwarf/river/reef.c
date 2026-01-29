/*         
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1996
 *
 * Author: K. Wiklund <gres@cd.chalmers.se>
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

string flower()
{
  return "As you bend down to "+query_verb()+" the flower, your movements\n"+
    "causes a sudden movement in the rock you are standing on, making you fall\n"+
    "into the river. The strong current carries you away into a dark\n"+
    "forbidding hole.\n";

  this_player()->move_object("/d/Genesis/start/dwarf/river/river4");
}
void create_room()
{
  set_short("reef in the middle of an underground river");
  set_long("You are standing on a small rock in the middle of the river.\n"+
	   "All around you, the river is flowing with terrifying\n"+
	   "intensity. It is a small wonder that you even managed to\n"+
	   "get here without drowning. Someone has planted a small flower\n"+
	   "here, and somehow it has managed to not get flushed away.\n");

  add_item("flower","It is a quite ordinary yellow flower.\n");
  add_item("rock","The rock wiggles a little as you bend down to examine it.\n"+
	   "You'd better be careful, or else you'll end up in the river!\n");

  add_cmd_item("flower",({"get","take","pick","eat"}),"@@flower");


}
