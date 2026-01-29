/* room1.c
   Mort 911004 */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>

#define PORDIR TOWNDIR + "mansion/porcia/"

object guard,nimgame;

int
check_guard() {
  if (guard) {
    if (guard->getfrust()) {
      write("The guards is so distracted he lets pass you..\n");
      return 0;
    }
    write("The guard looks at you carefully and won't let you pass.\n");
    return 1;
  }
  return 0;
}

reset_room() {
    if (!guard)
	guard = clone_object(PORDIR + "guard");
    guard->move_living("X",this_object());
    if (!nimgame)
	nimgame = clone_object(PORDIR + "nim");
    nimgame->move(this_object());
    nimgame->set_opponent(guard);
}

create_room() {
    set_short("A simple room");
    set_long(break_string("You find yourself in a very small room. " +
	"The walls are covered with dust, and cobwebs are hanging from " +
	"the ceiling. You feel quite uncomfortable in this room... " +
	"it looks a bit like a trap and you wonder if you'll ever be " +
	"able to leave it again.\n",70));
    guard = clone_object(PORDIR + "guard");
    guard->move_living("X",this_object());
    nimgame = clone_object(PORDIR + "nim");
    nimgame->move(this_object());
    nimgame->set_opponent(guard);
    add_prop(ROOM_I_INSIDE,1);
    add_exit(PORDIR + "entrance", "north","@@check_guard");

}

/*
 * Function name:
 * Description  :
 */

