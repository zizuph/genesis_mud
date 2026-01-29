/*
 * Hammerhands common
 * TAPAKAH, 10/2005
 * From Nick's common board room.
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"
#include "../../daenbraigh.h"

inherit "/d/Khalakhor/std/room";
/*
 * Prototypes
 */
void    load_board();

void
create_khalakhor_room()
{
  ::create_khalakhor_room();
  
  set_short("In the common board room");
  set_long("You are standing in the room where the common board is. It's "+
	   "common for all races in Genesis, immortals as well as mortals. " +
	   "You feel great magic at work here. You see no obvious exits but " +
	   "somehow you feel you can always go back to where you came from."+
	   "\n");
  
  set_noshow_obvious(1);
  
  add_prop(ROOM_I_NO_STEAL, 1);
  add_prop(ROOM_I_NO_TELEPORT, 1);
  add_prop(ROOM_I_NO_ATTACK, 1);
  add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
  add_prop(ROOM_I_INSIDE,1);
  load_board();
}

void
load_board()
{
  object bb;
  
  seteuid(getuid(this_object()));
  bb = clone_object("/d/Genesis/obj/board");
  bb->move(this_object());
}

void
init()
{
  add_action("back", "back");
  add_action("back", "return");
  add_action("back", "go");
  
  ::init();
}

int
back(string str)
{
  if (query_verb() == "go" && str != "back")
    return 0;
  
  TP->move_living("back",TP->query_prop(LIVE_O_LAST_ROOM));
  return 1;
}

/*
 * Function: enter_inv
 * Description: block non-interactives from entering.
 */
void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  
  if (living(ob) && !interactive(ob))
    ob->move(from);
}
